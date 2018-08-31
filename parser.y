%{
int yylex(void);
void yyerror (char const *s);
%}

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

%%

programa : global_var | new_type | func
type  : TK_PR_INT | TK_PR_FLOAT | TK_PR_BOOL | TK_PR_CHAR | TK_PR_STRING
scope : TK_PR_PRIVATE | TK_PR_PUBLIC | TK_PR_PROTECTED
var   : type TK_IDENTIFICADOR

new_type    : TK_PR_CLASS TK_IDENTIFICADOR '[' param_begin ';'
param_begin : scope  param_body | param_body
param_body  : var param_end
param_end   : ':' param_begin | ']' 

global_var       : TK_IDENTIFICADOR globar_var_begin 
globar_var_begin : TK_PR_STATIC type global_var_body | type global_var_body
global_var_body  : ';' | '[' global_var_end 
global_var_end   : '+' TK_LIT_INT ']' ';' | TK_LIT_INT ']' ';' 

func            : TK_PR_STATIC func_name | func_name
func_name       : type TK_IDENTIFICADOR '(' func_params
func_params     : ')' func_body | var func_params_end
func_params_end : ')' func_body | ',' var func_params_end
func_body       : '{' '}' 

%%

void yyerror(char const *s)
{
	
}
