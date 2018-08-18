%{
	#include <stdio.h>
	#include "tokens.h"
    #include "main.c"
	int num_lines = 1;
%}

%option noyywrap

SPECIAL_CHAR	[,|;|:|(|)|{|}|\[|\]|+|-|||?|*|/|<|>|=|!|&|%|#|^|.|$]
SIGNAL          [-|+]
LETTER			[A-Za-z_]
DIGIT			[0-9]
INT             {DIGIT}+
FLOAT           {DIGIT}+"."{DIGIT}+


%%

int 							return TK_PR_INT;
float							return TK_PR_FLOAT;
bool							return TK_PR_BOOL;
char 							return TK_PR_CHAR;
string							return TK_PR_STRING;
if 								return TK_PR_IF;
then							return TK_PR_THEN;
else							return TK_PR_ELSE;
while							return TK_PR_WHILE;
do								return TK_PR_DO;
input							return TK_PR_INPUT;
output							return TK_PR_OUTPUT;
return							return TK_PR_RETURN;
const							return TK_PR_CONST;
static							return TK_PR_STATIC;
foreach							return TK_PR_FOREACH;
for 							return TK_PR_FOR;
switch							return TK_PR_SWITCH;
break							return TK_PR_BREAK;
continue						return TK_PR_CONTINUE;
class 							return TK_PR_CLASS;
private							return TK_PR_PRIVATE;
public							return TK_PR_PUBLIC;
protected						return TK_PR_PROTECTED;

"<="							return TK_OC_LE;
">="							return TK_OC_GE;
"=="							return TK_OC_EQ;
"!="							return TK_OC_NE;
"&&"							return TK_OC_AND;
"||"							return TK_OC_OR;
"<<"							return TK_OC_SL;
">>"							return TK_OC_SR;
"%>%"							return TK_OC_FORWARD_PIPE;
"%|%"							return TK_OC_BASH_PIPE;

true 							return TK_LIT_TRUE;
false 							return TK_LIT_FALSE;

{INT}   						return TK_LIT_INT;
{SIGNAL}{INT}                   return TK_LIT_INT;

{FLOAT}                                     return TK_LIT_FLOAT;
{SIGNAL}{FLOAT}                             return TK_LIT_FLOAT;
({INT}|{FLOAT})(e|E){INT}                   return TK_LIT_FLOAT;
{SIGNAL}({INT}|{FLOAT})(e|E){INT}           return TK_LIT_FLOAT;
({INT}|{FLOAT})(e|E){SIGNAL}{INT}           return TK_LIT_FLOAT;
{SIGNAL}({INT}|{FLOAT})(e|E){SIGNAL}{INT}   return TK_LIT_FLOAT;

'.'								return TK_LIT_CHAR;
\".*\"							return TK_LIT_STRING;

{SPECIAL_CHAR}					return (int) yytext[0];

{LETTER}+({LETTER}|{DIGIT})*	return TK_IDENTIFICADOR;


\n 								++num_lines; 

"//".*					        
"/*"({LETTER}|\n)*"*/"          printf("A");
[ ]
[\t]+			

.								return TOKEN_ERRO;

%%

int get_line_number(void)
{
	return num_lines;
}