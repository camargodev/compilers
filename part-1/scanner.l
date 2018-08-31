%{
    // João Vitor de Camargo - 274722
    // Marcellus Farias 	 - 281984
	#include <stdio.h>
	#include "tokens.h"
%}
%option noyywrap
%option yylineno

SPECIAL_CHAR	[,;:(){}\[\]+\-|?*/<>=!&%#^.$]
LETTER			[A-Za-z_]
DIGIT			[0-9]
INT             {DIGIT}+
FLOAT           {DIGIT}+"."{DIGIT}+
NUM 			({INT}|{FLOAT})
ID 				({LETTER}|{DIGIT})

%x 				comment
%x				int_op
%x				float_op

%%

int 		return TK_PR_INT;
bool		return TK_PR_BOOL;
char 		return TK_PR_CHAR;
float		return TK_PR_FLOAT;
string		return TK_PR_STRING;

if 			return TK_PR_IF;
then		return TK_PR_THEN;
else		return TK_PR_ELSE;

do			return TK_PR_DO;
while		return TK_PR_WHILE;

input		return TK_PR_INPUT;
output		return TK_PR_OUTPUT;
return		return TK_PR_RETURN;

const		return TK_PR_CONST;
static		return TK_PR_STATIC;

for 		return TK_PR_FOR;
foreach		return TK_PR_FOREACH;

switch		return TK_PR_SWITCH;
case		return TK_PR_CASE;
break		return TK_PR_BREAK;
continue	return TK_PR_CONTINUE;

class 		return TK_PR_CLASS;
public		return TK_PR_PUBLIC;
private		return TK_PR_PRIVATE;
protected	return TK_PR_PROTECTED;

"<="		return TK_OC_LE;
">="		return TK_OC_GE;
"=="		return TK_OC_EQ;
"!="		return TK_OC_NE;
"||"		return TK_OC_OR;
"<<"		return TK_OC_SL;
">>"		return TK_OC_SR;
"&&"		return TK_OC_AND;
"%|%"		return TK_OC_BASH_PIPE;
"%>%"		return TK_OC_FORWARD_PIPE;

true        return TK_LIT_TRUE;
false       return TK_LIT_FALSE;

{INT}					return TK_LIT_INT;
{FLOAT}					return TK_LIT_FLOAT;
{NUM}(e|E)       		return TK_LIT_FLOAT;

'(\\.|[^'\n\t])'    	return TK_LIT_CHAR;
\"(\\.|[^"\n])*\"  	 	return TK_LIT_STRING;

{SPECIAL_CHAR}			return (int) yytext[0];

[\n]					 

{LETTER}+({ID})*		return TK_IDENTIFICADOR;

"/*"					BEGIN(comment);
<comment>[^*\n]*	   
<comment>"*"+[^*/\n]*   
<comment>\n		   		
<comment>"*"+"/"	   	BEGIN(INITIAL);


"//".*					        
[ ]
[\t]+			
.						return TOKEN_ERRO;



%%

int get_line_number(void)
{
	return yylineno;
}