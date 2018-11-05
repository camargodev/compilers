#include "../include/table.h"
#include "../include/lexeme.h"
#include "../include/category.h"
//#include "tree.h"
//#include "size.h"
#include <stdio.h>
#include <stdlib.h>
#include "../include/debug_print.h"

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

void print_line(table_line line)
{
	print_cabecalho_table_part1();
	printf("%s", line.token_name);
	printf("\t%d\t", line.declaration_line);
	printf("%d\t", line.nature);
	printf("%d\t", line.token_type);
	printf("%d\t", line.token_size);
	printf("%d\t", (line.category == FUNCTION) ? TRUE : FALSE);
	printf("%d\t", (line.user_type != NULL) ? TRUE : FALSE);
	printf("%d\t", line.array_size);
	printf("%d\t", line.num_user_type_args);
	
	if(line.user_type != NULL)
		print_user_type_list(line.user_type_args, line.num_user_type_args);
	
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