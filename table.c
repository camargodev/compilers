#include "table.h"
#include "nature.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

table create_table(){
	table table;
	table.lines = (table_line*) malloc(sizeof(table_line));

	table_line line;
	
	line.declaration_line = -1;
	line.nature = -1;
	line.token_type = -1;
	line.token_size = -1;	
	//line.function_arguments = (struct Lexeme*) malloc(sizeof(struct Lexeme));

	table.lines[0] = line;

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
			//table_line ** lines = &stack->array[actual_table].lines;

			if (&stack->array[num_actual_table].lines != NULL)
			{
				//table_line ** line = &stack->array[actual_table].lines[line_counter];
				while(&stack->array[num_actual_table].lines[line_counter] != NULL) 
				{
					if (stack->array[num_actual_table].lines[line_counter].token_name == token) 
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

	if (stack->array != NULL)
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
		
		//line.yyval
		line.array_vals = NULL;

		stack->array[table_index].lines = (table_line *)realloc(stack->array[table_index].lines,
															 sizeof(table_line) * ++stack->array[table_index].num_lines);
		
		stack->array[table_index].lines[stack->array[table_index].num_lines] = line;// arrumar aqui de acordo com o parametro
	}
}


void add_user_type_properties(table_stack * stack, char * key, char * current_scope, Lexeme * token)
{
	int table_index = 0;

	if (stack->array != NULL)
	{
		int line_index = 0;
		table_line line;
		// in fact this first condition will always be true, its here for the tests
		do
		{
			line = stack->array[table_index].lines[line_index];
			line_index++;
		} while (line_index < stack->array[table_index].num_lines
				&& line.token_name != key);

		line_index--;

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
				line.token_size = -1;
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