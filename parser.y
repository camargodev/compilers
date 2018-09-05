%{
	#include <stdio.h>
	
	extern int yylineno;

	int yylex(void);
	void yyerror (char const *s);
%}

%verbose

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
var     : type TK_IDENTIFICADOR
bool    : TK_LIT_TRUE | TK_LIT_FALSE
signal  : '+' | '-' | %empty
//pos_int : '+' TK_LIT_INT | TK_LIT_INT
//lits 	: TK_LIT_INT | TK_LIT_FLOAT | bool | TK_LIT_CHAR | TK_LIT_STRING

non_num_lits 	: bool | TK_LIT_CHAR | TK_LIT_STRING

new_type    : TK_PR_CLASS TK_IDENTIFICADOR '[' param_begin ';'
param_begin : scope  param_body | param_body
param_body  : var param_end
param_end   : ':' param_begin | ']' 

global_var       : TK_IDENTIFICADOR globar_var_begin 
globar_var_begin : TK_PR_STATIC type global_var_body | type global_var_body
global_var_body  : ';' | '[' global_var_end 
global_var_end   : artm ']' ';' 

func            : TK_PR_STATIC func_begin | func_begin
func_begin       : type TK_IDENTIFICADOR '(' func_params
func_params     : ')' func_body | var func_params_end
func_params_end : ')' func_body | ',' var func_params_end
func_body       : '{' cmd_block 

cmd_block	: '}' | cmd cmd_block 
cmd 		: TK_PR_STATIC local_var_begin | TK_PR_CONST local_var_body
cmd 		: type TK_IDENTIFICADOR local_var_end | TK_IDENTIFICADOR cmd_id_fix

cmd_id_fix	: TK_IDENTIFICADOR local_var_end | '[' artm ']' attr_field 
cmd_id_fix	: '$' TK_IDENTIFICADOR attr_body | attr_body

local_var_begin : TK_PR_CONST local_var_body | local_var_body
local_var_body  : type TK_IDENTIFICADOR local_var_end
local_var_end   : ';' | TK_OC_LE var_attr ';'

var_attr  		: TK_IDENTIFICADOR var_id_attr_fix | non_num_lits
var_attr 		: TK_LIT_INT var_attr_fix | TK_LIT_FLOAT var_attr_fix
var_attr_fix 	: op artm | %empty
var_id_attr_fix : artm_id_fix var_attr_fix

attr_field	: '$' TK_IDENTIFICADOR attr_body | attr_body
attr_body   : '=' var_attr ';'

op 		: '+' | '-' | '*' | '/'

artm 	 				: signal artm_vals
artm_vals 				: TK_LIT_FLOAT | TK_LIT_INT | TK_IDENTIFICADOR artm_id_fix | '(' artm ')'
artm_id_fix 			: '[' artm ']' artm_id_field |  artm_id_field | '(' artm_func_params
artm_func_params     	: ')' | artm artm_func_params_end | '.' artm_func_params_end
artm_func_params_end 	: ')' | ',' artm artm_func_params_end | '.' artm_func_params_end
artm_id_field 			: '$' TK_IDENTIFICADOR | %empty
artm 					: artm op artm

%%

void yyerror(char const *s)
{
    fprintf(stderr,"Error | Line: %d\n%s\n", yylineno, s);
}