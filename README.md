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
Just run ```make``` to generate the necessary files. Visiting the ```Makefile``` of each folder will show you how to test.

### Part 1 [Aug 2018]

A lexer scanner was developed to accept the tokens of the language.
This scanner uses only ```flex``` and is available at ```part-1/scanner.l```.

### Part 2 [Sep 2018]

In this part, ```bison``` was introduced to perform the syntactic analysis.
If you access ```part-2/parser.y```, you'll see that now some syntactic rules were done to give some sense to the inputs.
Still, no semantic analysis is performed, so something like ```int x = "hello";``` is accepted.

### Part 3 [Oct 2018]

In this part, the AST (Abstract Syntax Tree) is build within the syntactic analysis.
For this, structs like the ones ```tree.h``` and ```lexeme.h``` were developed.
Also, values were added to tokens on ```scanner.l``` and tree construction functions were used on ```parser.y```.

### Part 4 [Oct 2018]

In this part, the semantic analysis was added.
During the syntactic analysis, the tokens were semanticly verified.
This part will prevent the use of undeclared identifiers or double declaration of a identifier, for example.
A lot of structs were developed, but the most important are on ```table.h```, like ```table_stack``` that represents a stack of symbol tables.
Also, nodes for ```tree.h``` now have types (like a expression node) and conversions are marked on nodes.

### Part 5 [Nov 2018]

In this part, we started the code generation from "The Language" to [ILOC](https://en.wikipedia.org/wiki/Intermediate_representation#cite_note-6).
Also, the language was trully simplfied and we only deal with integers now.
The commands for which code is "generated" are:
* Variable declaration, ie ```x int;``` (global vars), ```int x;``` and ```int x <= 1;``` (local var with/without inicialization).
* If conditionals, ie ```if (bool) then {...};``` and ```if (bool) then {...} else {...};```.
* While/Do-While, ie ```do {...} while (bool);``` and ```while (bool) do {...};```

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

