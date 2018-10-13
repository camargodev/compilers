// João Vitor de Camargo
// Marcellus Farias

#include "lexeme.h"

#define NO_TABLES -1

typedef struct line {
	int declaration_line;
	int nature;
	int token_type;
	int token_size;
	struct Lexeme *function_arguments;
	// token de usuario ??
	//Lexeme[] field_arguments;

	struct line* next_line;

} table_line;

typedef struct table {
	struct line *lines;

} table;

table create_table();

/*
	TABLE STACK



*/

typedef struct table_stack {
	int num_tables;
	table* array;
} table_stack;

table_stack* create_stack ();

//int is_full (table_stack * table_stack);

int is_empty(table_stack * table_stack);

void push(table_stack * table_stack, table item);

void pop(table_stack * table_stack);

//TO DO: função de percorrer um array de SymbolTable
// e ver se tem o token buscado. Passar ela no scanner para veri
//ficação de erros