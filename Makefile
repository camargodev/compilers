# João Vitor de Camargo (274722) e Marcellus Farias (281984)

all: parser.y scanner.l main.c
	bison -d parser.y --report-file=report
	flex scanner.l
	gcc -c lex.yy.c parser.tab.c
	gcc -o parser lex.yy.o parser.tab.o main.c -lfl

test: test.txt parser
	cat test.txt | ./parser 

clean:
	rm -f parser
	rm -f parser.tab.c
	rm -f parser.tab.o
	rm -f parser.tab.h
	rm -f lex.yy.o
	rm -f lex.yy.c

