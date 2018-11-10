/*
Função principal para realização da E3.

Este arquivo não pode ser modificado.
*/
#include <stdio.h>
#include <stdlib.h>
#include "../parser.tab.h" //arquivo gerado com bison -d parser.y
#include "../include/table.h"
#include "../include/iloc.h"
#include "../include/tree.h"

extern int yylex_destroy(void);

void *arvore = NULL;
void descompila (void *arvore);
void libera (void *arvore);

int main (int argc, char **argv)
{
  int ret = yyparse(); 
  //descompila (arvore);
  print_code(((Node*)arvore)->code);
  libera(arvore);
  arvore = NULL;
  yylex_destroy();
  return 0;
}
