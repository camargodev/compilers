# João Vi4tor de Camargo (274722) e Marcellus Farias (281984)

all: parser.y scanner.l src/main.c
	bison -d parser.y --report-file=report
	flex scanner.l
	gcc -g -c lex.yy.c parser.tab.c src/tree.c src/table.c src/main.c src/error_helper.c src/conversions.c
	gcc -g -o etapa5 lex.yy.o parser.tab.o tree.o table.o main.o error_helper.o conversions.o -lfl

tst: scripts/test.sh tests/results.txt ./etapa5
	scripts/test.sh
	diff tests/results.txt tests/tempresults.txt
	echo $?

syntest: ./etapa5 syntest.txt
	./etapa4 < syntest.txt > eq1.txt
	./etapa4 < eq1.txt > eq2.txt
	diff eq1.txt eq2.txt
	echo $?

lktst: scripts/leak_test.sh ./etapa4
	scripts/leak_test.sh
	echo $?

iloctst: tests/iloc_test.c include/iloc.h src/iloc.c include/codes.h src/codes.c
	gcc -g -c src/iloc.c src/codes.c
	gcc -g -o iloc tests/iloc_test.c iloc.o codes.o

clean:
	rm -f etapa5
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
	rm -f parser.y.swp
	rm -f tests/tempresults.txt
	rm -f debug_print.o
	rm -f iloc.o
	rm -f codes.o
	rm -f iloc
	

