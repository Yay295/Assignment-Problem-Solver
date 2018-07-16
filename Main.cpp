#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <random>
#include <algorithm>
#include "APS.h"

// The int type to use to hold the matrix cost data.
typedef size_t D_TYPE;

const size_t THOUSAND = 1000;
const size_t MILLION = THOUSAND * THOUSAND;
const size_t BILLION = MILLION * THOUSAND;

std::vector<D_TYPE> values;

// Treats a vector as a base `max` unsigned integer and increments it by 1.
// Returns true if it was safely incremented, and false if it overflowed.
// If it overflowed, all values in the vector will be 0.
bool incrementValues(const size_t max) {
	for (size_t i = values.size(); i--;) {
		if (values[i] < max) {
			++values[i];
			return true;
		} else values[i] = 0;
	}
	return false;
}

void printMatrix(const size_t width, const size_t height, std::ostream & out = std::cout, const std::string & delimeter = " ") {
	size_t max = values[0], maxDigits = 0;

	for (size_t i = 1; i < width * height; ++i)
		if (values[i] > max) max = values[i];

	do {max /= 10; ++maxDigits;} while (max);

	for (size_t row = 0; row < height; ++row) {
		for (size_t column = 0; column < width; ++column) {
			if (column) out << delimeter;
			out.width(maxDigits);
			out << size_t(values[row*width + column]);
		}
		out << '\n';
	}
	out << '\n';
}

// Calculates the result of `todo` `width` x `height` matrices and averages
// their execution time.
void speedTest(const size_t todo, const size_t width, const size_t height) {
	std::cout << "== Speed Test (" << todo << ' ' << width << 'x' << height << ") ==\n";

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<size_t> random(0, D_TYPE(width * height));
	clock_t totalTime = 0;

	values.resize(width * height);

	for (size_t total = 1; total <= todo; ++total) {
		for (size_t i = 0; i < values.size(); ++i)
			values[i] = D_TYPE(random(mt));

		//std::cout << '.';

		if (total < 12) std::cout << '\n' << total;
		else if (total < 100 && total % 12 == 0) std::cout << '\n' << total / 12 << " Dozen";
		else if (total < THOUSAND && total % 100 == 0) std::cout << '\n' << total / 100 << " Hundred";
		else if (total < MILLION && total % THOUSAND == 0) std::cout << '\n' << total / THOUSAND << " Thousand";
		else if (total < BILLION && total % MILLION == 0) std::cout << '\n' << total / MILLION << " Million";
		else if (total % BILLION == 0) std::cout << '\n' << total / BILLION << " Billion";

		//printMatrix(width, height);

		clock_t start = clock();
		APSO X(values, width, height);
		clock_t end = clock();
		totalTime += end - start;

		//for (size_t i = 0; i < (width < height ? width : height); ++i) std::cout << '(' << X.results[i].x << ',' << X.results[i].y << "), ";
		//for (size_t i = 0; i < (width < height ? width : height); ++i) fout << X.results[i].x << ',' << X.results[i].y << '\n';

		//fout << width << ',' << end - start << '\n';
	}

	std::cout << "\n\n" << (totalTime / double(todo)) / CLOCKS_PER_SEC << "s Average Time\n\n";
}

// This test iterates through every unique matrix from a matrix of size
// minWidth x minHeight filled with zeroes to a matrix of size
// maxWidth x maxHeight filled with the value (maxWidth * maxHeight).
void exhaustiveTest(const size_t minWidth, const size_t minHeight, const size_t maxWidth, const size_t maxHeight) {
	const size_t outWidth = 1 + std::to_string(size_t(std::pow(maxWidth * maxHeight, maxWidth * maxHeight))).length();

	std::cout << "== Exhaustive Test ==\n\n";
	std::cout << "Height   Width   Tests     Time (s)\n";

	for (size_t height = minHeight; height <= maxHeight; ++height) {
		for (size_t width = std::max(height, minWidth); width <= maxWidth; ++width) {
			const size_t maxValue = width * height - 1;
			values.resize(maxValue + 1);

			std::cout.width(9);
			std::cout << std::left << height;
			std::cout.width(8);
			std::cout << std::left << width;
			std::cout.width(outWidth);
			std::cout.precision(0);
			std::cout << std::left << std::fixed << std::pow(width * height, width * height);
			std::cout.flush();

			clock_t totalTime = 0;
			do {
				//printMatrix(width, height);

				clock_t start = clock();
				APSO X(values.data(), width, height);
				clock_t end = clock();
				totalTime += end - start;
			} while (incrementValues(maxValue));

			std::cout << totalTime / double(CLOCKS_PER_SEC) << '\n';
		}
	}
}

// Tests specific matrices.
void specificTest() {
	std::cout << "== Specific Tests ==\n\n";

	std::vector<std::vector<unsigned char>> matrices = {
		{0, 0,
		 0, 0},

		{0, 0, 0, 0,
		 0, 0, 0, 0,
		 0, 0, 0, 0,
		 0, 0, 0, 1},

		{0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0,
		 0, 0, 1, 1, 1,
		 0, 0, 1, 1, 1,
		 0, 0, 1, 1, 1}
	};

	for (auto & matrix : matrices) {
		APSO X(matrix.data(), size_t(sqrt(matrix.size())), size_t(sqrt(matrix.size())));
		std::cout << "Results:\n";
		X.printResults(std::cout);
		std::cout << "Result Cost: " << size_t(X.resultCost(matrix.data())) << "\n\n";
	}
}

int main() {
	/*std::ofstream fout("times.csv");
	std::ofstream matrix("matrix.csv");*/

	speedTest(10000, 50, 50);
	speedTest(100, 250, 250);
	speedTest(10, 1000, 1000);
	//exhaustiveTest(1, 1, 3, 3);
	specificTest();

	std::cout << "\a\aPress 'Enter' to exit";
	std::cin.ignore();
}
