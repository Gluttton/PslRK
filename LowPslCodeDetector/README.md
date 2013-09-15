Low PSL code detector
=====================
Detector of codes with low peak sidelobe (PSL) level.



System requirements
===================
GNU Linux based 64-bit operating system is required.

To build program are required:
- ```make```     - build automation tool;
- ```g++```      - GNU C++ compiler.

To build program tests are also required:
- ```gcov```     - source code coverage analysis tool;
- ```gprof```    - performance analysis tool;
- ```lcov```     - tool for summarise code coverage information;
- ```gtest```    - Google's framework fow writing C++ tests;
- ```pthread```  - POSIX threads library.



Building and testing
====================
To build program type in projects rood directory:
```
make
```

It is possible to pass optimization level by arguments, for instance:
```
make OPTIMIZATION=OX
```
Where OX is optimization level (O0, O2, O3, etc).

By default optimization level is O0 (without optimization).

To build tests type in projects root directory:
```
make testing
```
To launch tests type:
```
./lpslcd.test

```
To generate test coverage report type:
```
make coverage
```
To generate performenace report type:
```
make profile
```



Usage
=====
Launch program in terminal:
```
./lpslcd
```
Programs results are recorded in ```lpslcd.dat``` test file.

Programs statistic is recorded in ```lpslcd.stat``` text file.
