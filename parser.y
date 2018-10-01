%{
	// João Vitor de Camargo (274722) e Marcellus Farias (281984)
	#include <stdio.h>
	#include <stdlib.h>
	#include "tree.h"
	#include "lexeme.h"
	
	extern int yylineno;
	extern void* arvore;
	extern struct Lexeme **last_token; 

	extern struct Lexeme **errorsArray;

	int yylex(void);
	void yyerror(char const *s);
%}

%verbose
%define parse.error verbose

%union {
	struct Lexeme* valor_lexico;
	struct node* node;
}

%token <valor_lexico> TK_PR_INT
%token <valor_lexico> TK_PR_FLOAT
%token <valor_lexico> TK_PR_BOOL
%token <valor_lexico> TK_PR_CHAR
%token <valor_lexico> TK_PR_STRING
%token <valor_lexico> TK_PR_IF
%token <valor_lexico> TK_PR_THEN
%token <valor_lexico> TK_PR_ELSE
%token <valor_lexico> TK_PR_WHILE
%token <valor_lexico> TK_PR_DO
%token <valor_lexico> TK_PR_INPUT
%token <valor_lexico> TK_PR_OUTPUT
%token <valor_lexico> TK_PR_RETURN
%token <valor_lexico> TK_PR_CONST
%token <valor_lexico> TK_PR_STATIC
%token <valor_lexico> TK_PR_FOREACH
%token <valor_lexico> TK_PR_FOR
%token <valor_lexico> TK_PR_SWITCH
%token <valor_lexico> TK_PR_CASE
%token <valor_lexico> TK_PR_BREAK
%token <valor_lexico> TK_PR_CONTINUE
%token <valor_lexico> TK_PR_CLASS
%token <valor_lexico> TK_PR_PRIVATE
%token <valor_lexico> TK_PR_PUBLIC
%token <valor_lexico> TK_PR_PROTECTED
%token <valor_lexico> TK_OC_LE
%token <valor_lexico> TK_OC_GE
%token <valor_lexico> TK_OC_EQ
%token <valor_lexico> TK_OC_NE
%token <valor_lexico> TK_OC_AND
%token <valor_lexico> TK_OC_OR
%token <valor_lexico> TK_OC_SL
%token <valor_lexico> TK_OC_SR
%token <valor_lexico> TK_OC_FORWARD_PIPE
%token <valor_lexico> TK_OC_BASH_PIPE
%token <valor_lexico> TK_LIT_INT
%token <valor_lexico> TK_LIT_FLOAT
%token <valor_lexico> TK_LIT_FALSE
%token <valor_lexico> TK_LIT_TRUE
%token <valor_lexico> TK_LIT_CHAR
%token <valor_lexico> TK_LIT_STRING
%token <valor_lexico> TK_IDENTIFICADOR
%token <valor_lexico> TOKEN_ERRO
%token <valor_lexico> ',' ';' ':' '(' ')' '{' '}' '[' ']' '+' '-' '|' '?' '*' '/' '<' '>' '=' '!' '&' '%' '#' '^' '.' '$'

%type <node> programa 

%type <node> start
%type <node> type
%type <node> scope
%type <node> var 
%type <node> types
%type <node> bool
%type <node> pipe
%type <node> new_type 
%type <node> param_begin
%type <node> param_body
%type <node> param_end
%type <node> global_var
%type <node> global_var_vec
%type <node> globar_var_begin
%type <node> global_var_type
%type <node> index
%type <node> func
%type <node> func_begin
%type <node> func_params
%type <node> func_params_end
%type <node> func_body
%type <node> cmd_block
%type <node> cmd
%type <node> input
%type <node> output
%type <node> output_vals
%type <node> if_then
%type <node> else
%type <node> while
%type <node> do_while
%type <node> continue
%type <node> break
%type <node> return
%type <node> for
%type <node> cmd_for
%type <node> for_fst_list
%type <node> for_scd_list
%type <node> foreach
%type <node> foreach_list
%type <node> switch
%type <node> case
%type <node> cmd_id_fix
%type <node> static_var		
%type <node> const_var
%type <node> var_end
%type <node> var_lit
%type <node> attr
%type <node> piped_expr
%type <node> bin_op
%type <node> un_op
%type <node> not_null_un_op
%type <node> expr
%type <node> expr_begin
%type <node> expr_vals
%type <node> piped
%type <node> id_seq
%type <node> id_seq_field
%type <node> id_seq_field_vec
%type <node> id_seq_simple
%type <node> func_call_params
%type <node> func_call_params_body
%type <node> func_call_params_end

%start programa

%%

/*
	The rules are basically always the same.
	First token = new_node($$);
	Other tokens = children of the first token;
	For the children:
	when is a really a token = add_node($$, new node($x))
	when is another rule = add_node($$, $x),
		because the new_node will be created on the
		rule itself. Follow the pattern.
*/

programa :  start  
			{ 
				$$ = $1;
				arvore = $$;
			}

start : new_type start
			{ 
				$$ = $1; 
				add_node($$, $2); 				
			}
		| global_var start 
			{ 
				$$ = $1; 
				add_node($$, $2); 
			}
		| func start 
			{ 
				$$ = $1; 
				add_node($$, $2); 
			}
		| %empty 
			{ 
				$$ = new_node(NULL); 				
			}

type    : TK_PR_INT
			{ 
				$$ = new_node($1); 				
			}
		| TK_PR_FLOAT
			{ 
				$$ = new_node($1);
			}
		| TK_PR_BOOL
			{ 
				$$ = new_node($1); 
			}
		| TK_PR_CHAR
			{ 
				$$ = new_node($1);
			}
		| TK_PR_STRING
			{ 
				$$ = new_node($1); 
			}

scope   : TK_PR_PRIVATE
			{ 
				$$ = new_node($1); 
			}
		| TK_PR_PUBLIC
			{ 
				$$ = new_node($1); 
			}
		| TK_PR_PROTECTED
			{ 
				$$ = new_node($1); 
			}

var     : TK_PR_CONST types TK_IDENTIFICADOR
			{ 	
				$$ = new_node($1); 
				add_node($$, $2);
				add_node($$, new_node($3));
			}
		| types TK_IDENTIFICADOR
			{ 	
				$$ = $1; 
				add_node($$, new_node($2));
			}

types 	: type
			{ 
				$$ = $1; 
			}
		| TK_IDENTIFICADOR
			{ 
				$$ = new_node($1); 
			}

bool    : TK_LIT_TRUE
			{ 
				$$ = new_node($1); 
			}
		| TK_LIT_FALSE
			{ 
				$$ = new_node($1); 
			}

pipe 	: TK_OC_FORWARD_PIPE
			{ 
				$$ = new_node($1); 
			}
		| TK_OC_BASH_PIPE
			{ 
				$$ = new_node($1); 
			}

new_type    : TK_PR_CLASS TK_IDENTIFICADOR '[' param_begin ';'
				{	
					$$ = new_node($1);
					add_node($$, new_node($2));
					add_node($$, new_node($3));
					add_node($$, $4);
					add_node($$, new_node($5));
				}

param_begin : scope param_body
				{ 	
					$$ = $1;
					add_node($$, $2);
				}
			| param_body
				{	
					$$ = $1; 
				}

param_body  : type TK_IDENTIFICADOR param_end
				{	
					$$ = $1;
					add_node($$, new_node($2));
					add_node($$, $3);
				}

param_end   : ':' param_begin
				{	
					$$ = new_node($1);
					add_node($$, $2);
				}
			| ']'
				{	
					$$ = new_node($1);
				} 

global_var       : TK_IDENTIFICADOR global_var_vec 
					{	
						$$ = new_node($1);
						add_node($$, $2);
					}

global_var_vec  : '[' index ']' globar_var_begin
					{	
						$$ = new_node($1);
						add_node($$, $2);
						add_node($$, new_node($3));
						add_node($$, $4);
					}
				| globar_var_begin
					{
						$$ = $1;
					}

globar_var_begin	: TK_PR_STATIC global_var_type
						{
							$$ = new_node($1);
							add_node($$, $2);
						}
					| global_var_type
						{
							$$ = $1;
						}

global_var_type	: type ';'
					{
						$$ = $1;
						add_node($$, new_node($2));
					}
				| TK_IDENTIFICADOR ';'
					{
						$$ = new_node($1);
						add_node($$, new_node($2));
					}

index	: TK_LIT_INT 
			{
				$$ = new_node($1);
			}
		| '+' TK_LIT_INT
			{
				$$ = new_node($1);
				add_node($$, new_node($2));
			}

func 	: TK_PR_STATIC func_begin
			{
				$$ = new_node($1);
				add_node($$, $2);
			}
		| func_begin
			{
				$$ = $1;
			}

func_begin      : type TK_IDENTIFICADOR '(' func_params
					{
						$$ = $1;
						add_node($$, new_node($2));
						add_node($$, new_node($3));
						add_node($$, $4);
					}
				| TK_IDENTIFICADOR TK_IDENTIFICADOR '(' func_params
					{
						$$ = new_node($1);
						add_node($$, new_node($2));
						add_node($$, new_node($3));
						add_node($$, $4);
					}

func_params     : ')' func_body
					{
						$$ = new_node($1);
						add_node($$, $2);
					}
				| var func_params_end
					{
						$$ = $1;
						add_node($$, $2);
					}

func_params_end : ')' func_body
					{
						$$ = new_node($1);
						add_node($$, $2);
					}
				| ',' var func_params_end
					{
						$$ = new_node($1);
						add_node($$, $2);
						add_node($$, $3);
					}

func_body       : '{' cmd_block 
					{
						$$ = new_node($1);
						add_node($$, $2);
					}

cmd_block	: '}' 
				{
					$$ = new_node($1);
				}
			| cmd cmd_block
				{
					$$ = $1;
					add_node($$, $2);
				} 

cmd 		: TK_IDENTIFICADOR cmd_id_fix ';'
					{
						$$ = new_node($1);
						add_node($$, $2);
						add_node($$, new_node($3));
					}
				| TK_PR_STATIC static_var ';'
					{
						$$ = new_node($1);
						add_node($$, $2);
						add_node($$, new_node($3));
					}
				| TK_PR_CONST const_var ';'
					{
						$$ = new_node($1);
						add_node($$, $2);
						add_node($$, new_node($3));
					}
				| type TK_IDENTIFICADOR var_end ';'
					{
						$$ = $1;
						add_node($$, new_node($2));
						add_node($$, $3);
						add_node($$, new_node($4));
					}
				| if_then ';'
					{
						$$ = $1;
						add_node($$, new_node($2));
					}
				| while ';'
					{
						$$ = $1;
						add_node($$, new_node($2));
					}
				| do_while ';'
					{
						$$ = $1;
						add_node($$, new_node($2));
					}
				| continue ';'
					{
						$$ = $1;
						add_node($$, new_node($2));
					}
				| break ';'
					{
						$$ = $1;
						add_node($$, new_node($2));
					}
				| return ';'
					{
						$$ = $1;
						add_node($$, new_node($2));
					}
				| for ';'
					{
						$$ = $1;
						add_node($$, new_node($2));
					}
				| foreach ';'
					{
						$$ = $1;
						add_node($$, new_node($2));
					}
				| switch ';'
					{
						$$ = $1;
						add_node($$, new_node($2));
					}
				| input ';'
					{
						$$ = $1;
						add_node($$, new_node($2));
					}
				| '{' cmd_block ';'
					{
						$$ = new_node($1);
						add_node($$, $2);
						add_node($$, new_node($3));
					}
				| output 
					{
						$$ = $1;
					}
				| case
					{
						$$ = $1;
					}
						
input 		: TK_PR_INPUT expr
				{
					$$ = new_node($1);
					add_node($$, $2);
				}

output 		: TK_PR_OUTPUT expr output_vals
				{
					$$ = new_node($1);
					add_node($$, $2);
					add_node($$, $3);
				}

output_vals : ';'
				{
					$$ = new_node($1);
				}
			| ',' expr output_vals
				{
					$$ = new_node($1);
					add_node($$, $2);
					add_node($$, $3);
				}

if_then 	: TK_PR_IF '(' expr ')'
				TK_PR_THEN '{' cmd_block else
				{
					$$ = new_node($1);
					add_node($$, new_node($2));
					add_node($$, $3);
					add_node($$, new_node($4));
					add_node($$, new_node($5));
					add_node($$, new_node($6));
					add_node($$, $7);
					add_node($$, $8);
				}

else 		: TK_PR_ELSE '{' cmd_block
				{
					$$ = new_node($1);
					add_node($$, new_node($2));
					add_node($$, $3);
				}
			|  %empty
				{
					$$ = new_node(NULL);
				}

while 		: TK_PR_WHILE '(' expr ')'
				TK_PR_DO '{' cmd_block
				{
					$$ = new_node($1);
					add_node($$, new_node($2));
					add_node($$, $3);
					add_node($$, new_node($4));
					add_node($$, new_node($5));
					add_node($$, new_node($6));
					add_node($$, $7);
				}

do_while 	: TK_PR_DO '{' cmd_block
				TK_PR_WHILE '(' expr ')'
				{
					$$ = new_node($1);
					add_node($$, new_node($2));
					add_node($$, $3);
					add_node($$, new_node($4));
					add_node($$, new_node($5));
					add_node($$, $6);
					add_node($$, new_node($7));

				}

continue 	: TK_PR_CONTINUE
				{
					$$ = new_node($1);
				}

break 		: TK_PR_BREAK
				{
					$$ = new_node($1);
				}

return 		: TK_PR_RETURN expr
				{
					$$ = new_node($1);
					add_node($$, $2);
				}

for 		: TK_PR_FOR '(' cmd_for for_fst_list
						expr ':'
						cmd_for for_scd_list
						'{' cmd_block
				{
					$$ = new_node($1);
					add_node($$, new_node($2));
					add_node($$, $3);
					add_node($$, $4);
					add_node($$, $5);
					add_node($$, new_node($6));
					add_node($$, $7);
					add_node($$, $8);
					add_node($$, new_node($9));
					add_node($$, $10);
				}

cmd_for 	: TK_IDENTIFICADOR cmd_id_fix
					{
						$$ = new_node($1);
						add_node($$, $2);
					}
				| type TK_IDENTIFICADOR var_end
					{
						$$ = $1;
						add_node($$, new_node($2));
						add_node($$, $3);
					}
				| TK_PR_STATIC static_var
					{
						$$ = new_node($1);
						add_node($$, $2);
					}
				| TK_PR_CONST const_var
					{
						$$ = new_node($1);
						add_node($$, $2);
					}
				| if_then 
					{
						$$ = $1;
					}
				| while 
					{
						$$ = $1;
					}
				| do_while 
					{
						$$ = $1;
					}
				| continue 
					{
						$$ = $1;
					}
				| break 
					{
						$$ = $1;
					}
				| return
					{
						$$ = $1;
					}
				| for 
					{
						$$ = $1;
					}
				| foreach
					{
						$$ = $1;
					}
				| switch
					{
						$$ = $1;
					}
				| input
					{
						$$ = $1;
					}
				| TK_PR_OUTPUT expr 
					{
						$$ = new_node($1);
						add_node($$, $2);
					}
				| '{' cmd_block 
					{
						$$ = new_node($1);
						add_node($$, $2);
					}

for_fst_list	: ',' cmd_for for_fst_list
					{
						$$ = new_node($1);
						add_node($$, $2);
						add_node($$, $3);
					}
				| ':'
					{
						$$ = new_node($1);
					}

for_scd_list	: ',' cmd_for for_scd_list
					{
						$$ = new_node($1);
						add_node($$, $2);
						add_node($$, $3);
					}
				| ')' 
					{
						$$ = new_node($1);
					}

foreach 	: TK_PR_FOREACH '(' TK_IDENTIFICADOR
							':' expr foreach_list
							'{' cmd_block
					{
						$$ = new_node($1);
						add_node($$, new_node($2));
						add_node($$, new_node($3));
						add_node($$, new_node($4));
						add_node($$, $5);
						add_node($$, $6);
						add_node($$, new_node($7));
						add_node($$, $8);
					}

foreach_list	: ',' expr foreach_list 
					{
						$$ = new_node($1);
						add_node($$, $2);
						add_node($$, $3);
					}
				| ')' 
					{
						$$ = new_node($1);
					}

switch 		: TK_PR_SWITCH '(' expr ')' '{' cmd_block
				{
					$$ = new_node($1);
					add_node($$, new_node($2));
					add_node($$, $3);
					add_node($$, new_node($4));
					add_node($$, new_node($5));
					add_node($$, $6);
				}

case 		: TK_PR_CASE TK_LIT_INT ':'
				{
					$$ = new_node($1);
					add_node($$, new_node($2));
					add_node($$, new_node($3));
				}

cmd_id_fix	: TK_IDENTIFICADOR
				{
					$$ = new_node($1);
				}
			| id_seq_simple attr
				{
					$$ = $1;
					add_node($$, $2);
				}
			| '(' func_call_params piped_expr
				{
					$$ = new_node($1);
					add_node($$, $2);
					add_node($$, $3);
				}

static_var	: TK_PR_CONST const_var
				{
					$$ = new_node($1);
					add_node($$, $2);
				}
			| const_var 
				{
					$$ = $1;
				}
			
const_var	: type TK_IDENTIFICADOR var_end
				{
					$$ = $1;
					add_node($$, new_node($2));
					add_node($$, $3);
				}
			| TK_IDENTIFICADOR TK_IDENTIFICADOR
				{
					$$ = new_node($1);
					add_node($$, new_node($2));
				}

var_end 	: TK_OC_LE var_lit
				{
					$$ = new_node($1);
					add_node($$, $2);
				}
			| %empty
				{
					$$ = new_node(NULL);
				}

var_lit		: TK_IDENTIFICADOR
				{
					$$ = new_node($1);
				}
			| TK_LIT_INT
				{
					$$ = new_node($1);
				}
			| TK_LIT_FLOAT
				{
					$$ = new_node($1);
				}
			| TK_LIT_CHAR
				{
					$$ = new_node($1);
				}
			| TK_LIT_STRING
				{
					$$ = new_node($1);
				}
			| TK_LIT_TRUE
				{
					$$ = new_node($1);
				}
			| TK_LIT_FALSE	
				{
					$$ = new_node($1);
				}

attr 		: '=' expr
				{
					$$ = new_node($1);
					add_node($$, $2);
				}
			| TK_OC_SL expr 
				{
					$$ = new_node($1);
					add_node($$, $2);
				}
			| TK_OC_SR expr 
				{
					$$ = new_node($1);
					add_node($$, $2);
				}
			| pipe un_op TK_IDENTIFICADOR id_seq piped_expr 
				{
					$$ = $1;
					add_node($$, $2);
					add_node($$, new_node($3));
					add_node($$, $4);
					add_node($$, $5);
				}

piped_expr	: pipe un_op TK_IDENTIFICADOR id_seq piped_expr
				{
					$$ = $1;
					add_node($$, $2);
					add_node($$, new_node($3));
					add_node($$, $4);
					add_node($$, $5);
				}
			| %empty 
				{
					$$ = new_node(NULL);
				}

bin_op			: '+' 
					{
						$$ = new_node($1);
					}
				| '-' 
					{
						$$ = new_node($1);
					}
				| '*' 
					{
						$$ = new_node($1);
					}
				| '/' 
					{
						$$ = new_node($1);
					}
				| '%'
					{
						$$ = new_node($1);
					}
				| '^' 
					{
						$$ = new_node($1);
					}
				| '|' 
					{
						$$ = new_node($1);
					}
				| '&' 
					{
						$$ = new_node($1);
					}
				| '>' 
					{
						$$ = new_node($1);
					}
				| '<'
					{
						$$ = new_node($1);
					}
				| TK_OC_AND 
					{
						$$ = new_node($1);
					}
				| TK_OC_OR 
					{
						$$ = new_node($1);
					}
				| TK_OC_LE
					{
						$$ = new_node($1);
					}
				| TK_OC_NE 
					{
						$$ = new_node($1);
					}
				| TK_OC_EQ 
					{
						$$ = new_node($1);
					}
				| TK_OC_GE
					{
						$$ = new_node($1);
					}

un_op 			: not_null_un_op un_op
					{
						$$ = $1;
						add_node($$, $2);
					}
				| %empty
					{
						$$ = new_node(NULL);
					}

not_null_un_op  : '+' 
					{
						$$ = new_node($1);
					}
				| '-'
					{
						$$ = new_node($1);
					} 
				| '!'
					{
						$$ = new_node($1);
					} 
				| '&'
					{
						$$ = new_node($1);
					} 
				| '*'
					{
						$$ = new_node($1);
					} 
				| '?'
					{
						$$ = new_node($1);
					} 
				| '#'
					{
						$$ = new_node($1);
					}

expr 			: un_op expr_vals expr_begin
					{
						$$ = $1;
						add_node($$, $2);
						add_node($$, $3);
					}

expr_begin 		: bin_op expr
					{
						$$ = $1;
						add_node($$, $2);
					}
				| '?' expr ':' expr
					{
						$$ = new_node($1);
						add_node($$, $2);
						add_node($$, new_node($3));
						add_node($$, $4);
					} 
				| %empty
					{
						$$ = new_node(NULL);
					}

expr_vals		: TK_LIT_FLOAT
					{
						$$ = new_node($1);
					}
				| TK_LIT_INT
					{
						$$ = new_node($1);
					}
				| TK_IDENTIFICADOR id_seq piped 
					{
						$$ = new_node($1);
						add_node($$, $2);
						add_node($$, $3);
					}
				| TK_LIT_CHAR 
					{
						$$ = new_node($1);
					}
				| TK_LIT_STRING 
					{
						$$ = new_node($1);
					}
				|'(' expr ')' 
					{
						$$ = new_node($1);
						add_node($$, $2);
						add_node($$, new_node($3));
					}
				| bool
					{
						$$ = $1;
					}

piped 			: %empty
					{
						$$ = new_node(NULL);
					}
				| pipe TK_IDENTIFICADOR id_seq piped_expr
					{
						$$ = $1;
						add_node($$, new_node($2));
						add_node($$, $3);
						add_node($$, $4);
					}

id_seq			:  id_seq_simple
					{
						$$ = $1;
					}
				| '(' func_call_params
					{
						$$ = new_node($1);
						add_node($$, $2);
					} 

id_seq_field 	: '$' TK_IDENTIFICADOR id_seq_field_vec 
					{
						$$ = new_node($1);
						add_node($$, new_node($2));
						add_node($$, $3);
					}
				| %empty
					{
						$$ = new_node(NULL);
					}

id_seq_field_vec: '[' expr ']'
					{
						$$ = new_node($1);
						add_node($$, $2);
						add_node($$, new_node($3));
					} 
				| %empty
					{
						$$ = new_node(NULL);
					}

id_seq_simple	: '[' expr ']' id_seq_field
					{
						$$ = new_node($1);
						add_node($$, $2);
						add_node($$, new_node($3));
						add_node($$, $4);
					} 
				|  id_seq_field
					{
						$$ = $1;
					}

func_call_params	: ')' 
						{
							$$ = new_node($1);
						}
					| expr func_call_params_body
						{
							$$ = $1;
							add_node($$, $2);
						}
					| '.' func_call_params_body
						{
							$$ = new_node($1);
							add_node($$, $2);
						}

func_call_params_body 	: ')' 
						{
							$$ = new_node($1);
						}
						| ',' func_call_params_end
						{
							$$ = new_node($1);
							add_node($$, $2);
						}

func_call_params_end 	: expr func_call_params_body
							{
								$$ = $1;
								add_node($$, $2);
							}
						| '.' func_call_params_body
							{
								$$ = new_node($1);
								add_node($$, $2);
							}

%%

void yyerror(char const *s)
{
	/*
	//printf("valor de s: %s\n", s);
	//printf("valor de last_token: %s", (*last_token)->value.v_string);
	
	if ((*last_token) != NULL) {
		//printf("valor de token1 %i\n", (*last_token)->token_type);
		if ((*last_token)->token_type == KEYWORD
			|| (*last_token)->token_type == OPERATOR
			|| (*last_token)->token_type == IDENTIFIER) {
			
			//printf("é identificador\n");
			printf("string %s\n", (*last_token)->value.v_string);

			free((*last_token)->value.v_string);
		} else if ((*last_token)->token_type == LITERAL) {			
			switch ((*last_token)->literal_type) {
				case STRING:
					free((*last_token)->value.v_string);
					
					printf("é string\n");
					
					break;
			}
		}
		free((last_token));

		
		if((*last_token) == NULL)
			printf("é null\n");
		else
			printf("Não é null\n");
	}*/
    fprintf(stderr,"ERROR: line %d - %s\n", yylineno, s);
}








