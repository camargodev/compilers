# João Vi4tor de Camargo (274722) e Marcellus Farias (281984)

all: parser.y scanner.l main.c
	bison -d parser.y --report-file=report
	flex scanner.l
	gcc -g -c lex.yy.c parser.tab.c tree.c table.c main.c error_helper.c conversions.c debug_print.c
	gcc -g -o etapa4 lex.yy.o parser.tab.o tree.o table.o main.o error_helper.o conversions.o debug_print.o -lfl

tst: ./test.sh tests/results.txt ./etapa4
	./test.sh
	diff tests/results.txt tests/tempresults.txt
	echo $?

syntest: ./etapa4 syntest.txt
	./etapa4 < syntest.txt > eq1.txt
	./etapa4 < eq1.txt > eq2.txt
	diff eq1.txt eq2.txt
	echo $?

clean:
	rm -f etapa4
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
	rm -f conversions.o
	rm -f error_helper.o
	rm -f .parser.y.swp
	rm -f tests/tempresults.txt
	rm -f debug_print.o
	

