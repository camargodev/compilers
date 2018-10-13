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
	line.function_arguments = (struct Lexeme*) malloc(sizeof(struct Lexeme));

	table.lines[0] = line;

	return table;
}

/*
	TABLE STACK



*/

table_stack* create_stack (unsigned capacity){
	table_stack* stack = (table_stack *) malloc(sizeof(table_stack));
	stack->array = (table*) malloc(sizeof(table));
	stack->num_tables = NO_TABLES;

	return stack;
}

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
