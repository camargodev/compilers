#include "table.h"
#include <stdio.h>
#include <stdlib.h>

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
int is_declared (table_stack * stack, Lexeme token){
	
	if (stack->num_tables == NO_TABLES)
	{
		return FALSE;
	}
	else
	{
		int actual_table = stack->num_tables;

		while(actual_table != NO_TABLES)
		{
			int line_counter = 0;
			//table_line ** lines = &stack->array[actual_table].lines;

			if (&stack->array[actual_table].lines != NULL)
			{
				//table_line ** line = &stack->array[actual_table].lines[line_counter];
				while(&stack->array[actual_table].lines[line_counter] != NULL) 
				{
					if (stack->array[actual_table].lines[line_counter].token_name == "marcellus") //mudar aqui depois
					{
						return TRUE;
					}
					line_counter++;
				}
			}

			actual_table--;
		}

		return FALSE;
	}
}
//If it is declared (can know it using the function above) and there is another declaration, we must throw an error.


//Now, if it is not declared, we must declare it.
// By now, there will be 2 functions: one for the first table (the one for global_var and classes) and one for the last table.

// Again, i need to change the parameter in the future.
void declare_token(table_stack * stack, Lexeme token, int global_declaration)
{
	int table_index = (global_declaration == TRUE) ? 0 : stack->num_tables;

	if (stack->array != NULL)
	{
		table_line line;

		// initialize line

		stack->array[table_index].lines = (table_line *)realloc(stack->array[table_index].lines,
															 sizeof(table_line) * ++stack->array[table_index].num_lines);
		
		stack->array[table_index].lines[stack->array[table_index].num_lines] = line;// arrumar aqui de acordo com o parametro
	}
}

//TO DO: initialize line and table.

table_line inialize_line(char * token_name)
{
	table_line line;

	line.token_name = token_name;

	line.declaration_line = -1;
	line.nature = -1;
	line.token_type = -1;
	line.token_size = -1;

	line.is_function = -1;
	line.is_user_type -1;
	line.array_size = -1;

	line.function_args = (func_args *) malloc(sizeof(func_args));
	line.user_type_args = (user_type_args *) malloc(sizeof(user_type_args));

	Lexeme any_lexeme;
	any_lexeme.line_number = -1;
	any_lexeme.token_type = -1;
	any_lexeme.literal_type = -1;
	any_lexeme.value.v_int = -1;

	line.yyval = any_lexeme;
	line.array_vals = (Lexeme*) malloc(sizeof(Lexeme));

	return line;
}