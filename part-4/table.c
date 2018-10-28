#include "table.h"
#include "nature.h"
#include "category.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

table_line* get_line(table_stack * stack, char* token);
void free_line(table_line line);
void free_table(table table);

table create_table() {
	table table;
	table.lines = (table_line*) malloc(sizeof(table_line));
	table.num_lines = NO_LINES;
	
	return table;
}

void push(table_stack* stack, table item){
	
	stack->num_tables++;
	stack->array = realloc(stack->array, sizeof(table)*(stack->num_tables+1));
	stack->array[stack->num_tables] = item;
}

void pop(table_stack * stack){
	
	if(stack->num_tables == NO_TABLES){
		printf("Pilha já vazia!");
		return;
	}
	else {
		free_table(stack->array[stack->num_tables]);
		stack->num_tables--;
		return;
	}	
}

int is_declared (table_stack * stack, char* token) {
	table_line* line = get_line(stack, token);
	return (line != NULL);	
}

int is_declared_on_current_table (table_stack * stack, char* token) {
	if (stack->num_tables == NO_TABLES) {
		return NOT_DECLARED;
	} else {
		int num_actual_table = stack->num_tables;
		int line_counter = 0;
		if (stack->array[num_actual_table].num_lines != NO_LINES) {
			while(line_counter <= stack->array[num_actual_table].num_lines) {					
				if (strcmp(stack->array[num_actual_table].lines[line_counter].token_name, token) == 0)  
					return stack->array[num_actual_table].lines[line_counter].declaration_line;
				line_counter++;
			}
		}
		return NOT_DECLARED;
	}
}

int is_function_declared (table_stack * stack, char* token){
	table_line* line = get_line(stack, token);
	if (line != NULL) 
		return (line->category == FUNCTION);
	return FALSE;
}

void set_func_as_static(table_stack * stack, char* token) {
	table_line* line = get_line(stack, token);
	if (line != NULL)
		line->is_static = TRUE;
}

void add_user_type(table_stack * stack, Lexeme * token) {
	int table_index = stack->num_tables;

	if (stack->num_tables != NO_TABLES) {
		table_line line;
		
		line = inicialize_line(token);
		line.token_name = strdup(token->value.v_string);
		line.declaration_line = token->line_number;
		line.nature = NATUREZA_IDENTIFICADOR;
		
		line.category = USER_TYPE;
		line.array_size = 0;

		line.function_args = NULL;
		line.num_user_type_args = 0;
		line.token_size = 0;

		stack->array[table_index].lines = (table_line *) realloc(stack->array[table_index].lines,
															 sizeof(table_line) * (++stack->array[table_index].num_lines + 1));

		stack->array[table_index].lines[stack->array[table_index].num_lines] = line;
	}

	return;
}

void add_user_type_properties(table_stack * stack, char * key, user_type_args token) {
	int table_index = stack->num_tables;

	if(stack->num_tables != NO_TABLES) {
		int line_index = 0;
		table_line line;
		// in fact this first condition will always be true, its here for the tests
		do {
			line = stack->array[table_index].lines[line_index];
			line_index++;
		} while (line_index <= stack->array[table_index].num_lines
				&& line.token_name != key);

		line_index--;

		switch(token.token_type) {
			case INT:
				line.token_size = line.token_size + SIZE_INT;
				break;
			case FLOAT:
				line.token_size = line.token_size + SIZE_FLOAT;
				break;
			case CHAR:
				line.token_size = line.token_size + SIZE_CHAR;
				break;
			case BOOL:
				line.token_size = line.token_size + SIZE_BOOL;
				break;
			case STRING:
				line.token_size = line.token_size + strlen(token.token_name);
				break;
			default:
				break;
		}
		
		line.num_user_type_args++;
		line.token_type = USER_TYPE;
		
		line.user_type_args = realloc(line.user_type_args,
										sizeof(user_type_args) * line.num_user_type_args);

		line.user_type_args[line.num_user_type_args - 1].scope = token.scope;
		line.user_type_args[line.num_user_type_args - 1].token_type = token.token_type;
		line.user_type_args[line.num_user_type_args - 1].token_name = strdup(token.token_name);	

		stack->array[table_index].lines[line_index] = line;	
	}

	return;
}

table_line inicialize_line(Lexeme * token) {
	table_line line;

	line.token_name = token->value.v_string;

	line.declaration_line = token->line_number;
	line.nature = -1;
	line.token_type = -1;
	line.token_size = 0;

	line.category = NONE;
	line.array_size = -1;

	line.user_type = NULL;

	line.function_args = NULL;
	line.user_type_args = NULL;
	line.num_user_type_args = -1;
	line.num_func_args = -1;

	line.is_static = FALSE;
	line.is_const = FALSE;

	line.lexeme = token;

	return line;
}

global_var_args initialize_global_var_args() {
	global_var_args temp;
	temp.is_array = FALSE;
	temp.array_size = FALSE;
	temp.is_static = FALSE;

	temp.user_type_size = FALSE;

	temp.name = NULL;
	temp.type = -1;

	return temp;
}

void add_global_var(table_stack * stack, global_var_args globalvar_args, Lexeme * token) {
	int table_index = stack->num_tables;

	if (stack->num_tables != NO_TABLES) {
		table_line line;
		
		line = inicialize_line(token);
		line.token_name = strdup(globalvar_args.name);
		line.declaration_line = token->line_number;
		line.nature = NATUREZA_IDENTIFICADOR;
		
		if (globalvar_args.is_array) {
			line.category = ARRAY;
			line.array_size = globalvar_args.array_size;
		} else {
			line.category = VARIABLE;
			line.array_size = 0;
		}

		line.token_type = globalvar_args.type;

		switch(globalvar_args.type) {
			case INT:
				line.token_size = (globalvar_args.is_array) ? 
							line.token_size + (SIZE_INT * globalvar_args.array_size) : line.token_size + SIZE_INT;
				break;
			case FLOAT:
				line.token_size = (globalvar_args.is_array) ?
							line.token_size + (SIZE_FLOAT * globalvar_args.array_size) : line.token_size + SIZE_FLOAT;
				break;
			case CHAR:
				line.token_size = (globalvar_args.is_array) ?
							line.token_size + (SIZE_CHAR * globalvar_args.array_size) : line.token_size + SIZE_CHAR;
				break;
			case BOOL:
				line.token_size = (globalvar_args.is_array) ?
							line.token_size + (SIZE_BOOL * globalvar_args.array_size) : line.token_size + SIZE_BOOL;
				break;
			case STRING: //se for array, tem que ver essa parte.
				line.token_size = line.token_size + strlen(globalvar_args.name);
				break;
			case USER_TYPE:
				line.user_type = strdup(globalvar_args.user_type);
				line.token_size = (globalvar_args.is_array) ?
							(globalvar_args.user_type_size * globalvar_args.array_size) : globalvar_args.user_type_size;
				break;
			default:
				break;
		}

		line.function_args = NULL;
		line.num_user_type_args = 0;
		
		line.lexeme = token;

		stack->array[table_index].lines = (table_line *)realloc(stack->array[table_index].lines,
															 sizeof(table_line) * (++stack->array[table_index].num_lines + 1));
		stack->array[table_index].lines[stack->array[table_index].num_lines] = line;
	}
}

void add_function(table_stack* stack, int type, char* user_type, int num_func_args, func_args *function_args, Lexeme *token) {
	int table_index = stack->num_tables;

	if (stack->num_tables != NO_TABLES)	{
		table_line line;
		
		line = inicialize_line(token);
		line.token_name = strdup(token->value.v_string);
		line.declaration_line = token->line_number;
		line.nature = NATUREZA_IDENTIFICADOR;
		
		line.category = FUNCTION;
		line.is_static = FALSE;
		line.array_size = 0;

		line.num_func_args = num_func_args;
		line.function_args = function_args;

		line.num_user_type_args = 0;
		line.token_size = 0;

		line.token_type = type;
		
		if (user_type != NULL)
			line.user_type = strdup(user_type);
		else
			line.user_type = NULL;

		stack->array[table_index].lines = (table_line *)realloc(stack->array[table_index].lines,
															 sizeof(table_line) * (++stack->array[table_index].num_lines + 1));
		stack->array[table_index].lines[stack->array[table_index].num_lines] = line;
	}

	return;
}

void add_local_var(table_stack* stack, int type, char* user_type, int lv_static, int lv_const, Lexeme *token) {
	int table_index = stack->num_tables;

	if (stack->num_tables != NO_TABLES) {
		table_line line;
		
		line = inicialize_line(token);
		line.token_name = strdup(token->value.v_string);
		line.declaration_line = token->line_number;
		line.nature = NATUREZA_IDENTIFICADOR;
		
		line.category = VARIABLE;
		line.is_static = lv_static;
		line.is_const = lv_const;
		line.array_size = 0;

		line.num_func_args = 0;
		line.function_args = NULL;

		line.num_user_type_args = 0;
		
		//if(token->type == STRING)
		//	line.token_size = strlen();
		//else
			line.token_size = 0;

		line.token_type = type;

		if (user_type != NULL)
			line.user_type = strdup(user_type);
		else
			line.user_type = NULL;

		stack->array[table_index].lines = (table_line *)realloc(stack->array[table_index].lines,
															 sizeof(table_line) * (++stack->array[table_index].num_lines + 1));
		stack->array[table_index].lines[stack->array[table_index].num_lines] = line;
	}

	return;
}

int get_user_type_size(table_stack * stack, char * token) {
	table_line* line = get_line(stack, token);
	if (line != NULL) 
		return line->token_size;
	return 0;
}

void free_line(table_line line) {
	free(line.token_name); 
	line.token_name = NULL;
	
	if (line.user_type != NULL){
		free(line.user_type);
		line.user_type = NULL;
	}
	
	if (line.function_args != NULL) {
		free(line.function_args);
		line.function_args = NULL;
	}

	if (line.user_type_args != NULL) {
		int i;
		for (i = 0; i < line.num_user_type_args; i++)
			if (line.user_type_args[i].token_name != NULL) {
				free(line.user_type_args[i].token_name);
				line.user_type_args[i].token_name = NULL;
			}
		free(line.user_type_args);
		line.user_type_args = NULL;
	}
}

void free_table(table table) {
	int line_counter = 0;
	while(line_counter <= table.num_lines) { 
		free_line(table.lines[line_counter]);
		line_counter++;
	}

	free(table.lines);
	table.lines = NULL;
}

void free_table_stack(table_stack * stack) {
	if (stack->num_tables == NO_TABLES) {
		return;
	} else {
		int num_actual_table = stack->num_tables;
		while(num_actual_table != NO_TABLES) {
			free_table(stack->array[num_actual_table]);
			num_actual_table--;
		}		
		free(stack);
		stack = NULL;
		return;
	}
}

int get_id_type(table_stack * stack, char* token, char** user_type_return) {
	table_line* line = get_line(stack, token);
	if (line != NULL) {
		*user_type_return = line->user_type;
		return line->token_type;
	}
	*user_type_return = NULL;
	return NOT_DECLARED;
}

int get_id_field_type(table_stack * stack, char* token, char* field) {
	table_line* line = get_line(stack, token);
	if (line != NULL) {
		if (line->category == USER_TYPE) {
			int i;
			for (i = 0; i < line->num_user_type_args; i++) {
				if (strcmp(line->user_type_args[i].token_name, field) == 0) {
					return line->user_type_args[i].token_type;
				}
			}
			return INVALID_FIELD;
		} else {
			return NOT_USER_TYPE;
		}
	}
	return INVALID_FIELD;
}

int get_func_num_params(table_stack * stack, char* token) {
	table_line* line = get_line(stack, token);
	if (line != NULL)  {
		if (line->category == FUNCTION)
			return line->num_func_args;
	}
	return -1	;
}

int* get_func_params_types(table_stack * stack, char* token) {
	table_line* line = get_line(stack, token);
	if (line != NULL) {
		if (line->num_func_args <= 0)
			return NULL;
		int i;
		int* types = malloc(sizeof(int));
		for (i = 0; i < line->num_func_args; i++) {
			types = realloc(types, sizeof(int)*(i+1));
			types[i] = line->function_args[i].type;
		}
		return types;
	}
	return NULL;
}

int get_category(table_stack * stack, char* token) {
	table_line* line = get_line(stack, token);
	if (line != NULL) 
		return line->category;
	return FALSE;
}

table_line* get_line(table_stack * stack, char* token) {
	
	if (stack->num_tables == NO_TABLES) {
		return NULL;
	} else {
		int num_actual_table = stack->num_tables;
		while(num_actual_table != NO_TABLES) {
			int line_counter = 0; 
			if (stack->array[num_actual_table].num_lines != NO_LINES) {
				while(line_counter <= stack->array[num_actual_table].num_lines) {		
					if (strcmp(stack->array[num_actual_table].lines[line_counter].token_name, token) == 0) {
						return &stack->array[num_actual_table].lines[line_counter];
					}
					line_counter++;
				}
			}
			num_actual_table--;
		}		
		return NULL;
	}
}

int get_param_type(char* field, int num_params, func_args* params) {
	int index;
	if (field == NULL)
		return NOT_DECLARED;
	if (params == NULL)
		return NOT_DECLARED;
	for (index = 0; index < num_params; index++) {
		if (strcmp(params[index].name, field) == 0)
			return params[index].type;
	}
	return NOT_DECLARED;
}

void update_string_size(table_stack * stack, Lexeme* token_update, Lexeme* token_data) {
	
	table_line* line = get_line(stack, token_update->value.v_string);
	char* substr = malloc(sizeof(token_data->value.v_string));
	strncpy(substr, token_data->value.v_string, 1);
	if(strcmp(substr,"\"") == 0){
		line->token_size = strlen(token_data->value.v_string) - 2;
	}
	else{
		table_line* line2 = get_line(stack, token_data->value.v_string);
		line->token_size = line2->token_size;
	}

	return;
}

int get_size(table_stack* stack, Lexeme* token) {
	return get_line(stack, token->value.v_string)->token_size;
}


