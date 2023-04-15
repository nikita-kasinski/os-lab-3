# Exercise 3 ОS
## Made by Nikita Kasinski
### Overview
The app comprises main process and several marker threads. Markers mark shared array with their id, while main manages which marker should continue working and which should finish.
### Tools
* gcc - compiler
* make - build automation tool
* gtest - library for creating unit tests on c++
* gcov, lcov - tools to test code coverage
### CI/CD
CI/CD is made via Github Actions. There are build and test jobs in the workflow file, which enables project to be built and tested on a clean remote runner.
### Manual running, building, testing and testing code coverage
To perform any listed task several tools and libraries are required:
* gcc
* make 
* gtest (when testing code and code coverage)
* gcov (when testing code coverage)
* lcov (when testing code coverage)

Prepared targets:
* make run - launching the app
* make build - building the app
* make test - running tests
* make report - testing code coverage
