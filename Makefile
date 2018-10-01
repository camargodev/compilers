# João Vitor de Camargo (274722) e Marcellus Farias (281984)

all: parser.y scanner.l main.c
	bison -d parser.y --report-file=report
	flex scanner.l
	gcc -g -c lex.yy.c parser.tab.c tree.c main.c
	gcc -g -o etapa3 lex.yy.o parser.tab.o tree.o main.o -lfl

test_tree: tree.c tree_test.c
	gcc tree.c -o tree.o -c
	gcc tree_test.c -o tree_test.o -c
	gcc -o tree tree.o lexeme.h tree_test.o 

test: ./etapa3 test.txt
	./etapa3 < test.txt > eq1.txt
	./etapa3 < eq1.txt > eq2.txt
	diff eq1.txt eq2.txt
	echo $?

simple_test: ./etapa3 simple_test.txt
	./etapa3 < simple_test.txt

leak_test: ./etapa3 test.txt
	valgrind --leak-check=full --show-leak-kinds=all -v ./etapa3 < test.txt 

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
	rm -f tree_test.o
	rm -f lexeme.o
	rm -f main.o
	rm -f .parser.y.swp
	rm -f eq1.txt
	rm -f eq2.txt

