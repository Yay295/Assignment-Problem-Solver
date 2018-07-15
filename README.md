# Assignment Problem Solver

This code solves the [Assignment Problem](https://en.wikipedia.org/wiki/Assignment_problem). As far as I know, this is the fastest solver in existence. If you know of a faster one, create an issue request so I can beat it. The solver is in `APS.h`, and examples of its usage are in `Main.cpp`. There is no `APS.cpp` because the solver is entirely templated.

## Comparison With Other Implementations

One reason that I originally wrote this code was that I could not find a good, easy-to-use implementation for C++ already out there. I can't remember how thorough my initial search was, but I have since searched much harder to find every implementation - not just in C or C++ - so that I could compare my code with others'.

The first test I ran on every implementations was to find a solution to the following three matrices:
```
0 0
0 0
```
```
0 0 0 0
0 0 0 0
0 0 0 0
0 0 0 1
```
```
0 0 0 0 0
0 0 0 0 0
0 0 1 1 1
0 0 1 1 1
0 0 1 1 1
```
While fairly simple, these three matrices each pose slight challenges that I ran into myself. The fact that not all of the implementations pass this test shows their use.

Next, I ran a speed test (on the implementations that passed the first test), timing how long it took them to solve a certain number of random matrices of a given size. Due to difference in programming language and timing, these will not be exact, but I have tried to be as accurate as possible by timing the least amount of code possible (i.e. not timing initialization of matrices). I have entered these times as relative to my own code (< 1.0 is slower, > 1.0 is faster).

The Version Used is the date that the code I tested was last updated. Some of these have been updated since then, and I am working on re-testing them. Others have been tested more recently, but their code has not changed in some time.

__table still under construction__

| Author                    | Language   | Version Used  | Test 1 | Test 2 | Test 3 | Speed |
|---------------------------|------------|---------------|--------|--------|--------|-------|
| [Brian M. Clapper]        | Python     | Nov. 19, 2016 | Pass   | Pass   | Pass   |       |
| [dlib]                    | C++        | Oct. 10, 2016 | Pass   | Fail   | Fail   |       |
| [HungarianAlgorithm.com]  | ?          | July 15, 2018 | Pass   | Pass   | Pass   | ?     |
| [Kevin L. Stern]          | Java       | Nov. 19, 2016 | Pass   | Pass   | Pass   |       |
| Lantao Liu                | C++        | June 18, 2013 | Pass   | Fail   | Fail   |       |
| [Mattias Andrée]          | C          | Apr. 24, 2014 | Pass   | Pass   | Pass   |       |
| [saebyn]                  | C++        | Mar. 27, 2016 | Pass   | Pass   | Pass   | 0.5   |
| [University of Melbourne] | JavaScript | July 15, 2018 | Fail   | Fail   | Fail   |       |
| [Vamsi Kundeti]           | C++        | Dec. 20, 2008 | ?      | Fail   | Fail   |       |
| Yay295                    | C++        | Mar.  6, 2018 | Pass   | Pass   | Pass   | 1.0   |

### Notes

Although the [HungarianAlgorithm.com] implementation passed my tests, I did not time it beacuse it is a webpage, and the network tranfer times would have dwarfed any actual calculation times. Also, it only allows matrices up to 10x10.

Lantao Liu's code didn't compile until making modifications to `Matrix.h`. Its original source was http://robotics.usc.edu/~lantao/codes/hungarian.php, but I can no-longer find it online. Lantao Liu has a website at http://iurobotics.net/lantaoliu.html.

The [University of Melbourne] code doesn't actually solve it for you, but guides you along to a solution. Unfortunately, it's so broken that it won't let you reach a solution in many cases.

[Vamsi Kundeti]'s code passed my first test without crashing, but I wasn't able to determine what result it found. The code is a mess, and since it crashed on the second and third test I didn't bother checking the first more closely.

[Brian M. Clapper]: https://github.com/bmc/munkres
[dlib]: http://dlib.net/
[HungarianAlgorithm.com]: http://hungarianalgorithm.com/solve.php
[Kevin L. Stern]: https://github.com/KevinStern/software-and-algorithms/blob/master/src/main/java/blogspot/software_and_algorithms/stern_library/optimization/HungarianAlgorithm.java
[Lantao Liu]: http://robotics.usc.edu/~lantao/codes/hungarian.php
[Mattias Andrée]: https://github.com/maandree/hungarian-algorithm-n3
[saebyn]: https://github.com/saebyn/munkres-cpp
[University of Melbourne]: http://www.ifors.ms.unimelb.edu.au/tutorial/hungarian/welcome_frame.html
[Vamsi Kundeti]: https://launchpad.net/lib-bipartite-match
