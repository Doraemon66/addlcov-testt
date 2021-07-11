# Use Gcov and LCOV to perform code coverage testing for C/C++ projects

[中文 Readme](README-CN.md)

## Question

How do you do when your C/C++ project does not have unit test code, and you want to do code coverage testing?

There are some of these tools for C/C++ project code coverage testing on the market, but most of them are charged.

I researched a paid C/C++ code coverage tool [Squish Coco](https://shenxianpeng.github.io/2019/05/squishcoco/) a long time ago. Since there were some compilation problems that were not resolved at that time, I just No purchase on hold.

When I restarted the work on code coverage testing of C/C++ projects, I learned that GCC actually provides code coverage compilation options `-fprofile-arcs` and `-ftest-coverage`. In order to figure out how [Gcov](https://gcc.gnu.org/onlinedocs/gcc/Gcov.html) works, I did some investigations, and the results are summarized as follows.


## Precondition

If you need to run the program in this repository, you need to install [gcc](https://gcc.gnu.org/install/index.html) and [lcov](http://ltp.sourceforge.net/coverage/lcov.php) first.

## About the branch

The `master` branch only saves files such as `.c`, `.h`, and `makefile` that need to be used for demonstration.

The `coverage` branch saves all the files generated during the compilation process, as well as the final code coverage HTML report file (under the `out` directory).

## Generate code coverage

If you want to generate code coverage yourself, you only need to perform the following 3 steps:

```bash
# step 1 compile
make

# step 2 run executable
./main

# step 3 generate the report
make report

# delete all files generated above
make clean
```

The above commands are actually executed through `makefile` by putting some other commands together. For details, please refer to the steps below.

### 1. Compile

```bash
$ make
# this is the output after adding -fprofile-arcs -ftest-coverage compilation options
gcc -fPIC -fprofile-arcs -ftest-coverage -c -Wall -Werror -fpic main.c
gcc -fPIC -fprofile-arcs -ftest-coverage -c -Wall -Werror -fpic foo.c
gcc -fPIC -fprofile-arcs -ftest-coverage -o main main.o foo.o
```

Let's take a look at what files are generated in the current workspace.

```bash
$ ls
foo.c  foo.gcno  foo.h  foo.o  img  main.c  main.exe  main.gcno  main.o  makefile  README.md  README-CN.md
```

After compilation, in addition to generating `main` and `.o` files, there are also two `.gcno` files.

> The `.gcno` notes file is generated when the source file is compiled with the GCC `-ftest-coverage` option. It contains information to reconstruct the basic block graphs and assign source line numbers to blocks.

### 2. Run executable

The program is compiled with the options `-fprofile-arcs` and `-ftest-coverage`, after running the executable file `main`, the run data is recorded in the count data `.gcda` file.

```bash
$ ./main
Start calling foo() ...
when num is equal to 1...
when num is equal to 2...

# After main is executed, two .gcda files are generated
$ ls
foo.c  foo.gcda  foo.gcno  foo.h  foo.o  img  main.c  main.exe  main.gcda  main.gcno  main.o  makefile  README.md  README-CN.md
```

> The `.gcda` count data file is generated when a program containing object files built with the GCC `-fprofile-arcs` option is executed. A separate `.gcda` file is created for each object file compiled with this option. It contains arc transition counts, value profile counts, and some summary information.

### 3. Generate report

Finally, execute `make report` to generate the final HTML report, which actually does the following things:

First, generate report file

When the two files `.gcno` and `.gcda` are available, the report file is generated through the `gcov` command, `.gcov` file is generated by executing `gcov main.c foo.c` command.

```bash
gcov main.c foo.c
File 'main.c'
Lines executed:100.00% of 5
Creating 'main.c.gcov'

File 'foo.c'
Lines executed:85.71% of 7
Creating 'foo.c.gcov'

Lines executed:91.67% of 12
```

Second, generate an HTML report

Although the above output can already know the code coverage of the two source files of `main.c` and `foo.c`, it is not intuitive enough, and it is impossible to see which line is not executed. `LCOV` is a tool that can help us generate more intuitive HTML reports.

> LCOV is a graphical front-end for GCC's coverage testing tool gcov. It collects gcov data for multiple source files and creates HTML pages containing the source code annotated with coverage information. It also adds overview pages for easy navigation within the file structure. LCOV supports statement, function and branch coverage measurement.

1. using `lcov --capture --directory. --output-filecoverage.info` command to generate coverage.info data file.

```bash
$ lcov --capture --directory . --output-file coverage.info
Capturing coverage data from .
Found gcov version: 4.8.5
Scanning . for .gcda files ...
Found 2 data files in .
Processing foo.gcda
Processing main.gcda
Finished .info-file creation
```

2. execute `genhtml coverage.info --output-directory out` to generate HTML report.

```bash
$ genhtml coverage.info --output-directory out
Reading data file coverage.info
Found 2 entries.
Found common filename prefix "/workspace/coco"
Writing .css and .png files.
Generating output.
Processing file gcov-example/main.c
Processing file gcov-example/foo.c
Writing directory view page.
Overall coverage rate:
  lines......: 91.7% (11 of 12 lines)
  functions..: 100.0% (2 of 2 functions)
```

## Code coverage report

![index](img/index.png)

![example](img/example.png)

![main.c](img/main.c.png)

![foo.c](img/foo.c.png)

Note: git checkout to `coverage` branch, under `out` directory to view or download the report.

## Reference

Some useful documents related to this research:

* Gcov homepage: https://gcc.gnu.org/onlinedocs/gcc/Gcov.html
* Lcov homepage: http://ltp.sourceforge.net/coverage/lcov.php

* gcovr homepage: https://github.com/gcovr/gcovr （Another HTML report generation tool implemented in Python, the report display is slightly different from Lcov.)

* Gcov Data File Relocation to Support Cross-Profiling
    * https://gcc.gnu.org/onlinedocs/gcc/Cross-profiling.html#Cross-profiling
    * https://stackoverflow.com/questions/7671612/crossprofiling-with-gcov-but-gcov-prefix-and-gcov-prefix-strip-is-ignored

* Using gcov with the Linux kernel: https://01.org/linuxgraphics/gfx-docs/drm/dev-tools/gcov.html
