# YUCK Compiler


## Program Organisation

- [`lexer`](/src/lexer.flex) - lexer for C-like syntax
- [`parser`](/src/parser.y) - parser for C-like syntax
- [`yuck`](/src/c_compiler.cpp) - optimised YUCK compiler (c-to-mips)
- [`ast`](/include) - structure of Abstract Syntax Tree (AST) 


## Environment


### Makefile

This repository includes a [`makefile`](/makefile) to build the program via the following commands:

``` shell
# build all the targets
make all

# To build the lexer file
make lexer

# To build the parser file
make parser

# To build the compiler
make yuck

# To clear output files
make clean
```

#### Translator Function

Invoked using the flag `--translate`, with the source file and output file specified on the command line:
```
bin/c_compiler --translate [source-file.c] -o [dest-file.py]
```


#### Compilation Function

Invoked using the flag `-S`, with the source file and output file specified on the command line:
```
bin/c_compiler -S [source-file.c] -o [dest-file.s]
```


---------------
## C Test Suite

The tests cases can be found in the folder: [`test_deliverable`](/test_deliverable/test_cases) 


### Testing YUCK

A [`bash`](https://en.wikipedia.org/wiki/Bash_(Unix_shell)) script that runs the tests. It will build your program, then apply it to each input in turn to produce a file containing the generated output.

You can run the program via the commands:
``` shell
# Testing the translator
./test_translator.sh

# Testing the compiler
./test_compiler.sh

# Testing translator formative
./c_translator_formative.sh

# Testing c test deliverables
./test_deliverable.sh

```
NB: for [test_compiler.sh](./test_compiler.sh), you MUST download [Mars 4.5](https://www.softpedia.com/get/Programming/Coding-languages-Compilers/Vollmar-MARS.shtml) - a MIPS assembly simulator - and include it in the [test](./test) folder.

NB: the [unix execute permissions](https://en.wikipedia.org/wiki/Modes_(Unix))
may have been lost, in which case you can indicate the script should be
executable with: 
````
# eg.
chmod u+x ./test_compiler.sh
````

## Project Management

To keep track of progress and key milestones, we've included the following files to log the progress of this project.

- [`milestones`](/management/milestones.csv) a list of defined milestones, including the dependencies that each milestone has, which team member is responsible for leading it, and the completion status of each,

- [`week-log`](/management/week-log.csv) a week-by-week view of planned effort (hours to be spent) going into the project (taking into account other deadlines that you expect to have from other courses), and

- [`effort-log`](/management/effort-log.csv) a log of actual effort spent on each milestone (including an assessment of whether the estimates were optimistic or pessimistic, and whether you need to reduce the scope of certain deliverables).



## Features

The YUCK is able to compile the following:

### Basic
- [x] functions without arguments
- [x] `int` type variables
- [x] local variables
- [x] arithmetic expressions
- [x] logical expressions
- [x] if-then-else statements
- [x] while loops

### Intermediate
- [x] scope
- [x] functions with parameters (up to 4)
- [x] for loops
- [x] do-while loops
- [ ] local arrays
- [ ] global arrays
- [ ] reading and writing elements of an array
- [x] recursive function calls
- [ ] `enum` keyword
- [x] `switch` statements
- [x] `break` keyword
- [x] `continue` keyword

### Advanced
- [ ] `double`, `float`, `char`, `unsigned`, `structs`, and `pointer` type variables
- [x] calling externally-defined functions
- [x] mutually recursive function calls
- [x] locally scoped variable declarations
- [ ] `typedef` keyword
- [x] `sizeof` keyword
- [ ] address of variable via `&` operator
- [ ] derefercing a pointer-variable via `*` operator
- [ ] pointer arithmetic
- [ ] character literals (including escape sequences eg. `\n`)
- [ ] strings (as NULL-terminated character arrays)
- [ ] declaration and use of structs


---------------
## Vagrant

In order to run YUCK on a personal machine, use [VirtualBox](https://www.virtualbox.org/) together with [Vagrant](https://www.vagrantup.com/); The target environment and required dependencies:  `make bison flex python3 g++-mips-linux-gnu qemu tidy`  will be installed via Vagrant.

This repository contains a [Vagrantfile](Vagrantfile), which is a script that sets up a blank Ubuntu 16.04 environment, and then installs all the necessary tools. 

- Open a shell in this directory.

- Run `vagrant up` to download, install, and configure the VM.

- Run `vagrant ssh` to log into the VM.

- Run `cd /vagrant` : This will put you in the same directory, with
your host files shared with the VM.

You can then use command line build tools in the VM, while editing
the source files in your host editor.

If you want to stop the machine,

- Run `exit` to exit the session,

- Run `vagrant halt` to shut down the virtual machine.

If you later run `vagrant up` again, it will not need to download the VM from scratch.

The tests and builds can then be run from there.
