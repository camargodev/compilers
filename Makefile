etapa1: lex.yy.c
	gcc -o etapa1 lex.yy.c
lex.yy.c: scanner.l
	flex scanner.l
