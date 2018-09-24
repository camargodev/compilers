%{
	// João Vitor de Camargo (274722) e Marcellus Farias (281984)
	#include <stdio.h>
	
	extern int yylineno;

	int yylex(void);
	void yyerror (char const *s);
%}

%verbose
%define parse.error verbose

%token TK_PR_INT
%token TK_PR_FLOAT
%token TK_PR_BOOL
%token TK_PR_CHAR
%token TK_PR_STRING
%token TK_PR_IF
%token TK_PR_THEN
%token TK_PR_ELSE
%token TK_PR_WHILE
%token TK_PR_DO
%token TK_PR_INPUT
%token TK_PR_OUTPUT
%token TK_PR_RETURN
%token TK_PR_CONST
%token TK_PR_STATIC
%token TK_PR_FOREACH
%token TK_PR_FOR
%token TK_PR_SWITCH
%token TK_PR_CASE
%token TK_PR_BREAK
%token TK_PR_CONTINUE
%token TK_PR_CLASS
%token TK_PR_PRIVATE
%token TK_PR_PUBLIC
%token TK_PR_PROTECTED
%token TK_OC_LE
%token TK_OC_GE
%token TK_OC_EQ
%token TK_OC_NE
%token TK_OC_AND
%token TK_OC_OR
%token TK_OC_SL
%token TK_OC_SR
%token TK_OC_FORWARD_PIPE
%token TK_OC_BASH_PIPE
%token TK_LIT_INT
%token TK_LIT_FLOAT
%token TK_LIT_FALSE
%token TK_LIT_TRUE
%token TK_LIT_CHAR
%token TK_LIT_STRING
%token TK_IDENTIFICADOR
%token TOKEN_ERRO

%start programa

%locations

%%

programa :  start  

start : new_type start | global_var start | func start | %empty

type    : TK_PR_INT | TK_PR_FLOAT | TK_PR_BOOL | TK_PR_CHAR | TK_PR_STRING
scope   : TK_PR_PRIVATE | TK_PR_PUBLIC | TK_PR_PROTECTED
var     : TK_PR_CONST types TK_IDENTIFICADOR | types TK_IDENTIFICADOR
types 	: type | TK_IDENTIFICADOR
bool    : TK_LIT_TRUE | TK_LIT_FALSE
pipe 	: TK_OC_FORWARD_PIPE | TK_OC_BASH_PIPE

new_type    : TK_PR_CLASS TK_IDENTIFICADOR '[' param_begin ';'
param_begin : scope param_body | param_body
param_body  : type TK_IDENTIFICADOR param_end
param_end   : ':' param_begin | ']' 

global_var       : TK_IDENTIFICADOR global_var_vec 
global_var_vec   : '[' index ']' globar_var_begin | globar_var_begin
globar_var_begin : TK_PR_STATIC global_var_type | global_var_type
global_var_type	 : type ';' | TK_IDENTIFICADOR ';'
index			 : TK_LIT_INT | '+' TK_LIT_INT

func            : TK_PR_STATIC func_begin | func_begin
func_begin      : type TK_IDENTIFICADOR '(' func_params
					| TK_IDENTIFICADOR TK_IDENTIFICADOR '(' func_params
func_params     : ')' func_body | var func_params_end
func_params_end : ')' func_body | ',' var func_params_end
func_body       : '{' cmd_block 

cmd_block	: '}' | cmd cmd_block 
cmd 		: TK_IDENTIFICADOR cmd_id_fix ';'
				| TK_PR_STATIC static_var ';'
				| TK_PR_CONST const_var ';'
				| type TK_IDENTIFICADOR var_end ';'
				| if_then ';'
				| while ';'
				| do_while ';'
				| continue ';'
				| break ';'
				| return ';'
				| for ';'
				| foreach ';'
				| switch ';'
				| input ';'
				| '{' cmd_block ';'
				| output 
				| case
						
input 		: TK_PR_INPUT expr
output 		: TK_PR_OUTPUT expr output_vals
output_vals : ';' | ',' expr output_vals

if_then 	: TK_PR_IF '(' expr ')'
				TK_PR_THEN '{' cmd_block else
else 		: TK_PR_ELSE '{' cmd_block |  %empty

while 		: TK_PR_WHILE '(' expr ')'
				TK_PR_DO '{' cmd_block

do_while 	: TK_PR_DO '{' cmd_block
				TK_PR_WHILE '(' expr ')'

continue 	: TK_PR_CONTINUE
break 		: TK_PR_BREAK
return 		: TK_PR_RETURN expr

for 		: TK_PR_FOR '(' cmd_for for_fst_list
						expr ':'
						cmd_for for_scd_list
						'{' cmd_block

cmd_for 	: TK_IDENTIFICADOR cmd_id_fix
				| type TK_IDENTIFICADOR var_end
				| TK_PR_STATIC static_var
				| TK_PR_CONST const_var
				| if_then 
				| while 
				| do_while 
				| continue 
				| break 
				| return
				| for 
				| foreach
				| switch
				| input
				| TK_PR_OUTPUT expr 
				| '{' cmd_block

for_fst_list: ',' cmd_for for_fst_list | ':'
for_scd_list: ',' cmd_for for_scd_list | ')' 

foreach 	: TK_PR_FOREACH '(' TK_IDENTIFICADOR
							':' expr foreach_list
							'{' cmd_block

foreach_list: ',' expr foreach_list | ')'

switch 		: TK_PR_SWITCH '(' expr ')' '{' cmd_block
case 		: TK_PR_CASE TK_LIT_INT ':'

cmd_id_fix	: TK_IDENTIFICADOR
			| id_seq_simple attr
			| '(' func_call_params piped_expr

static_var	: TK_PR_CONST const_var
			| const_var
			
const_var	: type TK_IDENTIFICADOR var_end
			| TK_IDENTIFICADOR TK_IDENTIFICADOR

var_end 	: TK_OC_LE var_lit
			| %empty

var_lit		: TK_IDENTIFICADOR
			| TK_LIT_INT
			| TK_LIT_FLOAT
			| TK_LIT_CHAR
			| TK_LIT_STRING
			| TK_LIT_TRUE
			| TK_LIT_FALSE	

attr 		: '=' expr
			| TK_OC_SL expr 
			| TK_OC_SR expr 
			| pipe un_op TK_IDENTIFICADOR id_seq piped_expr 

piped_expr	: pipe un_op TK_IDENTIFICADOR id_seq piped_expr | %empty 

bin_op			: '+' | '-' | '*' | '/' | '%'
				| '^' | '|' | '&' | '>' | '<'
				| TK_OC_AND | TK_OC_OR | TK_OC_LE
				| TK_OC_NE | TK_OC_EQ | TK_OC_GE
un_op 			: not_null_un_op un_op | %empty
not_null_un_op  : '+' | '-' | '!' | '&' | '*' | '?' | '#'

expr 			: un_op expr_vals expr_begin
expr_begin 		: bin_op expr | '?' expr ':' expr | %empty
expr_vals		: TK_LIT_FLOAT | TK_LIT_INT | TK_IDENTIFICADOR id_seq piped | TK_LIT_CHAR | TK_LIT_STRING |'(' expr ')' | bool

piped 			: %empty | pipe TK_IDENTIFICADOR id_seq piped_expr

id_seq			:  id_seq_simple | '(' func_call_params 
id_seq_field 	: '$' TK_IDENTIFICADOR id_seq_field_vec | %empty
id_seq_field_vec: '[' expr ']' | %empty

id_seq_simple	: '[' expr ']' id_seq_field |  id_seq_field

func_call_params		: ')' | expr func_call_params_body | '.' func_call_params_body
func_call_params_body 	: ')' | ',' func_call_params_end
func_call_params_end 	: expr func_call_params_body | '.' func_call_params_body

%%

void yyerror(char const *s)
{
    fprintf(stderr,"ERROR: line %d - %s\n", yylineno, s);
}
