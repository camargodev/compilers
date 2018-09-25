%{
    // João Vitor de Camargo - 274722
    // Marcellus Farias 	 - 281984
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include "parser.tab.h"
	#include "lexeme.h"
	#include "tree.h"

	int get_line_number(void);
	
	void operator();
	void keyword();
	void identifier();
	void special_char();
	void boolean(int bool_value);
	void integer();
	void floating();
	void character();
	void string();
	void literal();
	void non_literal();
	void config_token();
%}

%option noyywrap
%option yylineno

SPECIAL_CHAR	[,;:(){}\[\]+\-|?*/<>=!&%#^.$]
LETTER			[A-Za-z_]
DIGIT			[0-9]
SIGN            [-|+]
INT             {DIGIT}+
FLOAT           {DIGIT}+"."{DIGIT}+
NUM 			({INT}|{FLOAT})
ID 				({LETTER}|{DIGIT})
EXP				([+-]{INT}|{INT})

%x comment

%%

int 		{ 	keyword(); 
				return TK_PR_INT;
			}
bool		{ 	keyword(); 
				return TK_PR_BOOL;
			}
char 		{ 	keyword(); 
				return TK_PR_CHAR;
			}
float		{ 	keyword(); 
				return TK_PR_FLOAT;
			}
string		{ 	keyword(); 
				return TK_PR_STRING;
			}

if 			{ 	keyword(); 
				return TK_PR_IF;
			}
then		{ 	keyword(); 
				return TK_PR_THEN;
			}
else		{ 	keyword(); 
				return TK_PR_ELSE;
			}

do			{ 	keyword(); 
				return TK_PR_DO;
			}
while		{ 	keyword(); 
				return TK_PR_WHILE;
			}

input		{ 	keyword(); 
				return TK_PR_INPUT;
			}
output		{ 	keyword(); 
				return TK_PR_OUTPUT;
			}
return		{ 	keyword(); 
				return TK_PR_RETURN;
			}

const		{ 	keyword(); 
				return TK_PR_CONST;
			}
static		{ 	keyword(); 
				return TK_PR_STATIC;
			}

for 		{ 	keyword(); 
				return TK_PR_FOR;
			}
foreach		{ 	keyword(); 
				return TK_PR_FOREACH;
			}

switch		{ 	keyword(); 
				return TK_PR_SWITCH;
			}
case		{ 	keyword(); 
				return TK_PR_CASE;
			}
break		{ 	keyword(); 
				return TK_PR_BREAK;
			}
continue	{ 	keyword(); 
				return TK_PR_CONTINUE;
			}

class 		{ 	keyword(); 
				return TK_PR_CLASS;
			}
public		{ 	keyword(); 
				return TK_PR_PUBLIC;
			}
private		{ 	keyword(); 
				return TK_PR_PRIVATE;
			}
protected	{ 	keyword(); 
				return TK_PR_PROTECTED;
			}

"<="		{
				operator();
				return TK_OC_LE;
			}
">="		{
				operator();
				return TK_OC_GE;
			}
"=="		{
				operator();
				return TK_OC_EQ;
			}
"!="		{
				operator();
				return TK_OC_NE;
			}
"||"		{
				operator();
				return TK_OC_OR;
			}
"<<"		{
				operator();
				return TK_OC_SL;
			}
">>"		{
				operator();
				return TK_OC_SR;
			}
"&&"		{
				operator();
				return TK_OC_AND;
			}
"%|%"		{
				operator();
				return TK_OC_BASH_PIPE;
			}
"%>%"		{
				operator();
				return TK_OC_FORWARD_PIPE;
			}

true        {
				boolean(TRUE);
				return TK_LIT_TRUE;
			}
false       {
				boolean(FALSE);
				return TK_LIT_FALSE;
			}


{INT}               	{
							integer();
							return TK_LIT_INT;
						}

{FLOAT}					{	floating();
							return TK_LIT_FLOAT;
						}
{NUM}(e|E){EXP}			{	floating();
							return TK_LIT_FLOAT;
						}

'(\\.|[^'\n\t])'    	{	character();
							return TK_LIT_CHAR;
						}
\"(\\.|[^"\n])*\"  	 	{	string();
							return TK_LIT_STRING;
						}

{SPECIAL_CHAR}			{	special_char();
							return (int) yytext[0];
						}

{LETTER}+({ID})*		{	identifier();
							return TK_IDENTIFICADOR;
						}

[\n]					 

"/*"					BEGIN(comment);
<comment>[^*\n]*        
<comment>"*"+[^*/\n]*   
<comment>\n             
<comment>"*"+"/"        BEGIN(INITIAL);

"//".*					        
[ ]
[\t]+			
.						return TOKEN_ERRO;



%%

int get_line_number(void) {
	return yylineno;
}

void operator() {
	non_literal();
	yylval.valor_lexico->token_type = OPERATOR;
}

void keyword() {
	non_literal();
	yylval.valor_lexico->token_type = KEYWORD;
}

void identifier() {
	non_literal();
	yylval.valor_lexico->token_type = IDENTIFIER;	
}

void special_char() {
	non_literal();
	yylval.valor_lexico->token_type = SPECIAL_CHAR;	
}

void boolean(int bool_value) {
	literal();
	yylval.valor_lexico->literal_type = BOOL;
	yylval.valor_lexico->value.v_bool = bool_value;
}

void integer() {
	literal();
	yylval.valor_lexico->literal_type = INT;
	yylval.valor_lexico->value.v_int = atoi(yytext);
}

void floating() {
	literal();
	yylval.valor_lexico->literal_type = FLOAT;
	yylval.valor_lexico->value.v_float = atof(yytext);
}

void character() {
	literal();
	yylval.valor_lexico->literal_type = CHAR;
	yylval.valor_lexico->value.v_char = yytext[1];
}

void string() {
	literal();
	yylval.valor_lexico->literal_type = STRING;
	yylval.valor_lexico->value.v_string = strdup(yytext);
}

void literal() {
	config_token();
	yylval.valor_lexico->literal_type = NOT_LITERAL;
}

void non_literal() {
	config_token();
	yylval.valor_lexico->literal_type = NOT_LITERAL;
	yylval.valor_lexico->value.v_string = strdup(yytext);
}

void config_token() {
	yylval.valor_lexico = (struct Lexeme*) malloc(sizeof(struct Lexeme));
	yylval.valor_lexico->line_number = yylineno;
}