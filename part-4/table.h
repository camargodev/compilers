// João Vitor de Camargo
// Marcellus Farias

#include "lexeme.h"
#include "nature.h"
#include "size.h"

#define NO_TABLES -1
#define NO_LINES -1

#define NOT_DECLARED 0
#define NOT_USER_TYPE -1
#define INVALID_FIELD -2

#define INVALID_TYPE -3

typedef struct expr_arguments {
	int has_int;
	int has_float;
	int has_id;
	int has_bool;
	int has_char;
	int has_string;
	int has_user_type;
} expr_args;

typedef struct globar_var_arguments {
	int is_array;
	int array_size;
	int is_static;
	int type;
	char* user_type;
	char* name;
	int user_type_size;
} global_var_args;

typedef struct function_arguments {
	int is_const;
	int type;
	char* user_type;
	char* name;
} func_args;

// The user_type does not have arguments that are also user_types. We must define the access_modification arguments.

#define PRIVATE 0
#define PUBLIC 1
#define PROTECTED 2

typedef struct user_type_arguments {
	char * scope;
	int token_type;
	char * token_name;
} user_type_args;

typedef struct func {
	int type;
	char *type_name;
	int args_counter;
	func_args* function_args;
	Lexeme * lexeme;
} function_data;

typedef struct function_call_arg {
	int type;
	char *user_type;
} func_call_arg;

typedef struct line {
	
	char * token_name; // KEY
	int declaration_line;	// Necessary information
	int nature;
	int token_type;
	int token_size;
	int category;
	char *user_type;
	int is_static;
	int is_const;
	int array_size;
	func_args * function_args;
	user_type_args * user_type_args;
	int num_user_type_args;
	int num_func_args;
	Lexeme *lexeme;

} table_line;

typedef struct table {
	int num_lines;
	//char scope_name;
	table_line *lines;

} table;

table create_table();

typedef struct table_stack {
	int num_tables;
	table* array;
} table_stack;

int is_empty(table_stack * table_stack);

void push(table_stack * table_stack, table item);

void pop(table_stack * table_stack);

// FUNCTIONS that manage the information of the tables.

int is_declared (table_stack * stack, char* token);
int is_declared_on_current_table (table_stack * stack, char* token);


void add_user_type(table_stack * stack, Lexeme * token);
void add_user_type_properties(table_stack * stack, char * key, user_type_args token);
table_line inicialize_line(Lexeme * token_name);

void initialize_stack();

global_var_args initialize_global_var_args();
void add_global_var(table_stack * stack, global_var_args globalvar_args, Lexeme * token);
int get_user_type_size(table_stack * stack, char * token);

void add_function(table_stack* stack, int type, char* user_type, int num_func_args, func_args *function_args, Lexeme *token);
int is_function_declared(table_stack * stack, char* token);
void set_func_as_static(table_stack * stack, char* token);

void add_local_var(table_stack* stack, int type, char* user_type, int lv_static, int lv_const, Lexeme *token);

void free_table_stack(table_stack * stack);

expr_args init_expr_args();

int get_id_type(table_stack * stack, char* token, char** user_type_return);
int get_id_field_type(table_stack * stack, char* token, char* field);
int get_func_num_params(table_stack * stack, char* token);
int* get_func_params_types(table_stack * stack, char* token);

int get_category(table_stack * stack, char* token);