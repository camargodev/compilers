# João Vitor de Camargo (274722) e Marcellus Farias (281984)

all: parser.y scanner.l main.c
	bison -d parser.y --report-file=report
	flex scanner.l
	gcc -g -c lex.yy.c parser.tab.c tree.c table.c main.c
	gcc -g -o etapa3 lex.yy.o parser.tab.o tree.o table.o main.o -lfl

clean:
	rm -f etapa3
	rm -f parser.tab.c
	rm -f parser.tab.o
	rm -f parser.tab.h
	rm -f parser.output
	rm -f lex.yy.o
	rm -f lex.yy.c
	rm -f report
	rm -f tree
	rm -f tree.o
	rm -f table
	rm -f table.o
	rm -f tree_test.o
	rm -f lexeme.o
	rm -f main.o
	rm -f .parser.y.swp
	rm -f eq1.txt
	rm -f eq2.txt

