comp: lex.yy.c
	gcc -o comp lex.yy.c
lex.yy.c: scanner.l
	flex scanner.l
