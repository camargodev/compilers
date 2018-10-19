%{
	// João Vitor de Camargo (274722) e Marcellus Farias (281984)
	#include <stdio.h>
	#include <stdlib.h>
	#include "tree.h"
	#include "lexeme.h"
	#include "table.h"
	#include "errors.h"
	
	extern int yylineno;
	extern void* arvore;
	table_stack * stack;

	char * current_token;
	char * current_scope;

	int args_allocated;
	
	/* Vars and functions for user type fields */
	user_type_args * list_user_type_args;
	int num_user_type_args = 0;
	int num_types = 0;

	int has_scope = FALSE;
	int debug_user_type = FALSE;

	void set_field_scope(char* scope);
	void set_field_default_scope();
	void set_field_type(int type);
	void set_field_name(char* name);

	/* Vars and functions for global vars */
	global_var_args globalvar_args;

	int debug_global_var = FALSE;

	void set_global_var_type(int type);
	void set_global_var_user_type(char* type);
	void set_global_var_static(int is_static);
	void set_global_var_as_array(int is_array);
	void set_global_var_name(char* name);
	void set_global_var_size(int size);

	/* Vars and functions for functions declaration */
	int num_func_args = 0;
	func_args *function_args;
	int function_type = UNDECLARED_TYPE;
	char *last_added_func;

	void set_function_type(int type);
	void set_user_type_arg(char *type);
	void set_arg_type(int type);
	void set_func_info(char* name, int is_const);
	void reset_func_vars();

	void init_table_stack();
	int yylex(void);
	void yyerror(char const *s);
	void quit_with_error(int error);

	extern int yylex_destroy(void);

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
%type <node> func_arg_types
%type <node> field_type
%type <node> var_types
%type <node> func_type
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

programa :  initializer start destroyer
			{ 
					
				$$ = $2;
				arvore = $$;

				//print_stack(stack);
			}

initializer : %empty
			{
				init_table_stack();
			}

destroyer : %empty
			{
				free_table_stack(stack);
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

field_type : TK_PR_INT
			{ 	
				if(debug_user_type)
					printf("[TYPE] Token_Type : %s\n", $1->value.v_string);
				set_field_type(INT);
				$$ = new_node($1); 
			}
		| TK_PR_FLOAT
			{ 
				if(debug_user_type)
					printf("[TYPE] Token_Type : %s\n", $1->value.v_string);
				set_field_type(FLOAT);
				$$ = new_node($1); 
			}
		| TK_PR_BOOL
			{ 
				if(debug_user_type)
					printf("[TYPE] Token_Type : %s\n", $1->value.v_string);
				set_field_type(BOOL);
				$$ = new_node($1);   
			}
		| TK_PR_CHAR
			{ 
				if(debug_user_type)
					printf("[TYPE] Token_Type : %s\n", $1->value.v_string);
				set_field_type(CHAR);
				$$ = new_node($1);  
			}
		| TK_PR_STRING
			{ 
				if(debug_user_type)
					printf("[TYPE] Token_Type : %s\n", $1->value.v_string);
				set_field_type(STRING);
				$$ = new_node($1); 
			}

var_types : TK_PR_INT
			{ 
				if(debug_global_var)
					printf("[TYPE] Token_Type : %s\n", $1->value.v_string);
				set_global_var_type(INT);
				$$ = new_node($1); 
			}
		| TK_PR_FLOAT
			{ 
				if(debug_global_var)
					printf("[TYPE] Token_Type : %s\n", $1->value.v_string);
				set_global_var_type(FLOAT);
				$$ = new_node($1); 
			}
		| TK_PR_BOOL
			{ 
				if(debug_global_var)
					printf("[TYPE] Token_Type : %s\n", $1->value.v_string);
				set_global_var_type(BOOL);
				$$ = new_node($1);   
			}
		| TK_PR_CHAR
			{ 
				if(debug_global_var)
					printf("[TYPE] Token_Type : %s\n", $1->value.v_string);
				set_global_var_type(CHAR);
				$$ = new_node($1);  
			}
		| TK_PR_STRING
			{ 
				if(debug_global_var)
					printf("[TYPE] Token_Type : %s\n", $1->value.v_string);
				set_global_var_type(STRING);
				$$ = new_node($1); 
			}

func_type  : TK_PR_INT
			{ 
				//printf("\nfunc_type");
				set_function_type(INT);
				$$ = new_node($1); 
			}
		| TK_PR_FLOAT
			{ 
				set_function_type(FLOAT);
				$$ = new_node($1); 
			}
		| TK_PR_BOOL
			{ 
				set_function_type(BOOL);
				$$ = new_node($1);   
			}
		| TK_PR_CHAR
			{ 
				set_function_type(CHAR);
				$$ = new_node($1);  
			}
		| TK_PR_STRING
			{ 
				set_function_type(STRING);
				$$ = new_node($1); 
			}

func_arg_type  : TK_PR_INT
			{ 
				set_arg_type(INT);
				$$ = new_node($1); 
			}
		| TK_PR_FLOAT
			{ 
				set_arg_type(FLOAT);
				$$ = new_node($1); 
			}
		| TK_PR_BOOL
			{ 
				set_arg_type(BOOL);
				$$ = new_node($1);   
			}
		| TK_PR_CHAR
			{ 
				set_arg_type(CHAR);
				$$ = new_node($1);  
			}
		| TK_PR_STRING
			{ 
				set_arg_type(STRING);
				$$ = new_node($1); 
			}

scope   : TK_PR_PRIVATE
			{ 				
				if(debug_user_type)
					printf("[SCOPE] Value : %s\n", $1->value.v_string);
				set_field_scope($1->value.v_string);
				$$ = new_node($1); 
			}
		| TK_PR_PUBLIC
			{ 				
				if(debug_user_type)
					printf("[SCOPE] Value : %s\n", $1->value.v_string);
				set_field_scope($1->value.v_string);
				$$ = new_node($1); 
			}
		| TK_PR_PROTECTED
			{ 				
				if(debug_user_type)
					printf("[SCOPE] Value : %s\n", $1->value.v_string);
				set_field_scope($1->value.v_string);
				$$ = new_node($1); 
			}

var     : TK_PR_CONST func_arg_types TK_IDENTIFICADOR
			{ 	
				set_func_info($3->value.v_string, TRUE);

				$$ = new_node($1); 
				add_node($$, $2);
				add_node($$, new_node($3));
			}
		| func_arg_types TK_IDENTIFICADOR
			{ 	
				set_func_info($2->value.v_string, FALSE);

				$$ = $1; 
				add_node($$, new_node($2));
			}

func_arg_types: func_arg_type
			{ 
				$$ = $1; 
			}
		| TK_IDENTIFICADOR
			{ 
				if(is_declared(stack, $1->value.v_string) == NOT_DECLARED)
				{							
					printf("ERROR: line %d - user type '%s' was not previously declared\n", yylineno, $1->value.v_string);
					quit_with_error(ERR_UNDECLARED);
				}
				
				set_user_type_arg($1->value.v_string);

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
				
					if(debug_user_type)
						printf("[NEW_TYPE] token : %s\n", $2->value.v_string);
					
					int declaration_line = is_declared(stack, $2->value.v_string);
					if(declaration_line != NOT_DECLARED)
					{
						printf("ERROR: line %d - class '%s' was already declared on line %i\n",
							yylineno, $2->value.v_string, declaration_line);
						quit_with_error(ERR_DECLARED);
					}
					else
					{
						add_user_type(stack, $2);
					}

					int i;
					for(i = 0; i < num_user_type_args; i++)
					{
						add_user_type_properties(stack, $2->value.v_string, list_user_type_args[i]);
					}						

					free(list_user_type_args);
					num_user_type_args = 0;
					num_types = 0;		
					args_allocated = FALSE;			
				}

param_begin : scope param_body
				{ 	
					num_user_type_args++;
					num_types--;
					
					if(debug_user_type)
						printf("[PARAM_BEGIN] Token Com Scope\n");

					$$ = $1;
					add_node($$, $2);					
				}
			| param_body
				{	
					if(debug_user_type)
						printf("[PARAM_BEGIN] Token Sem Scope\n");

					set_field_default_scope();
					num_user_type_args++;
					num_types--;

					$$ = $1; 					
				}

param_body  : field_type TK_IDENTIFICADOR param_end
				{	
					if(debug_user_type)
						printf("[PARAM_BODY] Token_Name : %s, num_types : %d\n", $2->value.v_string, num_types);
					
					set_field_name($2->value.v_string);

					$$ = $1;
					add_node($$, new_node($2));
					add_node($$, $3);
				}

param_end   : ':' param_begin
				{	
					if(debug_user_type)
						printf("\n[PARAM_END]\n");
					
					$$ = new_node($1);
					add_node($$, $2);
				}
			| ']'
				{	
					if(debug_user_type)
						printf("\n[PARAM_END]\n");
					$$ = new_node($1);
				} 

global_var       : TK_IDENTIFICADOR global_var_vec 
					{	
						if(debug_global_var)
							printf("[GLOBAL_VAR] Identificador: %s\n\n", $1->value.v_string);

						int declaration_line = is_declared(stack, $1->value.v_string);
						if (declaration_line != NOT_DECLARED) {
							printf("ERROR: line %d - global variavel '%s' was already declared on line %i\n",
								yylineno, $1->value.v_string, declaration_line);
							quit_with_error(ERR_DECLARED);
						}

						if(debug_global_var)
							printf("[GLOBAL_VAR] Token_Type %d\n", globalvar_args.type);

						set_global_var_name($1->value.v_string);

						add_global_var(stack, globalvar_args, $1);
						globalvar_args = initialize_global_var_args();

						$$ = new_node($1);
						add_node($$, $2);
					}

global_var_vec  : '[' index ']' global_var_begin
					{	
						if(debug_global_var)
							printf("[GLOBAL_VAR_VEC] Is Array\n");

						set_global_var_as_array(TRUE);

						$$ = new_node($1);
						add_node($$, $2);
						add_node($$, new_node($3));
						add_node($$, $4);
					}
				| global_var_begin
					{
						if(debug_global_var)
							printf("[GLOBAL_VAR_VEC] Not array\n");

						set_global_var_as_array(FALSE);

						$$ = $1;
					}

global_var_begin	: TK_PR_STATIC global_var_type
						{
							if(debug_global_var)
								printf("[GLOBAL_VAR_BEGIN] Static\n");

							set_global_var_static(TRUE);

							$$ = new_node($1);
							add_node($$, $2);
						}
					| global_var_type
						{
							if(debug_global_var)
								printf("[GLOBAL_VAR_BEGIN] Not Static\n");

							set_global_var_static(FALSE);

							$$ = $1;
						}

global_var_type	: var_types ';'
					{
						$$ = $1;
						add_node($$, new_node($2));
					}
				| TK_IDENTIFICADOR ';'
					{
						if(is_declared(stack, $1->value.v_string) == NOT_DECLARED)
						{							
							printf("ERROR: line %d - user type '%s' was not previously declared\n", yylineno, $1->value.v_string);
							quit_with_error(ERR_UNDECLARED);
						}

						if(debug_global_var)
							printf("[GLOBAL_VAR_TYPE] token_type : %s\n", $1->value.v_string);

						set_global_var_user_type($1->value.v_string);

						$$ = new_node($1);
						add_node($$, new_node($2));
					}

index	: TK_LIT_INT 
			{
				if(debug_global_var)
					printf("[INDEX] Without '+', Index : %d\n", $1->value.v_int);
				
				set_global_var_size($1->value.v_int);
				$$ = new_node($1);
			}
		| '+' TK_LIT_INT
			{
				if(debug_global_var)
					printf("[INDEX] Without '+', Index : %d\n", $1->value.v_int);
				
				set_global_var_size($2->value.v_int);
				$$ = new_node($1);
				add_node($$, new_node($2));
			}

func 	: TK_PR_STATIC func_begin
			{
				set_func_as_static(stack, last_added_func);
				last_added_func = NULL;

				$$ = new_node($1);
				add_node($$, $2);
			}
		| func_begin
			{
				//printf("\nfunc");
				$$ = $1;
			}

func_begin      : func_type TK_IDENTIFICADOR '(' func_params
					{
						//printf("\nfunc_begin");

						int func_decl_line = is_function_declared(stack, $2->value.v_string);
						if (func_decl_line != NOT_DECLARED) {
							printf("ERROR: line %d - function '%s' already declared on line %i\n", 
								yylineno, $2->value.v_string, func_decl_line);
							quit_with_error(ERR_DECLARED);							
						}

						add_function(stack, function_type, NULL, num_func_args, function_args, $2);
						last_added_func = $2->value.v_string;

						reset_func_vars();

						$$ = $1;
						add_node($$, new_node($2));
						add_node($$, new_node($3));
						add_node($$, $4);
					}

				| TK_IDENTIFICADOR TK_IDENTIFICADOR '(' func_params
					{
						if(is_declared(stack, $1->value.v_string) == NOT_DECLARED) {
							printf("ERROR: line %d - user type '%s' used on function %s was not previously declared\n", 
								yylineno, $1->value.v_string, $2->value.v_string);
							quit_with_error(ERR_UNDECLARED);
						}
						int func_decl_line = is_function_declared(stack, $2->value.v_string);
						if (func_decl_line != NOT_DECLARED) {
							printf("ERROR: line %d - function '%s' already declared on line %i\n", 
								yylineno, $2->value.v_string, func_decl_line);
							quit_with_error(ERR_DECLARED);							
						}

						add_function(stack, USER_TYPE, $1->value.v_string, num_func_args, function_args, $2);
						last_added_func = $2->value.v_string;

						reset_func_vars();

						$$ = new_node($1);
						add_node($$, new_node($2));
						add_node($$, new_node($3));
						add_node($$, $4);
					}

func_params     : ')' func_body
					{
						//printf("\nfuncparam");
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
						//printf("\nfunc body");
						$$ = new_node($1);
						add_node($$, $2);
					}

cmd_block	: '}' 
				{
					//printf("\ncmd block");
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
    fprintf(stderr,"ERROR: line %d - %s\n", yylineno, s);
}

void init_table_stack() {
	
	stack = (table_stack *) malloc(sizeof(table_stack));
	stack->array = NULL;
	stack->num_tables = NO_TABLES;

	//printf("Inicializei stack->numtables\n");
				
	//printf("\tPilha inicializada!\n");

	//printf("Primeiro print_stack\n");
	//print_stack(stack);

				
	//first table will be global scope table
	table table = create_table();
	stack->num_tables++;
	stack->array = malloc(sizeof(table) * (stack->num_tables+1));
	stack->array[0] = table;

	//printf("\tSegundo print_stack\n");
	//print_stack(stack);	
}

void set_field_scope(char *scope) {
	has_scope = TRUE;
	if (args_allocated == TRUE) {
		list_user_type_args = realloc(list_user_type_args, sizeof(user_type_args) * (num_types + 1));
	} else {
		list_user_type_args = malloc(sizeof(user_type_args));
		args_allocated = TRUE;
	}
	list_user_type_args[num_types].scope = scope;
}

void set_field_default_scope() {
	//if(list_user_type_args[num_types - 1].scope == NULL) {
		if(debug_user_type)
			printf("[PARAM_BEGIN] Scope is null\n");
		list_user_type_args[num_types - 1].scope = "PUBLIC";
	//}
}

void set_field_type(int type) {
	if(has_scope == FALSE) {
		if (args_allocated == TRUE) {
			list_user_type_args = realloc(list_user_type_args, sizeof(user_type_args) * (num_types + 1));
		} else {
			list_user_type_args = malloc(sizeof(user_type_args));
			args_allocated = TRUE;
		}
	}
				
	has_scope = FALSE;
	list_user_type_args[num_types].token_type = type;
	num_types++;
}

void set_field_name(char* name) {
	list_user_type_args[num_types - 1].token_name = name;
}

void set_global_var_type(int type) {
	globalvar_args.type = type;
}

void set_global_var_user_type(char* type) {
	globalvar_args.type = USER_TYPE;
	globalvar_args.user_type = type;
	globalvar_args.user_type_size = get_user_type_size(stack, type);
}

void set_global_var_static(int is_static) {
	globalvar_args.is_static = is_static;
}

void set_global_var_as_array(int is_array) {
	globalvar_args.is_array = is_array;
}

void set_global_var_name(char* name) {
	globalvar_args.name = name;
}

void set_global_var_size(int size) {
	globalvar_args.array_size = size;
}

void set_function_type(int type) {
	function_type = type;
}

void set_user_type_arg(char *type) {
	function_args = realloc(function_args, sizeof(func_args) * (num_func_args + 1));
	function_args[num_func_args].type = USER_TYPE;
	function_args[num_func_args].user_type = type;
}

void set_arg_type(int type) {
	function_args = realloc(function_args, sizeof(func_args) * (num_func_args + 1));
	function_args[num_func_args].type = type;
}

void set_func_info(char* name, int is_const) {
	function_args[num_func_args].name = name;
	function_args[num_func_args].is_const = is_const;
	num_func_args++;
}

void reset_func_vars() {
	function_args = NULL;
	function_type = UNDECLARED_TYPE;
	num_func_args = 0;
}

void quit_with_error(int error) {
	libera(arvore);
  	arvore = NULL;
  	yylex_destroy();
	free_table_stack(stack);
	exit(error);
}