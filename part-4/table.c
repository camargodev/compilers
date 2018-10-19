#include "table.h"
#include "nature.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

table create_table(){
	table table;
	table.lines = (table_line*) malloc(sizeof(table_line));
	table.num_lines = NO_LINES;
	
	return table;
}

/*
	TABLE STACK
*/

void push(table_stack* stack, table item){
	
	//if(is_full(table_stack))
	//	return;
	//printf("DEI PUSH\n");
	//printf("TABLE TEM %i LINHAS\n", item.num_lines);
	stack->num_tables++;
	stack->array = realloc(stack->array, sizeof(table)*(stack->num_tables+1));
	stack->array[stack->num_tables] = item;
	//printf("TABLE TEM %i LINHAS\n", item.num_lines);
}

void pop(table_stack * stack){
	
	//printf("DEI POP\n");
	if(stack->num_tables == NO_TABLES){
		printf("Pilha já vazia!");
		return;
	}
	else {
		stack->num_tables--;
		return;
	}	
}

// DEBUGGING FUNCTIONS

void print_line(table_line line)
{

	print_cabecalho_table_part1();
	printf("%s", line.token_name);
	printf("\t%d\t", line.declaration_line);
	printf("%d\t", line.nature);
	printf("%d\t", line.token_type);
	printf("%d\t", line.token_size);
	printf("%d\t", line.is_function);
	printf("%d\t", line.is_user_type);
	printf("%d\t", line.array_size);
	printf("%d\t", line.num_user_type_args);
	
	if(line.is_user_type)
		print_user_type_list(line.user_type_args, line.num_user_type_args);
	/*print_cabecalho_table_part2();
	printf("\tFunction_Args");
	printf("\t\t\t\tUser_Type_Args");
	printf("\t\t\t\tLexeme");
	printf("\t\t\t\tArray_Vals");*/
	printf("+----------------------------------------------------------+\n");
	printf("\n");
}

void print_table(table table)
{
	int i;

	if (table.num_lines == NO_LINES)
	{
		printf("Tabela sem linhas!\n");
	}
	else
	{
		//print_cabecalho_table();

		for(i = 0; i <= table.num_lines; i++)
		{
			printf("Linha [%d]\n", i);
			print_line(table.lines[i]);			
		}

		printf("Tabela terminada de ser impressa!\n");
	}
	return;
}

void print_stack(table_stack * stack)
{
	int i;
	
	printf("\n\n*********************************************\n");
	printf("COMEÇANDO PRINT DA PILHA\n");
	printf("*********************************************\n\n");

	if(stack->num_tables == NO_TABLES)
		printf("Sem tables na pilha!\n");
	else
	{
		for(i = 0; i <= stack->num_tables; i++)
		{
			printf("Tabela [%d]\n\n", i);
			print_table(stack->array[i]);			
		}		
	}

	printf("\n\n*********************************************\n");
	printf("FIM PRINT DA PILHA\n");
	printf("*********************************************\n\n");
}

void print_cabecalho_table_part1()
{
	printf("+----------------------------------------------------------+\n");
	printf("NAM");
	printf("\tDEC");
	printf("\tNAT");
	printf("\tTTY");
	printf("\tTSI");
	printf("\tIFU");
	printf("\tIUT");
	printf("\tASI");
	printf("\tNUT");
	
	printf("\n");

	return;
}

void print_cabecalho_table_part2()
{
	printf("\tFunction_Args");
	printf("\t\t\t\tUser_Type_Args");
	printf("\t\t\t\tLexeme");
	printf("\t\t\t\tArray_Vals");

	return;
}

void print_user_type_list(user_type_args * list_user_type_args, int num_types)
{
	printf("\nUser_Type_Args\n");

	int i = 0;
	
	for(i = 0; i < num_types; i++)
	{
		printf("[%d] SCOPE : %s", i, list_user_type_args[i].scope);
		printf("\t[%d] TOKEN_TYPE : %d", i, list_user_type_args[i].token_type);
		printf("\t[%d] TOKEN_NAME : %s\n", i, list_user_type_args[i].token_name);
	}

	return;		
}

/*
	FIND A TOKEN IN TABLES
	
*/

// Don't how to pass the name of the identifier in parser.
// Abstracting this, the funcion would be something like this
int is_declared (table_stack * stack, char* token) {

	int debug = FALSE;
	if (debug == TRUE)
		printf("\nLOOKING FOR %s", token);
	
	if (stack->num_tables == NO_TABLES)
	{
		return NOT_DECLARED;
	}
	else
	{
		int num_actual_table = stack->num_tables;
		//printf("NUM ACTUAL TABLE = %i\n", num_actual_table);

		while(num_actual_table != NO_TABLES)
		{
			int line_counter = 0;
			
			if (stack->array[num_actual_table].num_lines != NO_LINES)
			{
				while(line_counter <= stack->array[num_actual_table].num_lines)
				{		
					if (debug)
						printf("\nFOUND %s", stack->array[num_actual_table].lines[line_counter].token_name);			
					if (strcmp(stack->array[num_actual_table].lines[line_counter].token_name, token) == 0) 
					{
						return stack->array[num_actual_table].lines[line_counter].declaration_line;
					}
					line_counter++;
				}
			}

			num_actual_table--;
		}		

		return NOT_DECLARED;
	}
}

int is_declared_on_current_table (table_stack * stack, char* token) {
	
	if (stack->num_tables == NO_TABLES)
	{
		return NOT_DECLARED;
	}
	else
	{
		int num_actual_table = stack->num_tables;
		int line_counter = 0;
			
		if (stack->array[num_actual_table].num_lines != NO_LINES)
		{
			while(line_counter <= stack->array[num_actual_table].num_lines) {					
				if (strcmp(stack->array[num_actual_table].lines[line_counter].token_name, token) == 0)  {
					return stack->array[num_actual_table].lines[line_counter].declaration_line;
				}
				line_counter++;
			}
		}

		return NOT_DECLARED;
	}
}

int is_function_declared (table_stack * stack, char* token){
	
	if (stack->num_tables == NO_TABLES)
	{
		return NOT_DECLARED;
	}
	else
	{
		int num_actual_table = stack->num_tables;

		while(num_actual_table != NO_TABLES)
		{
			int line_counter = 0;
			
			if (stack->array[num_actual_table].num_lines != NO_LINES)
			{
				while(line_counter <= stack->array[num_actual_table].num_lines)
				{					
					//printf("Token do arraY : %s, Token parametro : %s, strcmp : %d", 
					//	stack->array[num_actual_table].lines[line_counter].token_name, token, strcmp(stack->array[num_actual_table].lines[line_counter].token_name, token));
					
					if (strcmp(stack->array[num_actual_table].lines[line_counter].token_name, token) == 0) 
					{
						if (stack->array[num_actual_table].lines[line_counter].is_function == TRUE) {
							return stack->array[num_actual_table].lines[line_counter].declaration_line;
						} else {
							return NOT_DECLARED;
						}
					}
					line_counter++;
				}
			}

			num_actual_table--;
		}		

		return NOT_DECLARED;
	}
}

int is_symbol_user_type(table_stack * stack, char* token) {
	
	if (stack->num_tables == NO_TABLES)
	{
		return NOT_DECLARED;
	}
	else
	{
		int num_actual_table = stack->num_tables;

		while(num_actual_table != NO_TABLES)
		{
			int line_counter = 0;
			
			if (stack->array[num_actual_table].num_lines != NO_LINES)
			{
				while(line_counter <= stack->array[num_actual_table].num_lines)
				{					
					if (strcmp(stack->array[num_actual_table].lines[line_counter].token_name, token) == 0) 
					{
						if (stack->array[num_actual_table].lines[line_counter].is_user_type == TRUE) {
							return TRUE;
						} else {
							return NOT_DECLARED;
						}
					}
					line_counter++;
				}
			}

			num_actual_table--;
		}		

		return NOT_DECLARED;
	}
}

void set_func_as_static(table_stack * stack, char* token) {
	
	if (stack->num_tables == NO_TABLES)
	{
		return;
	}
	else
	{
		int num_actual_table = stack->num_tables;

		while(num_actual_table != NO_TABLES)
		{
			int line_counter = 0;
			
			if (stack->array[num_actual_table].num_lines != NO_LINES)
			{
				while(line_counter <= stack->array[num_actual_table].num_lines)
				{					
					//printf("Token do arraY : %s, Token parametro : %s, strcmp : %d", 
					//	stack->array[num_actual_table].lines[line_counter].token_name, token, strcmp(stack->array[num_actual_table].lines[line_counter].token_name, token));
					
					if (strcmp(stack->array[num_actual_table].lines[line_counter].token_name, token) == 0) 
					{
						stack->array[num_actual_table].lines[line_counter].is_static = TRUE;
					}
					line_counter++;
				}
			}

			num_actual_table--;
		}		

		return;
	}
}
//If it is declared (can know it using the function above) and there is another declaration, we must throw an error.


//Now, if it is not declared, we must add it to the table.
// By now, there will be some kind of functions. The first one is for user type

//We first add the informations that are avaliable in the fisrt parser rule.
void add_user_type(table_stack * stack, Lexeme * token)
{
	int table_index = stack->num_tables;

	if (stack->num_tables != NO_TABLES)
	{
		table_line line;
		
		line = inicialize_line(token);
		line.token_name = strdup(token->value.v_string);
		line.declaration_line = token->line_number;
		line.nature = NATUREZA_IDENTIFICADOR;
		
		line.is_function = FALSE;
		line.is_user_type = TRUE;
		line.array_size = FALSE;

		line.function_args = NULL;
		line.num_user_type_args = 0;
		line.token_size = 0;

		//line.user_type = strdup(token->value.v_string);

		//printf("[ADD_USER_TYPE] Espaço alocado : %ld\n", sizeof(table_line) * (++stack->array[table_index].num_lines + 1));
				
		stack->array[table_index].lines = (table_line *)realloc(stack->array[table_index].lines,
															 sizeof(table_line) * (++stack->array[table_index].num_lines + 1));

		//print_line(line);
		stack->array[table_index].lines[stack->array[table_index].num_lines] = line;
	}

	return;
}

//stack, $2->value.v_string, list_user_type_args[i]
void add_user_type_properties(table_stack * stack, char * key, user_type_args token)
{
	int table_index = stack->num_tables;

	if(stack->num_tables != NO_TABLES)
	{
		int line_index = 0;
		table_line line;
		// in fact this first condition will always be true, its here for the tests
		do
		{
			line = stack->array[table_index].lines[line_index];
			//printf("[ADD_USER_TYPE_PROPERTIES] line_index : %d, token_name = %s\n", line_index, line.token_name);
			//print_line(line);
			line_index++;
		} while (line_index <= stack->array[table_index].num_lines
				&& line.token_name != key);

		line_index--;

		//printf("[ADD_USER_TYPE_PROPERTIES] Passou do while!\n");
		
		switch(token.token_type)
		{
			case INT:
				line.token_size = line.token_size + SIZE_INT;
				break;
			case FLOAT:
				//printf("[ADD_USER_TYPE_PROPERTIES] token_size : %d\n", line.token_size + SIZE_FLOAT);
				line.token_size = line.token_size + SIZE_FLOAT;
				break;
			case CHAR:
				//printf("[ADD_USER_TYPE_PROPERTIES] token_size : %d\n", line.token_size + SIZE_CHAR);
				line.token_size = line.token_size + SIZE_CHAR;
				break;
			case BOOL:
				//printf("[ADD_USER_TYPE_PROPERTIES] token_size : %d\n", line.token_size + SIZE_BOOL);
				line.token_size = line.token_size + SIZE_BOOL;
				break;
			case STRING:
				//printf("[ADD_USER_TYPE_PROPERTIES] token_size : %ld\n", line.token_size + strlen(token.token_name));
				line.token_size = line.token_size + strlen(token.token_name);
				break;
			default:
				//printf("[ADD_USER_TYPE_PROPERTIES] Default\n");
				break;
		}
		
		line.num_user_type_args++;
		line.token_type = USER_TYPE;
		//printf("[ADD_USER_TYPE_PROPERTIES] sizeof: %ld\n", sizeof(user_type_args));
		//printf("[ADD_USER_TYPE_PROPERTIES] sizeof: %d\n", line.num_user_type_args);

		line.user_type_args = realloc(line.user_type_args,
										sizeof(user_type_args) * line.num_user_type_args);

		line.user_type_args[line.num_user_type_args - 1].scope = token.scope;
		line.user_type_args[line.num_user_type_args - 1].token_type = token.token_type;
		line.user_type_args[line.num_user_type_args - 1].token_name = strdup(token.token_name);	

		stack->array[table_index].lines[line_index] = line;	
	}

	return;
}

//TO DO: initialize line and table.

table_line inicialize_line(Lexeme * token)
{
	table_line line;

	line.token_name = token->value.v_string;

	line.declaration_line = token->line_number;
	line.nature = -1;
	line.token_type = -1;
	line.token_size = 0;

	line.is_function = -1;
	line.is_user_type -1;
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

global_var_args initialize_global_var_args()
{
	global_var_args temp;
	temp.is_array = FALSE;
	temp.array_size = FALSE;
	temp.is_static = FALSE;

	temp.user_type_size = FALSE;

	temp.name = NULL;
	temp.type = -1;

	return temp;
}

void add_global_var(table_stack * stack, global_var_args globalvar_args, Lexeme * token)
{
	int table_index = stack->num_tables;

	if (stack->num_tables != NO_TABLES)
	{
		table_line line;
		
		line = inicialize_line(token);
		line.token_name = strdup(globalvar_args.name);
		line.declaration_line = token->line_number;
		line.nature = NATUREZA_IDENTIFICADOR;
		
		line.is_function = FALSE;
		line.is_user_type = FALSE;
		
		if(globalvar_args.is_array)
			line.array_size = globalvar_args.array_size;
		else
			line.array_size = FALSE;

		line.token_type = globalvar_args.type;

		switch(globalvar_args.type)
		{
			case INT:
				line.token_size = line.token_size + SIZE_INT;
				break;
			case FLOAT:
				//printf("[ADD_USER_TYPE_PROPERTIES] token_size : %d\n", line.token_size + SIZE_FLOAT);
				line.token_size = line.token_size + SIZE_FLOAT;
				break;
			case CHAR:
				//printf("[ADD_USER_TYPE_PROPERTIES] token_size : %d\n", line.token_size + SIZE_CHAR);
				line.token_size = line.token_size + SIZE_CHAR;
				break;
			case BOOL:
				//printf("[ADD_USER_TYPE_PROPERTIES] token_size : %d\n", line.token_size + SIZE_BOOL);
				line.token_size = line.token_size + SIZE_BOOL;
				break;
			case STRING:
				//printf("[ADD_USER_TYPE_PROPERTIES] token_size : %ld\n", line.token_size + strlen(token.token_name));
				line.token_size = line.token_size + strlen(globalvar_args.name);
				break;
			case USER_TYPE:
				line.user_type = strdup(globalvar_args.user_type);
				line.token_size = globalvar_args.user_type_size;
				break;
			default:
				break;
		}

		line.function_args = NULL;
		line.num_user_type_args = 0;
		
		//buscar na tabela
		//line.token_size = 0;

		line.lexeme = token;

		//printf("[ADD_USER_TYPE] Espaço alocado : %ld\n", sizeof(table_line) * (++stack->array[table_index].num_lines + 1));
				
		stack->array[table_index].lines = (table_line *)realloc(stack->array[table_index].lines,
															 sizeof(table_line) * (++stack->array[table_index].num_lines + 1));
		//print_line(line);
		stack->array[table_index].lines[stack->array[table_index].num_lines] = line;
	}
}

void add_function(table_stack* stack, int type, char* user_type, int num_func_args, func_args *function_args, Lexeme *token)
{
	int table_index = stack->num_tables;

	if (stack->num_tables != NO_TABLES)
	{
		table_line line;
		
		line = inicialize_line(token);
		line.token_name = strdup(token->value.v_string);
		line.declaration_line = token->line_number;
		line.nature = NATUREZA_IDENTIFICADOR;
		
		line.is_function = TRUE;
		line.is_static = FALSE;
		line.is_user_type = FALSE;
		line.array_size = FALSE;

		line.num_func_args = num_func_args;
		line.function_args = function_args;

		line.num_user_type_args = 0;
		line.token_size = 0;

		line.token_type = type;

		if (user_type != NULL)
			line.user_type = strdup(user_type);
		else
			line.user_type = NULL;

		//printf("[ADD_USER_TYPE] Espaço alocado : %ld\n", sizeof(table_line) * (++stack->array[table_index].num_lines + 1));
				
		stack->array[table_index].lines = (table_line *)realloc(stack->array[table_index].lines,
															 sizeof(table_line) * (++stack->array[table_index].num_lines + 1));
		//print_line(line);
		stack->array[table_index].lines[stack->array[table_index].num_lines] = line;
	}

	return;
}

void add_local_var(table_stack* stack, int type, char* user_type, int lv_static, int lv_const, Lexeme *token)
{
	int table_index = stack->num_tables;

	if (stack->num_tables != NO_TABLES)
	{
		table_line line;
		
		line = inicialize_line(token);
		line.token_name = strdup(token->value.v_string);
		line.declaration_line = token->line_number;
		line.nature = NATUREZA_IDENTIFICADOR;
		
		line.is_function = FALSE;
		line.is_static = lv_static;
		line.is_const = lv_const;
		line.is_user_type = (type == USER_TYPE) ? TRUE : FALSE;
		line.array_size = FALSE;

		line.num_func_args = 0;
		line.function_args = NULL;

		line.num_user_type_args = 0;
		line.token_size = 0;

		line.token_type = type;

		if (user_type != NULL)
			line.user_type = strdup(user_type);
		else
			line.user_type = NULL;

		//printf("[ADD_USER_TYPE] Espaço alocado : %ld\n", sizeof(table_line) * (++stack->array[table_index].num_lines + 1));
				
		stack->array[table_index].lines = (table_line *)realloc(stack->array[table_index].lines,
															 sizeof(table_line) * (++stack->array[table_index].num_lines + 1));
		//print_line(line);
		stack->array[table_index].lines[stack->array[table_index].num_lines] = line;
	}

	return;
}

int get_user_type_size(table_stack * stack, char * token)
{
	if (stack->num_tables == NO_TABLES)
	{
		return FALSE;
	}
	else
	{
		int num_actual_table = stack->num_tables;

		while(num_actual_table != NO_TABLES)
		{
			int line_counter = 0;
			
			if (stack->array[num_actual_table].num_lines != NO_LINES)
			{
				while(line_counter <= stack->array[num_actual_table].num_lines)
				{					
					//printf("Token do arraY : %s, Token parametro : %s, strcmp : %d", 
					//	stack->array[num_actual_table].lines[line_counter].token_name, token, strcmp(stack->array[num_actual_table].lines[line_counter].token_name, token));
					
					if (strcmp(stack->array[num_actual_table].lines[line_counter].token_name, token) == 0) 
					{
						return stack->array[num_actual_table].lines[line_counter].token_size;
					}
					line_counter++;
				}
			}

			num_actual_table--;
		}		

		return FALSE;
	}
}

void free_table_stack(table_stack * stack) 
{
	if (stack->num_tables == NO_TABLES)
	{
		return;
	}
	else
	{
		int num_actual_table = stack->num_tables;
		while(num_actual_table != NO_TABLES)
		{
			int line_counter = 0;
			
			if (stack->array[num_actual_table].num_lines != NO_LINES)
			{
				while(line_counter <= stack->array[num_actual_table].num_lines)
				{
					free(stack->array[num_actual_table].lines[line_counter].token_name); 

					stack->array[num_actual_table].lines[line_counter].token_name = NULL;
					
					if (stack->array[num_actual_table].lines[line_counter].user_type != NULL){
						free(stack->array[num_actual_table].lines[line_counter].user_type);
						stack->array[num_actual_table].lines[line_counter].user_type = NULL;
					}
					
					if (stack->array[num_actual_table].lines[line_counter].function_args != NULL) {
						free(stack->array[num_actual_table].lines[line_counter].function_args);
						stack->array[num_actual_table].lines[line_counter].function_args = NULL;
					}

					if (stack->array[num_actual_table].lines[line_counter].user_type_args != NULL) {
						int i;
						for (i = 0; i < stack->array[num_actual_table].lines[line_counter].num_user_type_args; i++)
							if (stack->array[num_actual_table].lines[line_counter].user_type_args[i].token_name != NULL)
								free(stack->array[num_actual_table].lines[line_counter].user_type_args[i].token_name);
						free(stack->array[num_actual_table].lines[line_counter].user_type_args);
						stack->array[num_actual_table].lines[line_counter].user_type_args = NULL;
					}

					line_counter++;
				}


				free(stack->array[num_actual_table].lines);
				stack->array[num_actual_table].lines = NULL;

			}

			free(stack->array);

			num_actual_table--;
		}		

		free(stack);
		stack = NULL;

		return;
	}
}

int get_id_type(table_stack * stack, char* token, char** user_type_return) {
	
	if (stack->num_tables == NO_TABLES)
	{
		return NOT_DECLARED;
	}
	else
	{
		int num_actual_table = stack->num_tables;
		
		while(num_actual_table != NO_TABLES)
		{
			int line_counter = 0;
			if (stack->array[num_actual_table].num_lines != NO_LINES)
			{
				while(line_counter <= stack->array[num_actual_table].num_lines)
				{					
					if (strcmp(stack->array[num_actual_table].lines[line_counter].token_name, token) == 0) 
					{
						if (stack->array[num_actual_table].lines[line_counter].token_type == USER_TYPE) {
							*user_type_return = stack->array[num_actual_table].lines[line_counter].user_type;
						} else {
							*user_type_return = NULL;
						}
						return stack->array[num_actual_table].lines[line_counter].token_type;
					}
					line_counter++;
				}
			}
			num_actual_table--;
		}		
		return NOT_DECLARED;
	}
}

int get_id_field_type(table_stack * stack, char* token, char* field) {
	
	if (stack->num_tables == NO_TABLES)
	{
		return NOT_DECLARED;
	}
	else
	{
		int num_actual_table = stack->num_tables;
		
		while(num_actual_table != NO_TABLES)
		{
			int line_counter = 0;
			if (stack->array[num_actual_table].num_lines != NO_LINES)
			{
				while(line_counter <= stack->array[num_actual_table].num_lines)
				{					
					if (strcmp(stack->array[num_actual_table].lines[line_counter].token_name, token) == 0) 
					{
						if (stack->array[num_actual_table].lines[line_counter].is_user_type == TRUE) {
							int i;
							for (i = 0; i < stack->array[num_actual_table].lines[line_counter].num_user_type_args; i++) {
								if (strcmp(stack->array[num_actual_table].lines[line_counter].user_type_args[i].token_name, field) == 0) {
									return stack->array[num_actual_table].lines[line_counter].user_type_args[i].token_type;
								}
							}
							return INVALID_FIELD;
						} else {
							return NOT_USER_TYPE;
						}
						return stack->array[num_actual_table].lines[line_counter].token_type;
					}
					line_counter++;
				}
			}
			num_actual_table--;
		}		
		return NOT_DECLARED;
	}
}

int is_user_type(table_stack * stack, char* token) {
	
	if (stack->num_tables == NO_TABLES)
	{
		return FALSE;
	}
	else
	{
		int num_actual_table = stack->num_tables;
		
		while(num_actual_table != NO_TABLES)
		{
			int line_counter = 0;
			if (stack->array[num_actual_table].num_lines != NO_LINES)
			{
				while(line_counter <= stack->array[num_actual_table].num_lines)
				{					
					if (strcmp(stack->array[num_actual_table].lines[line_counter].token_name, token) == 0) 
					{
						if (stack->array[num_actual_table].lines[line_counter].num_user_type_args > 0)
							return TRUE;
					}
					line_counter++;
				}
			}
			num_actual_table--;
		}		
		return FALSE;
	}
}

expr_args init_expr_args()
{
	expr_args args;

	args.has_int = FALSE;
	args.has_float = FALSE;
	args.has_char = FALSE;
	args.has_string = FALSE;
	args.has_bool = FALSE;
	args.has_id = FALSE;
	args.has_user_type = FALSE;

	return args;
}