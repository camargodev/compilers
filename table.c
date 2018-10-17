#include "table.h"
#include "nature.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

table create_table(){
	table table;
	table.lines = (table_line*) malloc(sizeof(table_line));
	table.num_lines = NO_LINES;
	//line.function_arguments = (struct Lexeme*) malloc(sizeof(struct Lexeme));

	//table.lines[0] = line;

	return table;
}

/*
	TABLE STACK



*/

void push(table_stack* table_stack, table item){
	
	//if(is_full(table_stack))
	//	return;
	table_stack->array[++table_stack->num_tables] = item;
	printf("Item pushed\n");
}

void pop(table_stack * table_stack){
	
	if(table_stack->num_tables == NO_TABLES){
		printf("Pilha já vazia!");
		return;
	}
	else{
		//free(table_stack->array[table_stack->num_tables]);
		table_stack->num_tables--;
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
int is_declared (table_stack * stack, char* token){
	
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
//If it is declared (can know it using the function above) and there is another declaration, we must throw an error.


//Now, if it is not declared, we must add it to the table.
// By now, there will be some kind of functions. The first one is for user type

//We first add the informations that are avaliable in the fisrt parser rule.
void add_user_type(table_stack * stack, Lexeme * token)
{
	int table_index = 0;

	if (stack->num_tables != NO_TABLES)
	{
		table_line line;
		
		line = inicialize_line(token);
		line.token_name = token->value.v_string;
		line.declaration_line = token->line_number;
		line.nature = NATUREZA_IDENTIFICADOR;
		
		line.is_function = FALSE;
		line.is_user_type = TRUE;
		line.array_size = FALSE;

		line.function_args = NULL;
		line.num_user_type_args = 0;
		line.token_size = 0;
		
		line.array_vals = NULL;

		//printf("[ADD_USER_TYPE] Espaço alocado : %ld\n", sizeof(table_line) * (++stack->array[table_index].num_lines + 1));
				
		stack->array[table_index].lines = (table_line *)realloc(stack->array[table_index].lines,
															 sizeof(table_line) * (++stack->array[table_index].num_lines + 1));
		//print_line(line);
		stack->array[table_index].lines[stack->array[table_index].num_lines] = line;
	}

	return;
}

//stack, $2->value.v_string, list_user_type_args[i]
void add_user_type_properties2(table_stack * stack, char * key, user_type_args token)
{
	int table_index = 0;

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
		
		//printf("[ADD_USER_TYPE_PROPERTIES] Token_Type : %d\n", token.token_type);

		switch(token.token_type)
		{
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
		}
		
		line.num_user_type_args++;
		//printf("[ADD_USER_TYPE_PROPERTIES] sizeof: %ld\n", sizeof(user_type_args));
		//printf("[ADD_USER_TYPE_PROPERTIES] sizeof: %d\n", line.num_user_type_args);

		line.user_type_args = realloc(line.user_type_args,
										sizeof(user_type_args) * line.num_user_type_args);

		line.user_type_args[line.num_user_type_args - 1].scope = token.scope;
		line.user_type_args[line.num_user_type_args - 1].token_type = token.token_type;
		line.user_type_args[line.num_user_type_args - 1].token_name = token.token_name;	

		stack->array[table_index].lines[line_index] = line;	
	}

	return;
}


void add_user_type_properties(table_stack * stack, char * key, char * current_scope, Lexeme * token)
{
	int table_index = 0;

	if (stack->num_tables != NO_TABLES)
	{
		int line_index = 0;
		table_line line;
		// in fact this first condition will always be true, its here for the tests
		do
		{
			line = stack->array[table_index].lines[line_index];
			printf("[ADD_USER_TYPE_PROPERTIES] line_index : %d, token_name = %s", line_index, line.token_name);
			print_line(line);
			line_index++;
		} while (line_index <= stack->array[table_index].num_lines
				&& line.token_name != key);

		line_index--;

		printf("[ADD_USER_TYPE_PROPERTIES] Passou do while!\n");
		
		printf("[ADD_USER_TYPE_PROPERTIES] Token_Type : %d\n", token->token_type);

		switch(token->token_type)
		{
			case INT:
				line.token_size = SIZE_INT;
				break;
			case FLOAT:
				line.token_size = SIZE_FLOAT;
				break;
			case CHAR:
				line.token_size = SIZE_CHAR;
				break;
			case BOOL:
				line.token_size = SIZE_BOOL;
				break;
			case STRING:
				line.token_size = strlen(token->value.v_string);
				break;
		}
		line.num_user_type_args++;
		line.user_type_args = realloc(line.user_type_args,
										sizeof(line.user_type_args) * line.num_user_type_args);

		line.user_type_args[line.num_user_type_args].scope = current_scope;
		line.user_type_args[line.num_user_type_args].token_type = token->token_type;
		line.user_type_args[line.num_user_type_args].token_name = token->value.v_string;	

		stack->array[table_index].lines[line_index] = line;	
	}
}

//TO DO: initialize line and table.

table_line inicialize_line(Lexeme * token)
{
	table_line line;

	line.token_name = token->value.v_string;

	line.declaration_line = token->line_number;
	line.nature = -1;
	line.token_type = -1;
	line.token_size = -1;

	line.is_function = -1;
	line.is_user_type -1;
	line.array_size = -1;

	line.function_args = (func_args *) malloc(sizeof(func_args));
	line.user_type_args = (user_type_args *) malloc(sizeof(user_type_args));
	line.num_user_type_args = -1;

	line.lexeme = *token;
	line.array_vals = (Lexeme*) malloc(sizeof(Lexeme));

	return line;
}

/*
void initialize_stack()
{
	//initializing stack
	stack = (table_stack *) malloc(sizeof(table_stack));
	stack->array = NULL;
	stack->num_tables = NO_TABLES;
				
	printf("\tPilha inicializada!\n");

	printf("Primeiro print_stack\n");
	print_stack(stack);

				
				//first table will be global scope table
	table table = create_table();
	stack->num_tables++;
	stack->array = malloc(sizeof(table) * stack->num_tables);
	stack->array[0] = table;

	printf("\tSegundo print_stack\n");
	print_stack(stack);	

	return;
}*/