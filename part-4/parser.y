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
	Lexeme* func_lexeme = NULL;
	char *func_user_type_name = NULL;
	int func_decl_line;	
	void set_function_type(int type);
	void set_user_type_arg(char *type);
	void set_arg_type(int type);
	void set_func_info(char* name, int is_const);
	void reset_func_vars();
	
	/* Vars and functions for local var creation */

	int local_var_type = UNDECLARED_TYPE;
	int local_var_lit_type = UNDECLARED_TYPE;
	Lexeme* local_var_lexeme = NULL;
	void set_local_var_type(int type);
	void set_local_var_lit_type(int type);
	int came_from_local_var;
	int came_from_attr;

	/* Vars and functions for expressions */

	int debug_expr = TRUE;
	expr_args expr_list;
	void debug_operands(char expr, char * type_operand);
	void debug_expr_vals_char(char expr, char * type_operand);
	void debug_expr_vals_float(float expr, char * type_operand);
	void debug_expr_vals_int(int expr, char * type_operand);
	void debug_expr_vals_string(char * expr, char * type_operand);
	void print_expr_args(); 
	void add_type_to_expr(int type);
	char* expr_id_name = NULL;
	char* id_user_type = NULL;
	int current_expr_type = 0;
	int infer_expr_type();
	int has_numerical();
	int added_field_type = FALSE;
	int came_from_function_call = FALSE;
	int input_helper_flag = FALSE;

	/* Functions for general purposes */

	int can_convert(int type, int attr_type);
	char* get_type_name(int type);
	
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
%type <node> id_for_expr
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
				//free_table_stack(stack);
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

local_var_type  : TK_PR_INT
			{ 
				set_local_var_type(INT);
				$$ = new_node($1); 
			}
		| TK_PR_FLOAT
			{ 
				set_local_var_type(FLOAT);
				$$ = new_node($1); 
			}
		| TK_PR_BOOL
			{ 
				set_local_var_type(BOOL);
				$$ = new_node($1);   
			}
		| TK_PR_CHAR
			{ 
				set_local_var_type(CHAR);
				$$ = new_node($1);  
			}
		| TK_PR_STRING
			{ 
				set_local_var_type(STRING);
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

func_begin      : func_type func_name '(' func_params
					{
						/*add_function(stack, function_type, NULL, num_func_args, function_args, func_lexeme);
						last_added_func = func_lexeme->value.v_string;
						reset_func_vars();*/

						$$ = $1;
						add_node($$, $2);
						add_node($$, new_node($3));
						add_node($$, $4);
					}

				| func_name_user_type '(' func_params
					{


						/*add_function(stack, function_type, func_user_type_name, num_func_args, function_args, func_lexeme);
						last_added_func = func_lexeme->value.v_string;
						reset_func_vars();*/

						$$ = $1;
						add_node($$, new_node($2));
						add_node($$, $3);
					}

func_name_user_type	: TK_IDENTIFICADOR TK_IDENTIFICADOR
				{

					func_decl_line = is_function_declared(stack, $2->value.v_string);
					if (func_decl_line != NOT_DECLARED) {
						printf("ERROR: line %d - function '%s' already declared on line %i\n", 
							yylineno, $2->value.v_string, func_decl_line);
						quit_with_error(ERR_DECLARED);							
					}
					func_lexeme = $2;
					func_user_type_name = $1->value.v_string;

					if(is_declared(stack, $1->value.v_string) == NOT_DECLARED) {
						printf("ERROR: line %d - user type '%s' used on function %s was not previously declared\n", 
							func_decl_line, $1->value.v_string, func_lexeme->value.v_string);
						quit_with_error(ERR_UNDECLARED);
					}

					function_type = USER_TYPE;

					$$ = new_node($1);
					$$ = new_node($1);
					add_node($$, new_node($2));
				}


func_name 	: TK_IDENTIFICADOR
				{
					func_decl_line = is_function_declared(stack, $1->value.v_string);
					if (func_decl_line != NOT_DECLARED) {
						printf("ERROR: line %d - function '%s' already declared on line %i\n", 
							yylineno, $1->value.v_string, func_decl_line);
						quit_with_error(ERR_DECLARED);							
					}
					func_lexeme = $1;
					$$ = new_node($1);
				}

func_params     : ')' add_func func_body
					{
						//printf("\nfuncparam");
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
						add_function(stack, function_type, func_user_type_name, num_func_args, function_args, func_lexeme);
						last_added_func = func_lexeme->value.v_string;
						reset_func_vars();
					}

func_body       : '{' push_table cmd_block 
					{
						//printf("\nfunc body");
						$$ = new_node($1);
						add_node($$, $3);
					}

push_table		: %empty
					{
						push(stack, create_table(last_added_func));
					}

pop_table		: %empty
					{
						pop(stack);
					}

cmd_block	: '}' pop_table
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
						int declaration_line = is_declared(stack, $1->value.v_string);

						if (came_from_function_call == TRUE) {
							if (is_function_declared(stack, $1->value.v_string) == NOT_DECLARED) {
								if (is_user_type(stack, $1->value.v_string) == TRUE) {
									printf("ERROR: line %d - type '%s' used as function\n", 
										yylineno, $1->value.v_string);
									quit_with_error(ERR_USER);
								} else if (declaration_line != NOT_DECLARED) {
									printf("ERROR: line %d - variable '%s' used as function\n", 
										yylineno, $1->value.v_string);
									quit_with_error(ERR_VARIABLE);
								}

								printf("ERROR: line %d - function '%s' was not previously declared\n", 
									yylineno, $1->value.v_string);
								quit_with_error(ERR_UNDECLARED);
							}
							came_from_function_call = FALSE;
						} else if (declaration_line == NOT_DECLARED) {
							printf("ERROR: line %d - '%s' was not previously declared\n", 
								yylineno, $1->value.v_string);
							quit_with_error(ERR_UNDECLARED);							
						}

						if (came_from_local_var == TRUE) {
							int declaration_line = is_declared_on_current_table(stack, local_var_lexeme->value.v_string);
							if(declaration_line != NOT_DECLARED) {
								printf("ERROR: line %d - variable '%s' was already declared on line %i\n",
									yylineno, local_var_lexeme->value.v_string, declaration_line);
								quit_with_error(ERR_DECLARED);
							} else {
								add_local_var(stack, USER_TYPE, $1->value.v_string, FALSE, FALSE, local_var_lexeme);
							}
							came_from_local_var = FALSE;
						}

						if (came_from_attr == TRUE) {
							char *trash;
							int id_type = get_id_type(stack, $1->value.v_string, &trash);
							int expr_type = infer_expr_type();
							if (can_convert(id_type, expr_type) == FALSE) {
								printf("ERROR: line %d - incorrect assignation for variable %s\n",
									yylineno, $1->value.v_string);
								quit_with_error(ERR_WRONG_TYPE);
							}

							//printf("\nO TIPO DEVE SER %s", get_type_name(id_type));
							//printf("\nA EXPR EH %s", get_type_name(infer_expr_type()));
							came_from_attr = FALSE;
						}


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
				| local_var_type TK_IDENTIFICADOR var_end ';'
					{

						int declaration_line = is_declared_on_current_table(stack, $2->value.v_string);
						if(declaration_line != NOT_DECLARED) {
							printf("ERROR: line %d - variable '%s' was already declared on line %i\n",
								yylineno, $2->value.v_string, declaration_line);
							quit_with_error(ERR_DECLARED);
						} else {
							add_local_var(stack, local_var_type, NULL, FALSE, FALSE, $2);
						}

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
						//printf("\nA FUNC ATUAL EH %s", last_added_func);
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
					printf("[INPUT] Teste\n\n");
					
					if((expr_list.has_int
					 	|| expr_list.has_float
					 	|| expr_list.has_char
					 	|| expr_list.has_string
					 	|| expr_list.has_bool) && !input_helper_flag)
					 	{
					 		print_expr_args();
					 		printf("ERROR: input only accepts id types!\n");
					 		//error_code = ERR_WRONG_PAR_INPUT;
					 		exit(ERR_WRONG_PAR_INPUT);
					 	}

					
					$$ = new_node($1);
					add_node($$, $2);
				}

output 		: TK_PR_OUTPUT expr output_vals
				{
					print_expr_args();
					printf("%d\n", expr_list.has_char);
					printf("%d\n", expr_list.has_user_type);
					if(expr_list.has_char
					 	|| expr_list.has_user_type)
					 	{
					 		printf("ERROR: output only accepts arithmetic expr or string!\n");
					 		exit(ERR_WRONG_PAR_OUTPUT);
					 	}

					expr_list = init_expr_args();

					printf("[OUTPUT] Teste\n\n");
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
					int type = infer_expr_type();
					char* user_type_name;
					int expected_type = get_id_type(stack, last_added_func, &user_type_name);
					//printf("\nTYPE EXPR = %s", get_type_name(type));
					//printf("\nEXPECTED TYPE = %s", get_type_name(expected_type));
					if (type != expected_type) {
						if (can_convert(expected_type, type) == FALSE) {
							if (expected_type == USER_TYPE)
								printf("ERROR: line %d - wrong type on return. Expecting %s.\n", 
									yylineno, user_type_name);
							else
								printf("ERROR: line %d - wrong type on return. Expecting %s.\n", 
									yylineno, get_type_name(expected_type));	
							quit_with_error(ERR_WRONG_TYPE);
						}
					}
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
					came_from_local_var = TRUE;
					local_var_lexeme = $1;
					$$ = new_node($1);
				}
			| id_seq_simple attr
				{
					$$ = $1;
					add_node($$, $2);
				}
			| '(' func_call_params piped_expr
				{
					came_from_function_call = TRUE;
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
					int declaration_line = is_declared_on_current_table(stack, $2->value.v_string);
					if(declaration_line != NOT_DECLARED) {
						printf("ERROR: line %d - variable '%s' was already declared on line %i\n",
							yylineno, $2->value.v_string, declaration_line);
						quit_with_error(ERR_DECLARED);
					} else {
						add_local_var(stack, local_var_type, NULL, FALSE, TRUE, $2);
					}

					$$ = $1;
					add_node($$, new_node($2));
					add_node($$, $3);
				}
			| TK_IDENTIFICADOR TK_IDENTIFICADOR
				{
					if (is_declared(stack, $1->value.v_string) == NOT_DECLARED) {
							printf("ERROR: line %d - type '%s' was not previously declared\n", 
								yylineno, $1->value.v_string);
							quit_with_error(ERR_UNDECLARED);							
					}

					int declaration_line = is_declared_on_current_table(stack, $2->value.v_string);
					if(declaration_line != NOT_DECLARED) {
							printf("ERROR: line %d - variable '%s' was already declared on line %i\n",
							yylineno, $2->value.v_string, declaration_line);
						quit_with_error(ERR_DECLARED);
					} else {
						add_local_var(stack, local_var_type, $1->value.v_string, FALSE, TRUE, $2);
					}

					$$ = new_node($1);
					add_node($$, new_node($2));
				}

var_end 	: TK_OC_LE var_lit
				{
					if (local_var_type != local_var_lit_type) {
						if (can_convert(local_var_type, local_var_lit_type) == FALSE) {
							printf("ERROR: line %d - wrong type. Expecting %s, found %s.\n", 
								yylineno, get_type_name(local_var_type), get_type_name(local_var_lit_type));
							quit_with_error(ERR_WRONG_TYPE);
						}
					}

					$$ = new_node($1);
					add_node($$, $2);
				}
			| %empty
				{
					$$ = new_node(NULL);
				}

var_lit		: TK_IDENTIFICADOR
				{
					set_local_var_lit_type(USER_TYPE);
					$$ = new_node($1);
				}
			| TK_LIT_INT
				{
					set_local_var_lit_type(INT);
					$$ = new_node($1);
				}
			| TK_LIT_FLOAT
				{
					set_local_var_lit_type(FLOAT);
					$$ = new_node($1);
				}
			| TK_LIT_CHAR
				{
					set_local_var_lit_type(CHAR);
					$$ = new_node($1);
				}
			| TK_LIT_STRING
				{
					set_local_var_lit_type(STRING);
					$$ = new_node($1);
				}
			| TK_LIT_TRUE
				{
					set_local_var_lit_type(BOOL);
					$$ = new_node($1);
				}
			| TK_LIT_FALSE	
				{
					set_local_var_lit_type(BOOL);
					$$ = new_node($1);
				}

attr 		: '=' expr
				{
					came_from_attr = TRUE;

					//print_expr_args();
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
						debug_operands($1->value.v_char, "BIN_OP");
						$$ = new_node($1);
					}
				| '-' 
					{
						debug_operands($1->value.v_char, "BIN_OP");
						$$ = new_node($1);
					}
				| '*' 
					{
						debug_operands($1->value.v_char, "BIN_OP");
						$$ = new_node($1);
					}
				| '/' 
					{
						debug_operands($1->value.v_char, "BIN_OP");
						$$ = new_node($1);
					}
				| '%'
					{
						debug_operands($1->value.v_char, "BIN_OP");
						$$ = new_node($1);
					}
				| '^' 
					{
						debug_operands($1->value.v_char, "BIN_OP");
						$$ = new_node($1);
					}
				| '|' 
					{
						debug_operands($1->value.v_char, "BIN_OP");
						$$ = new_node($1);
					}
				| '&' 
					{
						debug_operands($1->value.v_char, "BIN_OP");
						$$ = new_node($1);
					}
				| '>' 
					{
						debug_operands($1->value.v_char, "BIN_OP");
						$$ = new_node($1);
					}
				| '<'
					{
						debug_operands($1->value.v_char, "BIN_OP");
						$$ = new_node($1);
					}
				| TK_OC_AND 
					{
						debug_operands($1->value.v_char, "BIN_OP");
						$$ = new_node($1);
					}
				| TK_OC_OR 
					{
						debug_operands($1->value.v_char, "BIN_OP");
						$$ = new_node($1);
					}
				| TK_OC_LE
					{
						debug_operands($1->value.v_char, "BIN_OP");
						$$ = new_node($1);
					}
				| TK_OC_NE 
					{
						debug_operands($1->value.v_char, "BIN_OP");
						$$ = new_node($1);
					}
				| TK_OC_EQ 
					{
						debug_operands($1->value.v_char, "BIN_OP");
						$$ = new_node($1);
					}
				| TK_OC_GE
					{
						debug_operands($1->value.v_char, "BIN_OP");
						$$ = new_node($1);
					}

un_op 			: not_null_un_op un_op
					{
						if(debug_expr)
							printf("[UN_OP] Com operador\n");
						$$ = $1;
						add_node($$, $2);
					}
				| %empty
					{
						if(debug_expr)
							printf("[UN_OP] Empty\n");
						$$ = new_node(NULL);
					}

not_null_un_op  : '+' 
					{
						debug_operands($1->value.v_char, "NOT_NULL_UN_OP");
						$$ = new_node($1);
					}
				| '-'
					{
						debug_operands($1->value.v_char, "NOT_NULL_UN_OP");
						$$ = new_node($1);
					} 
				| '!'
					{
						debug_operands($1->value.v_char, "NOT_NULL_UN_OP");
						$$ = new_node($1);
					} 
				| '&'
					{
						debug_operands($1->value.v_char, "NOT_NULL_UN_OP");
						$$ = new_node($1);
					} 
				| '*'
					{
						debug_operands($1->value.v_char, "NOT_NULL_UN_OP");
						$$ = new_node($1);
					} 
				| '?'
					{
						debug_operands($1->value.v_char, "NOT_NULL_UN_OP");
						$$ = new_node($1);
					} 
				| '#'
					{
						debug_operands($1->value.v_char, "NOT_NULL_UN_OP");
						$$ = new_node($1);
					}

expr 			: un_op expr_vals expr_begin
					{
						if(debug_expr)
							printf("[EXPR] Final\n");
						$$ = $1;
						add_node($$, $2);
						add_node($$, $3);
					}

expr_begin 		: bin_op expr
					{
						if(debug_expr)
							printf("[EXPR_BEGIN] Binop expr\n");
						$$ = $1;
						add_node($$, $2);
					}
				| '?' expr ':' expr
					{
						if(debug_expr)
							printf("[EXPR_BEGIN] Ternário\n");
						$$ = new_node($1);
						add_node($$, $2);
						add_node($$, new_node($3));
						add_node($$, $4);
					} 
				| %empty
					{
						if(debug_expr)
							printf("[EXPR_BEGIN] Empty\n");
						$$ = new_node(NULL);
					}

expr_vals		: TK_LIT_FLOAT
					{
						expr_list.has_float = TRUE;
						debug_expr_vals_float($1->value.v_float, "EXPR_VALS");
						$$ = new_node($1);
					}
				| TK_LIT_INT
					{
						expr_list.has_int = TRUE;
						debug_expr_vals_int($1->value.v_int, "EXPR_VALS");
						$$ = new_node($1);
					}
				| id_for_expr id_seq piped 
					{
						if(debug_expr)
							printf("[EXPR_VALS] TK_ID id_seq piped\n");

						if (added_field_type == FALSE) {
							add_type_to_expr(current_expr_type);
							added_field_type = TRUE;
						}

						int decl_line_as_func = is_function_declared(stack, expr_id_name);
						if (came_from_function_call == TRUE) {
							if (decl_line_as_func == NOT_DECLARED) {
								if (is_user_type(stack, expr_id_name) == TRUE) {
									printf("ERROR: line %d - type '%s' used as function\n", 
										yylineno, expr_id_name);
									quit_with_error(ERR_USER);
								} 
								if (is_declared(stack, expr_id_name) != NOT_DECLARED) {
									printf("ERROR: line %d - variable '%s' used as function\n", 
										yylineno, expr_id_name);
									quit_with_error(ERR_VARIABLE);
								}

								printf("ERffROR: line %d - function '%s' was not previously declared\n", 
									yylineno, expr_id_name);
								quit_with_error(ERR_UNDECLARED);
							}
							came_from_function_call = FALSE;
						} else {
							if (decl_line_as_func != NOT_DECLARED) {
								printf("ERROR: line %d - function '%s' used as variable\n", 
									yylineno, expr_id_name);
								quit_with_error(ERR_FUNCTION);
							}
							if (is_user_type(stack, expr_id_name) == TRUE) {
								printf("ERROR: line %d - type '%s' used as variable\n", 
									yylineno, expr_id_name);
								quit_with_error(ERR_USER);
							}
						}
						expr_list.has_id = TRUE;

						$$ = $1;
						add_node($$, $2);
						add_node($$, $3);
					}
				| TK_LIT_CHAR 
					{
						expr_list.has_char = TRUE;
						debug_expr_vals_char($1->value.v_char, "EXPR_VALS");
						$$ = new_node($1);
					}
				| TK_LIT_STRING 
					{
						expr_list.has_string = TRUE;
						debug_expr_vals_string($1->value.v_string, "EXPR_VALS");
						$$ = new_node($1);
					}
				|'(' expr ')' 
					{
						if(debug_expr)
							("[EXPR_VALUE] ( expr )\n");
						$$ = new_node($1);
						add_node($$, $2);
						add_node($$, new_node($3));
					}
				| bool
					{
						expr_list.has_bool = TRUE;
						$$ = $1;
					}

id_for_expr		: TK_IDENTIFICADOR
					{
						if(debug_expr)
							printf("[ID_FOR_EXPR] ID [%s]\n", $1->value.v_string);
						expr_id_name = $1->value.v_string;
						// IMPORTANT: the method below already fills id_user_type if type = USER_TYPE
						// Otherwise, id_user_type is NULL
						current_expr_type = get_id_type(stack, $1->value.v_string, &id_user_type);

						if(current_expr_type == NOT_DECLARED)
						{
							printf("Erro! Identificador não declarado!\n");
							exit(ERR_UNDECLARED);
						}

						printf("[ID_FOR_EXPR] current_expr_type : %d\n", current_expr_type);

						$$ = new_node($1);
					}

piped 			: %empty
					{
						if(debug_expr)
							printf("[PIPED] Empty\n");
						$$ = new_node(NULL);
					}
				| pipe TK_IDENTIFICADOR id_seq piped_expr
					{
						if(debug_expr)
							printf("[PIPED] pipe TK_IDENTIFICADOR id_seq piped_expr\n");
						$$ = $1;
						add_node($$, new_node($2));
						add_node($$, $3);
						add_node($$, $4);
					}

id_seq			:  id_seq_simple
					{
						if(debug_expr)
							printf("[ID_SEQ] id_seq_simple\n");
						$$ = $1;
					}
				| '(' func_call_params
					{
						if(debug_expr)
							printf("[ID_SEQ] func_call_params\n");
						came_from_function_call = TRUE;
						$$ = new_node($1);
						add_node($$, $2);
					} 

id_seq_field 	: '$' TK_IDENTIFICADOR id_seq_field_vec 
					{
						if(debug_expr)
							printf("[ID_SEQ_FIELD] $ TK_ID [%s] vec\n", $2->value.v_string);

						if (id_user_type == NULL) {
							printf("ERROR: line %d - variable is not a user type\n", yylineno);
							quit_with_error(ERR_VARIABLE);
						}
						int type = get_id_field_type(stack, id_user_type, $2->value.v_string);
						
						if(debug_expr)
							printf("[ID_SEQ_FIELD] type : %d\n", type);
						if(type == NOT_DECLARED || type == NOT_USER_TYPE || type == INVALID_FIELD)
						{
							printf("[ID_SEQ_FIELD] Erro!\n");
							exit(ERR_UNDECLARED);
						}

						add_type_to_expr(type);
						added_field_type = TRUE;
						input_helper_flag = TRUE;
						$$ = new_node($1);
						add_node($$, new_node($2));
						add_node($$, $3);
					}
				| %empty
					{
						if(debug_expr)
							printf("[ID_SEQ_FIELD] empty\n");
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
						if(debug_expr)
							printf("[ID_SEQ_SIMPLE] Com vetor\n");
						$$ = new_node($1);
						add_node($$, $2);
						add_node($$, new_node($3));
						add_node($$, $4);
					} 
				|  id_seq_field
					{
						if(debug_expr)
							printf("[ID_SEQ_SIMPLE] Sem vetor\n");



						$$ = $1;
					}

func_call_params	: ')' 
						{	
							if(debug_expr)
								printf("[FUNC_CALL_PARAMS] ')'\n");
							$$ = new_node($1);
						}
					| expr func_call_params_body
						{
							if(debug_expr)
								printf("[FUNC_CALL_PARAMS] expr func_call_params_body\n");
							$$ = $1;
							add_node($$, $2);
						}
					| '.' func_call_params_body
						{
							if(debug_expr)
								printf("[FUNC_CALL_PARAMS] '.' func_call_params_body\n");
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
	table created_table = create_table(NULL);
	stack->num_tables = 0;
	stack->array = malloc(sizeof(table));
	stack->array[0] = created_table;

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
	func_user_type_name = NULL;
	expr_list = init_expr_args();
}

void set_local_var_type(int type) {
	local_var_type = type;
}

void set_local_var_lit_type(int type) {
	local_var_lit_type = type;
}

int can_convert(int type, int attr_type) {
	/*printf("\nCONVERT");
	printf("\nTYPE 1 = %s", get_type_name(type));
	printf("\nTYPE 2 = %s", get_type_name(attr_type));*/
	if (type == INT || type == FLOAT || type == BOOL) {
		if (attr_type == INT || attr_type == FLOAT || attr_type == BOOL) {
			return TRUE;
		} else {
			return FALSE;
		}
	} else{
		return FALSE;
	}
}

char* get_type_name(int type) {
	switch (type) {
		case INT:
			return "int";
		case FLOAT:
			return "float";
		case BOOL:
			return "bool";
		case CHAR:
			return "char";
		case STRING:
			return "string";
		case USER_TYPE:
			return "user type";
		default:
			return "invalid";
	}
}

void quit_with_error(int error) {
	libera(arvore);
  	arvore = NULL;
  	yylex_destroy();
	free_table_stack(stack);
	exit(error);
}

void debug_operands(char expr, char * type_operand)
{
	if(debug_expr)
		printf("[%s] Signal : %c\n", type_operand, expr);
}

void debug_expr_vals_char(char expr, char * type_operand)
{
	if(debug_expr)
		printf("[%s] VALUE : %c\n", type_operand, expr);
}

void debug_expr_vals_int(int expr, char * type_operand)
{
	if(debug_expr)
		printf("[%s] VALUE : %d\n", type_operand, expr);
}

void debug_expr_vals_float(float expr, char * type_operand)
{
	if(debug_expr)
		printf("[%s] VALUE : %f\n", type_operand, expr);
}

void debug_expr_vals_string(char * expr, char * type_operand)
{
	if(debug_expr)
		printf("[%s] VALUE : %s\n", type_operand, expr);
}

void print_expr_args() {
	printf("\nhas int = %i", expr_list.has_int);
	printf("\nhas float = %i", expr_list.has_float);
	//printf("\nhas id = %i", expr_list.has_id);
	printf("\nhas bool = %i", expr_list.has_bool);
	printf("\nhas chat = %i", expr_list.has_char);
	printf("\nhas str = %i", expr_list.has_string);
	printf("\nhas user type = %i\n", expr_list.has_user_type);
}

void add_type_to_expr(int type) {
	switch (type) {
		case INT:
			expr_list.has_int = TRUE;
			break;
		case FLOAT:
			expr_list.has_float = TRUE;
			break;
		case BOOL:
			expr_list.has_bool = TRUE;
			break;
		case CHAR:
			expr_list.has_char = TRUE;
			break;
		case STRING:
			expr_list.has_string = TRUE;
			break;
		case USER_TYPE:
			expr_list.has_user_type = TRUE;
			break;
	}
}

int infer_expr_type() {
	if (expr_list.has_char) {
		if (has_numerical()) {
			printf("ERROR: line %d - expression mixing char with numericals\n", yylineno);
			quit_with_error(ERR_CHAR_TO_X);
		} else if (expr_list.has_string || expr_list.has_user_type) {
			return INVALID_TYPE;
		} else {
			return CHAR;
		}
	} else if (expr_list.has_string) {
		if (has_numerical()) {
			printf("ERROR: line %d - expression mixing string with numericals\n", yylineno);
			quit_with_error(ERR_STRING_TO_X);
		} else if (expr_list.has_char || expr_list.has_user_type) {
			return INVALID_TYPE;
		} else {
			return STRING;
		}
	} else if (expr_list.has_user_type) {
		if (has_numerical()) {
			printf("ERROR: line %d - expression mixing user type with numericals\n", yylineno);
			quit_with_error(ERR_USER_TO_X);
		} else if (expr_list.has_char || expr_list.has_string) {
			return INVALID_TYPE;
		} else {
			return USER_TYPE;
		}
	} else if (expr_list.has_float) {
		return FLOAT;
	} else if (expr_list.has_int) {
		return INT;
	} else {
		return BOOL;
	}
}

int has_numerical() {
	return expr_list.has_int || expr_list.has_float || expr_list.has_bool;
}
