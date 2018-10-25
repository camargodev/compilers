%{
	// João Vitor de Camargo (274722) e Marcellus Farias (281984)
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "tree.h"
	#include "lexeme.h"
	#include "table.h"
	#include "errors.h"
	#include "error_helper.h"
	#include "conversions.h"
	
	extern int yylineno;
	extern void* arvore;
	table_stack * stack;

	Error* error = NULL;

	int type_args_counter = 0;
	user_type_args *type_arguments;
	char* scope = "public";

	global_var_args global_var;

	function_data function;

	int yylex(void);
	void yyerror(char const *s);

	void init_table_stack();

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

%type <node> set_tree
%type <node> start
%type <node> scope
%type <node> var 
%type <node> func_arg_types
%type <node> field_type
%type <node> var_types
%type <node> func_type
%type <node> local_var_type
%type <node> func_arg_type
%type <node> bool
%type <node> pipe
%type <node> new_type 
%type <node> param_begin
%type <node> param_body
%type <node> param_end
%type <node> global_var
%type <node> global_var_vec
%type <node> global_var_begin
%type <node> global_var_type
%type <node> index
%type <node> func
%type <node> func_begin
%type <node> func_name_user_type
%type <node> func_name
%type <node> func_params
%type <node> func_params_end
%type <node> func_body
%type <node> cmd_block
%type <node> cmd_ident
%type <node> cmd
%type <node> input
%type <node> output
%type <node> output_vals
%type <node> if_then 
%type <node> if_then_expr
%type <node> else
%type <node> while
%type <node> while_expr
%type <node> do_while
%type <node> do_while_expr
%type <node> continue
%type <node> break
%type <node> return
%type <node> for
%type <node> cmd_for
%type <node> for_expr
%type <node> for_fst_list
%type <node> for_scd_list
%type <node> foreach
%type <node> foreach_list
%type <node> foreach_count
%type <node> switch
%type <node> switch_expr
%type <node> case
%type <node> cmd_fix_local_var
%type <node> cmd_fix_attr
%type <node> cmd_fix_call
%type <node> static_var		
%type <node> const_var
%type <node> var_end
%type <node> var_lit
%type <node> attr
%type <node> piped_expr
%type <node> un_op
%type <node> not_null_un_op
%type <node> expr
%type <node> expr_vals
%type <node> id_for_expr
%type <node> piped
%type <node> id_seq
%type <node> id_seq_field
%type <node> id_seq_simple
%type <node> func_call_params
%type <node> func_call_params_body
%type <node> func_call_params_end

%left '*'
%left '+'
%left '-'
%left '/'
%left '%'
%left '^'
%left '|'
%left '&'
%left '>'
%left '<'
%left TK_OC_AND
%left TK_OC_OR
%left TK_OC_LE
%left TK_OC_NE
%left TK_OC_EQ
%left TK_OC_GE


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

programa :  initializer set_tree destroyer
			{}

set_tree	: start 
			{
				$$ = $1;
				arvore = $1;
			}

initializer : %empty
			{
				init_table_stack();
			}

destroyer : %empty
			{
				if (error != NULL) {
					printf("ERROR - line %i = %s\n", error->line, get_error_message(error->error_code));
					exit(error->error_code);
				}
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
			{	$$ = $1; 
				add_node($$, $2); 
			}
		| %empty 
			{ 
				$$ = new_node(NULL); 
			}

local_var_type : TK_PR_INT
			{ 	
				$$ = new_node($1); 
				set_node_type($$, INT);
			}
		| TK_PR_FLOAT
			{ 
				$$ = new_node($1); 
				set_node_type($$, FLOAT);
			}
		| TK_PR_BOOL
			{ 
				$$ = new_node($1);   
				set_node_type($$, BOOL);
			}
		| TK_PR_CHAR
			{ 
				$$ = new_node($1);  
				set_node_type($$, CHAR);
			}
		| TK_PR_STRING
			{ 
				$$ = new_node($1); 
				set_node_type($$, STRING);
			}

field_type : TK_PR_INT
			{ 	
				$$ = new_node($1); 
				set_node_type($$, INT);
			}
		| TK_PR_FLOAT
			{ 
				$$ = new_node($1); 
				set_node_type($$, FLOAT);
			}
		| TK_PR_BOOL
			{ 
				$$ = new_node($1);   
				set_node_type($$, BOOL);
			}
		| TK_PR_CHAR
			{ 
				$$ = new_node($1);  
				set_node_type($$, CHAR);
			}
		| TK_PR_STRING
			{ 
				$$ = new_node($1); 
				set_node_type($$, STRING);
			}

var_types : TK_PR_INT
			{ 	
				$$ = new_node($1); 
				set_node_type($$, INT);
			}
		| TK_PR_FLOAT
			{ 
				$$ = new_node($1); 
				set_node_type($$, FLOAT);
			}
		| TK_PR_BOOL
			{ 
				$$ = new_node($1);   
				set_node_type($$, BOOL);
			}
		| TK_PR_CHAR
			{ 
				$$ = new_node($1);  
				set_node_type($$, CHAR);
			}
		| TK_PR_STRING
			{ 
				$$ = new_node($1); 
				set_node_type($$, STRING);
			}

func_type  :  TK_PR_INT
			{ 	
				$$ = new_node($1); 
				set_node_type($$, INT);
			}
		| TK_PR_FLOAT
			{ 
				$$ = new_node($1); 
				set_node_type($$, FLOAT);
			}
		| TK_PR_BOOL
			{ 
				$$ = new_node($1);   
				set_node_type($$, BOOL);
			}
		| TK_PR_CHAR
			{ 
				$$ = new_node($1);  
				set_node_type($$, CHAR);
			}
		| TK_PR_STRING
			{ 
				$$ = new_node($1); 
				set_node_type($$, STRING);
			}

func_arg_type  :  TK_PR_INT
			{ 	
				$$ = new_node($1); 
				set_node_type($$, INT);
			}
		| TK_PR_FLOAT
			{ 
				$$ = new_node($1); 
				set_node_type($$, FLOAT);
			}
		| TK_PR_BOOL
			{ 
				$$ = new_node($1);   
				set_node_type($$, BOOL);
			}
		| TK_PR_CHAR
			{ 
				$$ = new_node($1);  
				set_node_type($$, CHAR);
			}
		| TK_PR_STRING
			{ 
				$$ = new_node($1); 
				set_node_type($$, STRING);
			}

scope   : TK_PR_PRIVATE
			{ 				
				$$ = new_node($1);
				scope = $1->value.v_string;
			}
		| TK_PR_PUBLIC
			{ 				
				$$ = new_node($1); 
				scope = $1->value.v_string;
			}
		| TK_PR_PROTECTED
			{ 				
				$$ = new_node($1); 
				scope = $1->value.v_string;
			}

var     : TK_PR_CONST func_arg_types TK_IDENTIFICADOR
			{ 	
				$$ = new_node($1); 
				add_node($$, $2);
				add_node($$, new_node($3));

				if (function.args_counter == 0)
					function.function_args = malloc(sizeof(func_args));
				else 
					function.function_args = realloc(function.function_args, (function.args_counter+1)*sizeof(func_args));

				function.function_args[function.args_counter].name = $3->value.v_string;
				function.function_args[function.args_counter].is_const = TRUE;
				function.function_args[function.args_counter].type = $2->type;
				function.function_args[function.args_counter].user_type = $2->user_type;

				function.args_counter++;

				int index;
				for (index = 0; index < function.args_counter-1; index++)
					if (strcmp(function.function_args[index].name, $3->value.v_string) == 0)
						set_error(ERR_DECLARED);

			}
		| func_arg_types TK_IDENTIFICADOR
			{ 	
				$$ = $1; 
				add_node($$, new_node($2));

				if (function.args_counter == 0)
					function.function_args = malloc(sizeof(func_args));
				else 
					function.function_args = realloc(function.function_args, (function.args_counter+1)*sizeof(func_args));

				function.function_args[function.args_counter].name = $2->value.v_string;
				function.function_args[function.args_counter].is_const = FALSE;
				function.function_args[function.args_counter].type = $1->type;
				function.function_args[function.args_counter].user_type = $1->user_type;

				function.args_counter++;

				int index;
				for (index = 0; index < function.args_counter-1; index++)
					if (strcmp(function.function_args[index].name, $2->value.v_string) == 0)
						set_error(ERR_DECLARED);
			}

func_arg_types: func_arg_type
			{ 
				$$ = $1; 

				$$->user_type = NULL;
			}
		| TK_IDENTIFICADOR
			{ 
				$$ = new_node($1); 

				if(is_declared(stack, $1->value.v_string) == NOT_DECLARED)
					set_error(ERR_UNDECLARED);

				$$->type = USER_TYPE;
				$$->user_type = $1->value.v_string;
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

					int declaration_line = is_declared(stack, $2->value.v_string);
					if(declaration_line != NOT_DECLARED) {				
						set_error(ERR_DECLARED);
					} else {
						add_user_type(stack, $2);
					}

					int index;
					for (index = 0; index < type_args_counter; index++)
						add_user_type_properties(stack, $2->value.v_string, type_arguments[index]);

					free(type_arguments);
					type_args_counter = 0;
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

param_body  : field_type TK_IDENTIFICADOR param_end
				{	
					$$ = $1;
					add_node($$, new_node($2));
					add_node($$, $3);

					if (type_args_counter == 0) 
						type_arguments = malloc(sizeof(user_type_args));
					else
						type_arguments = realloc(type_arguments, (type_args_counter+1)*sizeof(user_type_args));
				
					type_arguments[type_args_counter].token_type = $1->type;
					type_arguments[type_args_counter].scope = scope;
					type_arguments[type_args_counter].token_name = $2->value.v_string;

					type_args_counter++;

					int index;
					for (index = 0; index < type_args_counter-1; index++)
						if (strcmp(type_arguments[index].token_name, $2->value.v_string) == 0)
							set_error(ERR_DECLARED);
					
					scope = "public";
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

						int declaration_line = is_declared(stack, $1->value.v_string);
						if (declaration_line != NOT_DECLARED) {
							set_error(ERR_DECLARED);
						} 
						
						global_var.name = $1->value.v_string;
						add_global_var(stack, global_var, $1);

						global_var = initialize_global_var_args();
						
					}

global_var_vec  : '[' index ']' global_var_begin
					{	
						$$ = new_node($1);
						add_node($$, $2);
						add_node($$, new_node($3));
						add_node($$, $4);

						global_var.is_array = TRUE;
					}
				| global_var_begin
					{
						$$ = $1;

						global_var.is_array = FALSE;
					}

global_var_begin	: TK_PR_STATIC global_var_type
						{
							$$ = new_node($1);
							add_node($$, $2);

							global_var.is_static = TRUE;
						}
					| global_var_type
						{
							$$ = $1;

							global_var.is_static = FALSE;
						}

global_var_type	: var_types ';'
					{
						$$ = $1;
						add_node($$, new_node($2));

						global_var.type = $1->type;
					}
				| TK_IDENTIFICADOR ';'
					{
						$$ = new_node($1);
						add_node($$, new_node($2));

						if(is_declared(stack, $1->value.v_string) == NOT_DECLARED)						
							set_error(ERR_UNDECLARED);

						global_var.type = USER_TYPE;
						global_var.user_type = $1->value.v_string;
						global_var.user_type_size = get_user_type_size(stack, $1->value.v_string);
					}

index	: TK_LIT_INT 
			{
				$$ = new_node($1);

				global_var.array_size = $1->value.v_int;
			}
		| '+' TK_LIT_INT
			{
				$$ = new_node($1);
				add_node($$, new_node($2));

				global_var.array_size = $2->value.v_int;
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

func_begin      : func_type func_name '(' func_params
					{
						$$ = $1;
						add_node($$, $2);
						add_node($$, new_node($3));
						add_node($$, $4);

						function.type = $1->type;
					}

				| func_name_user_type '(' func_params
					{

						$$ = $1;
						add_node($$, new_node($2));
						add_node($$, $3);
					}

func_name_user_type	: TK_IDENTIFICADOR TK_IDENTIFICADOR
				{
					$$ = new_node(NULL);
					add_node($$, new_node($1));
					add_node($$, new_node($2));

					int declaration_line = is_declared(stack, $2->value.v_string);
					if (declaration_line != NOT_DECLARED)
						set_error(ERR_DECLARED);

					if(is_declared(stack, $1->value.v_string) == NOT_DECLARED)
						set_error(ERR_UNDECLARED);

					$$->type = USER_TYPE;
					$$->user_type = $1->value.v_string;

					function.lexeme = $2;

					function.type = USER_TYPE;
					function.type_name = $1->value.v_string;

				}


func_name 	: TK_IDENTIFICADOR
				{
					$$ = new_node($1);

					int declaration_line = is_function_declared(stack, $1->value.v_string);
					if (declaration_line != NOT_DECLARED)
						set_error(ERR_DECLARED);

					function.lexeme = $1;
				}

func_params     : ')' add_func func_body
					{
						$$ = new_node($1);
						add_node($$, $3);
					}
				| var func_params_end
					{
						$$ = $1;
						add_node($$, $2);
					}

func_params_end : ')' add_func func_body
					{
						$$ = new_node($1);
						add_node($$, $3);
					}
				| ',' var func_params_end
					{
						$$ = new_node($1);
						add_node($$, $2);
						add_node($$, $3);
					}

add_func 		: %empty
					{
						add_function(stack, function.type, function.type_name, function.args_counter, function.function_args, function.lexeme);

						function.function_args = NULL;
						function.type = 0;
						function.args_counter = 0;
						function.type_name = NULL;
					}

func_body       : '{' push_table cmd_block 
					{
						$$ = new_node($1);
						add_node($$, $3);
					}

push_table		: %empty
					{
						push(stack, create_table());
					}

pop_table		: %empty
					{
						pop(stack);
					}

cmd_block	: '}' pop_table
				{
					$$ = new_node($1);
				}
			| cmd cmd_block
				{
					$$ = $1;
					add_node($$, $2);
				} 

cmd_ident	: TK_IDENTIFICADOR
				{
					$$ = new_node($1);
					$$->type = USER_TYPE;
					$$->user_type = $1->value.v_string;

					int declaration_line = is_declared(stack, $1->value.v_string);
					if(declaration_line == NOT_DECLARED) 
						set_error(ERR_UNDECLARED);
				}

cmd 		: cmd_ident cmd_fix_local_var ';'
					{
						$$ = $1;
						add_node($$, $2);
						add_node($$, new_node($3));
	
						int declaration_line = is_declared_on_current_table(stack, $2->token->value.v_string);
						if(declaration_line != NOT_DECLARED) 
							set_error(ERR_DECLARED);
						else 
							add_local_var(stack, $1->type, $1->user_type, FALSE, FALSE, $2->token);
						

					}
				| cmd_ident cmd_fix_attr ';'
					{
						$$ = $1;
						add_node($$, $2);
						add_node($$, new_node($3));
					}
				| cmd_ident cmd_fix_call ';'
					{
						$$ = $1;
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
				| local_var_type TK_IDENTIFICADOR var_end ';'
					{
						$$ = $1;
						add_node($$, new_node($2));
						add_node($$, $3);
						add_node($$, new_node($4));

						int declaration_line = is_declared_on_current_table(stack, $2->value.v_string);
						if(declaration_line != NOT_DECLARED)
							set_error(ERR_DECLARED);
						else
							add_local_var(stack, $1->type, NULL, FALSE, FALSE, $2);

						printf("\nlocal var type = %i", $1->type);
						printf("\nvar end = %i", $3->type);

						if ($3->type != NOT_DECLARED) 
							if ($1->type == $3->type) {
								if ($1->type == USER_TYPE)
									if (strcmp($1->user_type, $3->user_type) != 0)
										set_error(ERR_WRONG_TYPE);		
							} else 
								if (can_convert($1->type, $3->type) == FALSE)
									set_error(ERR_WRONG_TYPE);
													
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

if_then 	: TK_PR_IF '(' if_then_expr ')'
				TK_PR_THEN '{' push_table cmd_block else
				{

					$$ = new_node($1);
					add_node($$, new_node($2));
					add_node($$, $3);
					add_node($$, new_node($4));
					add_node($$, new_node($5));
					add_node($$, new_node($6));
					add_node($$, $8);
					add_node($$, $9);
				}

if_then_expr : expr 
			{
				$$ = $1;
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

while 		: TK_PR_WHILE '(' while_expr ')'
				TK_PR_DO '{' push_table cmd_block
				{
					$$ = new_node($1);
					add_node($$, new_node($2));
					add_node($$, $3);
					add_node($$, new_node($4));
					add_node($$, new_node($5));
					add_node($$, new_node($6));
					add_node($$, $8);
				}

while_expr	: expr 
				{
					$$ = $1;
				}

do_while 	: TK_PR_DO '{' push_table cmd_block
				TK_PR_WHILE '(' do_while_expr ')'
				{
					$$ = new_node($1);
					add_node($$, new_node($2));
					add_node($$, $4);
					add_node($$, new_node($5));
					add_node($$, new_node($6));
					add_node($$, $7);
					add_node($$, new_node($8));
				}

do_while_expr: expr 
				{
					$$ = $1;
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
						for_expr ':'
						cmd_for for_scd_list
						'{' push_table cmd_block
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
					add_node($$, $11);
				}

for_expr 	: expr
			{	
				$$ = $1;
			}

cmd_for 	: cmd_ident cmd_fix_local_var ';'
					{
						$$ = $1;
						add_node($$, $2);
						add_node($$, new_node($3));
					}
				| cmd_ident cmd_fix_attr ';'
					{
						$$ = $1;
						add_node($$, $2);
						add_node($$, new_node($3));
					}
				| cmd_ident cmd_fix_call ';'
					{
						$$ = $1;
						add_node($$, $2);
						add_node($$, new_node($3));
					}
				| local_var_type TK_IDENTIFICADOR var_end
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
							'{' push_table cmd_block
					{
						$$ = new_node($1);
						add_node($$, new_node($2));
						add_node($$, new_node($3));
						add_node($$, new_node($4));
						add_node($$, $5);
						add_node($$, $6);
						add_node($$, new_node($7));
						add_node($$, $9);
					}

foreach_list	: ',' foreach_count expr foreach_list 
					{
						$$ = new_node($1);
						add_node($$, $3);
						add_node($$, $4);
					}
				| ')' foreach_count
					{
						$$ = new_node($1);
					}

foreach_count	: %empty
					{}

switch 		: TK_PR_SWITCH '(' switch_expr ')' '{' push_table cmd_block
				{
					$$ = new_node($1);
					add_node($$, new_node($2));
					add_node($$, $3);
					add_node($$, new_node($4));
					add_node($$, new_node($5));
					add_node($$, $7);
				}

switch_expr : expr
			{
				$$ = $1;
			}

case 		: TK_PR_CASE expr ':'
				{
					$$ = new_node($1);
					add_node($$, $2);
					add_node($$, new_node($3));
				}

cmd_fix_local_var	: TK_IDENTIFICADOR
				{
					$$ = new_node($1);
				}
cmd_fix_attr		: id_seq_simple attr
				{
					$$ = new_node(NULL);
					add_node($$, $1);
					add_node($$, $2);
					set_node_type($$, $2->type);
				}
cmd_fix_call		: '(' func_call_params piped_expr
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
			
const_var	: local_var_type TK_IDENTIFICADOR var_end
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
					$$ = new_node(NULL);
					add_node($$, new_node($1));
					add_node($$, $2);;
					$$->type = $2->type;
					$$->user_type = $2->user_type;
				}
			| %empty
				{
					$$ = new_node(NULL);
					$$->type = NOT_DECLARED;
					$$->user_type = NULL;
				}

var_lit		: TK_IDENTIFICADOR
				{
					$$ = new_node($1);
					$$->type = USER_TYPE;
					$$->user_type = $1->value.v_string;
				}
			| TK_LIT_INT
				{
					$$ = new_node($1);
					$$->type = INT;
					$$->user_type = NULL;
				}
			| TK_LIT_FLOAT
				{
					$$ = new_node($1);
					$$->type = FLOAT;
					$$->user_type = NULL;
				}
			| TK_LIT_CHAR
				{
					$$ = new_node($1);
					$$->type = CHAR;
					$$->user_type = NULL;
				}
			| TK_LIT_STRING
				{
					$$ = new_node($1);
					$$->type = STRING;
					$$->user_type = NULL;
				}
			| TK_LIT_TRUE
				{
					$$ = new_node($1);
					$$->type = BOOL;
					$$->user_type = NULL;
				}
			| TK_LIT_FALSE	
				{
					$$ = new_node($1);
					$$->type = BOOL;
					$$->user_type = NULL;
				}

attr 		: '=' expr
				{
					$$ = new_node(NULL);
					add_node($$, new_node($1));
					add_node($$, $2);
					set_node_type($$, $2->type);
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

expr 			: expr '+' expr
					{
						$$ = new_node(NULL);
						add_node($$, $1);
						add_node($$, new_node($2));
						add_node($$, $3);
					}
				| expr '-' expr
					{
						$$ = new_node(NULL);
						add_node($$, $1);
						add_node($$, new_node($2));
						add_node($$, $3);
					}
				| expr '*' expr
					{
						$$ = new_node(NULL);
						add_node($$, $1);
						add_node($$, new_node($2));
						add_node($$, $3);
					}
				| expr '/' expr
					{
						$$ = new_node(NULL);
						add_node($$, $1);
						add_node($$, new_node($2));
						add_node($$, $3);
					}
				| expr '%' expr
					{
						$$ = new_node(NULL);
						add_node($$, $1);
						add_node($$, new_node($2));
						add_node($$, $3);
					}
				| expr '^' expr
					{
						$$ = new_node(NULL);
						add_node($$, $1);
						add_node($$, new_node($2));
						add_node($$, $3);
					}
				| expr '|' expr
					{
						$$ = new_node(NULL);
						add_node($$, $1);
						add_node($$, new_node($2));
						add_node($$, $3);
					}
				| expr '&' expr
					{
						$$ = new_node(NULL);
						add_node($$, $1);
						add_node($$, new_node($2));
						add_node($$, $3);
					}
				| expr '>' expr
					{
						$$ = new_node(NULL);
						add_node($$, $1);
						add_node($$, new_node($2));
						add_node($$, $3);
					}
				| expr '<' expr
					{
						$$ = new_node(NULL);
						add_node($$, $1);
						add_node($$, new_node($2));
						add_node($$, $3);
					}
				| expr TK_OC_AND expr
					{
						$$ = new_node(NULL);
						add_node($$, $1);
						add_node($$, new_node($2));
						add_node($$, $3);
					}
				| expr TK_OC_OR expr
					{
						$$ = new_node(NULL);
						add_node($$, $1);
						add_node($$, new_node($2));
						add_node($$, $3);
					}
				| expr TK_OC_LE expr
					{
						$$ = new_node(NULL);
						add_node($$, $1);
						add_node($$, new_node($2));
						add_node($$, $3);
					}
				| expr TK_OC_NE expr
					{
						$$ = new_node(NULL);
						add_node($$, $1);
						add_node($$, new_node($2));
						add_node($$, $3);
					}
				| expr TK_OC_EQ expr
					{
						$$ = new_node(NULL);
						add_node($$, $1);
						add_node($$, new_node($2));
						add_node($$, $3);
					}
				| expr TK_OC_GE expr
					{
						$$ = new_node(NULL);
						add_node($$, $1);
						add_node($$, new_node($2));
						add_node($$, $3);
					}
				| un_op expr_vals
					{
						$$ = new_node(NULL);
						add_node($$, $1);
						add_node($$, $2);
						set_node_type($$, $2->type);
					}

expr_vals		: TK_LIT_FLOAT
					{
						$$ = new_node($1);
						set_node_type($$, FLOAT);
					}
				| TK_LIT_INT
					{
						$$ = new_node($1);
						set_node_type($$, INT);
					}
				| id_for_expr id_seq piped 
					{
						$$ = $1;
						add_node($$, $2);
						add_node($$, $3);
					}
				| TK_LIT_CHAR 
					{
						$$ = new_node($1);
						set_node_type($$, CHAR);
					}
				| TK_LIT_STRING 
					{
						$$ = new_node($1);
						set_node_type($$, STRING);
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
						set_node_type($$, BOOL);
					}

id_for_expr		: TK_IDENTIFICADOR
					{
						$$ = new_node($1);
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

id_seq_field 	: '$' TK_IDENTIFICADOR  
					{
						$$ = new_node($1);
						add_node($$, new_node($2));
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

proccess_expr		: %empty
						{
						}

func_call_params	: ')' 
						{	
							$$ = new_node($1);
						}
					| expr proccess_expr func_call_params_body
						{
							$$ = $1;
							add_node($$, $3);
						}
					| '.' proccess_expr func_call_params_body
						{
							$$ = new_node($1);
							add_node($$, $3);
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

func_call_params_end 	: expr proccess_expr func_call_params_body
							{
								$$ = $1;
								add_node($$, $3);
							}
						| '.' proccess_expr func_call_params_body
							{
								
								$$ = new_node($1);
								add_node($$, $3);
							}

%%

void yyerror(char const *s) {
    fprintf(stderr,"ERROR: line %d - %s\n", yylineno, s);
}

void init_table_stack() {
	stack = (table_stack *) malloc(sizeof(table_stack));
	stack->array = NULL;
	stack->num_tables = NO_TABLES;
	table created_table = create_table();
	stack->num_tables = 0;
	stack->array = malloc(sizeof(table));
	stack->array[0] = created_table;
}

void set_error(int error_code) {
	if(error == NULL) {
		error = new_error(error_code, yylineno);
	}
}