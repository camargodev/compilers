# João Vitor de Camargo (274722) e Marcellus Farias (281984)

all: scanner.l tokens.h main.c
	flex scanner.l
	gcc -o etapa1 lex.yy.c main.c

test: test.txt etapa1
	cat test.txt | ./etapa1 > test-result.txt
	diff test-result.txt test-answer.txt

clean:
	rm -f etapa1
	rm -f lex.yy.c
	rm -f test-result.txt

