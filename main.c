/*
Função principal para realização da E3.

Este arquivo não pode ser modificado.
*/
#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h" //arquivo gerado com bison -d parser.y
#include "table.h"

extern int yylex_destroy(void);

void *arvore = NULL;
void descompila (void *arvore);
void libera (void *arvore);

table_stack * stack;
int error_code = 0;
char * current_token;

int main (int argc, char **argv)
{
//initializing stack
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
				stack->array = malloc(sizeof(table) * stack->num_tables);
				stack->array[0] = table;

				//printf("\tSegundo print_stack\n");
				//print_stack(stack);	

  int ret = yyparse(); 
  descompila (arvore);
  libera(arvore);
  arvore = NULL;
  yylex_destroy();
  return error_code;
}
