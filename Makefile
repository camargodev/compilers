# João Vitor de Camargo (274722) e Marcellus Farias (281984)

all: parser.y scanner.l main.c
	bison -d parser.y --report-file=report
	flex scanner.l
	gcc -c lex.yy.c parser.tab.c
	gcc -o etapa2 lex.yy.o parser.tab.o main.c -lfl

test: tree.c tree_test.c
	gcc tree.c -o tree.o -c
	gcc tree_test.c -o tree_test.o -c
	gcc -o tree tree.o tree_test.o

clean:
	rm -f etapa2
	rm -f parser.tab.c
	rm -f parser.tab.o
	rm -f parser.tab.h
	rm -f parser.output
	rm -f lex.yy.o
	rm -f lex.yy.c
	rm -f report
	rm -f tree
	rm -f tree.o
	rm -f tree_test.o

