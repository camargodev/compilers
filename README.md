# 'The Language' Compiler (TLC)

Compiler for a programming language called The Language.
Proposed and developed in UFRGS' Compilers course.
You can clone or download this repository freely.


### Prerequisites

TLC is a flex-bison based compiler. So, you will need to install them.
You can use
```
apt-get install flex
```
and
```
apt-get install bison
```
It also uses programming language C, so you will need GCC.

### Installing

To get started, open the main folder on a Unix based system and type ```make```.
This command should generate ```flex``` and ```bison``` necessary files.
Also, with ```make```, you automatically generates the AST (Abstract Syntax Tree) for the language.

## Running the tests

To test, you can use ```make test```.
Also, each part has a different set of tests.
You can just get into the part specific folder and run the same command.

## Parts

The root folder has everything that is necessary for running this compiler.
Each specific part folder just marks the evolution of the project.

### Part 1 [Aug 2018]

Basically, a lexer scanner was developed to accept the tokens of the language.
If you access ```part-1/scanner.l```, you'll see the most basic lexer scanner of all.
It just has some simple rules that establish what is part of the language.
This scanner is entirely lexical, with no syntactic or semantic context.
Still, you'll need ```flex``` and can generate a executable file/test with ```make``` and ```make test```.

### Part 2 [Sep 2018]

In this part, ```bison``` was introduced to perform the syntactic analysis.
If you access ```part-2/parser.y```, you'll see that now some syntactic rules were done to give some sense to the inputs.
Still, no semantic analysis is performed, so something like ```int x = true;``` is accepted.
Again, ```make``` and ```make test``` do the tricks for these one.

### Part 3 [IN DEVELOPMENT]

In this part, the AST will be build together with the syntactic analysis.
For this, structs like the ones ```tree.h``` and ```lexeme.h``` were developed.
Also, values were added to tokens on ```scanner.l``` and tree construction functions were used on ```parser.y```.
I don't need to write again about ```make``` and ```make test```.

## Built With

* [Flex](https://www.gnu.org/software/flex/) - The Fast Lexical Analyzer
* [Bison](https://www.gnu.org/software/bison/) - A LALR(1) general-purpose parser generator
* [GCC](https://www.gnu.org/software/gcc/) - The GNU Compiler Collection

## Contributing

If you want to contribute to this compiler project, just e-mail me at ```camargodev@gmail.com```.
Although this was developed for a college course, it has a huge potential for learning.


## Authors

* **João Vitor de Camargo** - *Developer*
* **Marcellus Farias** - *Developer* 

## Acknowledgments

* This project was developed under the counseling of UFRGS' professor Lucas Schnorr.

