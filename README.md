# toki-open-2018

The repository consists of the skeleton, solution, problem descriptions, and testcase generator for TOKI Open 2018.

## Testcases

The testcases are generated using [tcframe](https://github.com/tcframe/tcframe) framework.

## Grader

There are two versions of the grader. `grader.cpp` is the one distributed to the contestants, while `grader_server.cpp` is the one in the grading server.

The grader in the grading server prints a hash password at the end of the execution, to make sure that the contestant will not terminate their program. The password is checked in our custom scorer `scorer.cpp`. Therefore, you will need to compile the solution using `grader_server.cpp` for generating the actual testcases deployed in the grading server (and to be checked with custom scorer `scorer.cpp`).
