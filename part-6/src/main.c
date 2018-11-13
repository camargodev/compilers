/*
Função principal para realização da E3.

Este arquivo não pode ser modificado.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../parser.tab.h" //arquivo gerado com bison -d parser.y
#include "../include/table.h"
#include "../include/iloc.h"
#include "../include/tree.h"
#include "../include/error.h"

extern int yylex_destroy(void);
extern Error* error;

void *arvore = NULL;
void descompila (void *arvore);
void libera (void *arvore);

int main (int argc, char **argv)
{
	int ret = yyparse();
	int print_error = 1;
	int error_code = 0;
	Node* tree = ((Node*)arvore);
 	
 	if (argc > 1) {
 		char* opt = argv[1];
		if (strcmp(opt, "all") == 0) {
			descompila (arvore);
			print_code(tree->code);
 		} else if (strcmp(opt, "tree")  == 0) {
			descompila (arvore);
 		} else if (strcmp(opt, "code")  == 0) {
			print_code(tree->code);
 		} else if (strcmp(opt, "none")  == 0) {
			print_error = 0;
 		}
 		//free(opt);
 	} else {
		print_code(tree->code);
 	}

 	free_op_list(tree->code);
	libera(arvore);
	arvore = NULL;
	yylex_destroy();

	error_code = raise_error(print_error);
 	if (error_code != 0) {
 		exit(error_code);
	}

	return 0;
}
