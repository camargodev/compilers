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

int main (int argc, char **argv)
{
//initializing stack


  int ret = yyparse(); 
  //descompila (arvore);
  libera(arvore);
  arvore = NULL;
  yylex_destroy();
  return 0;
}
