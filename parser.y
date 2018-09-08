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

programa :  type_section   

type_section 		: new_type type_section | global_var_section
global_var_section  : global_var global_var_section | func_section
func_section 		: func func_section | %empty

type    : TK_PR_INT | TK_PR_FLOAT | TK_PR_BOOL | TK_PR_CHAR | TK_PR_STRING
scope   : TK_PR_PRIVATE | TK_PR_PUBLIC | TK_PR_PROTECTED
var     : TK_PR_CONST types TK_IDENTIFICADOR | types TK_IDENTIFICADOR
types 	: type | TK_IDENTIFICADOR
bool    : TK_LIT_TRUE | TK_LIT_FALSE
pipe 	: TK_OC_FORWARD_PIPE | TK_OC_BASH_PIPE

new_type    : TK_PR_CLASS TK_IDENTIFICADOR '[' param_begin ';'
param_begin : scope param_body | param_body
param_body  : var param_end
param_end   : ':' param_begin | ']' 

global_var       : TK_IDENTIFICADOR globar_var_begin 
globar_var_begin : TK_PR_STATIC global_var_type | global_var_type
global_var_type	 : type global_var_body | TK_IDENTIFICADOR global_var_body
global_var_body  : ';' | '[' global_var_end 
global_var_end   : expr ']' ';' 

func            : TK_PR_STATIC func_begin | func_begin
func_begin      : type TK_IDENTIFICADOR '(' func_params
					| TK_IDENTIFICADOR TK_IDENTIFICADOR '(' func_params
func_params     : ')' func_body | var func_params_end
func_params_end : ')' func_body | ',' var func_params_end
func_body       : '{' cmd_block 

cmd_block	: '}' | cmd cmd_block 
cmd 		: TK_IDENTIFICADOR cmd_id_fix
				| TK_PR_INPUT expr ';'
				| TK_PR_OUTPUT expr output 
				| TK_LIT_INT expr_begin ';'
				| TK_LIT_FLOAT expr_begin ';'
				| not_null_un_op un_op expr_vals expr_begin ';'
				| TK_PR_IF '(' expr ')' TK_PR_THEN '{' cmd_block else
				| TK_PR_WHILE '(' expr ')' TK_PR_DO '{' cmd_block
				| TK_PR_DO '{' cmd_block TK_PR_WHILE '(' expr ')' ';'
				| TK_PR_CONTINUE ';'
				| TK_PR_BREAK ';'
				| TK_PR_RETURN expr ';'
				| TK_PR_FOR '(' expr for_list ':'
					expr ':' expr for_list ')' '{' cmd_block
				| TK_PR_FOREACH '(' TK_IDENTIFICADOR ':'
					expr for_list  ')' '{' cmd_block
				| TK_PR_SWITCH '(' expr ')' '{' cmd_block

cmd_id_fix	: TK_IDENTIFICADOR local_var_end
				| type local_var_end
				| id_seq attr
				| TK_PR_STATIC local_var_begin
				| TK_PR_CONST local_var_body

else 		: %empty | TK_PR_ELSE '{' cmd_block

output 		: ';' | ',' expr output

for_list	: ',' expr for_list | %empty

attr 	 	: '=' var_attr ';'
				| TK_OC_SL expr ';'
				| TK_OC_SR expr ';'
				| bin_op expr ';'
				| piped_expr ';'

piped_expr	: pipe TK_IDENTIFICADOR id_seq piped_expr | %empty

local_var_begin : TK_PR_CONST local_var_body | local_var_body
local_var_body  : type local_var_end | TK_IDENTIFICADOR local_var_end
local_var_end   : ';' | TK_OC_LE var_attr ';'

var_attr  		: TK_IDENTIFICADOR id_seq var_attr_fix
					| TK_LIT_STRING
					| TK_LIT_CHAR 
					| TK_LIT_INT expr_begin
					| TK_LIT_FLOAT expr_begin
					| not_null_un_op un_op expr_vals expr_begin
					| bool expr_begin

var_attr_fix 	: bin_op expr
					| pipe TK_IDENTIFICADOR id_seq piped_expr
					| %empty

bin_op		: '+' | '-' | '*' | '/' | '%'
				| '^' | '|' | '&' | '>' | '<'
				| TK_OC_AND | TK_OC_OR | TK_OC_LE
				| TK_OC_NE | TK_OC_EQ | TK_OC_GE
un_op 			: not_null_un_op un_op | %empty
not_null_un_op  : '+' | '-' | '!' | '&' | '*' | '?' | '#'

expr 			: un_op expr_vals expr_begin
expr_begin 		: bin_op expr | %empty
expr_vals		: TK_LIT_FLOAT | TK_LIT_INT | TK_IDENTIFICADOR id_seq | '(' expr ')' | bool

id_seq			: '[' expr ']' id_seq_field |  id_seq_field | '(' func_call_params
id_seq_field 	: '$' TK_IDENTIFICADOR | %empty

func_call_params		: ')' | expr func_call_params_body | '.' func_call_params_body
func_call_params_body 	: ')' | ',' func_call_params_end
func_call_params_end 	: expr func_call_params_body | '.' func_call_params_body

%%

void yyerror(char const *s)
{
    fprintf(stderr,"ERROR: line %d - %s\n", yylineno, s);
}