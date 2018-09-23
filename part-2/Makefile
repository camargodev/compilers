# João Vitor de Camargo (274722) e Marcellus Farias (281984)

all: parser.y scanner.l main.c
	bison -d parser.y --report-file=report
	flex scanner.l
	gcc -c lex.yy.c parser.tab.c
	gcc -o etapa2 lex.yy.o parser.tab.o main.c -lfl

test: test.txt etapa2
	cat test.txt | ./etapa2 

clean:
	rm -f etapa2
	rm -f parser.tab.c
	rm -f parser.tab.o
	rm -f parser.tab.h
	rm -f parser.output
	rm -f lex.yy.o
	rm -f lex.yy.c
	rm -f report

