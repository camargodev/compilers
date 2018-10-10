#include "lexeme.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

void test_lex() {
	struct Lexeme* lex;
	lex = (struct Lexeme*) malloc(sizeof(struct Lexeme));

	lex->line_number = 1;
	lex->token_type = KEYWORD;
	lex->literal_type = NOT_LITERAL;
	lex->value.v_string = "case";
	print_token(lex);

	lex->line_number = 1;
	lex->token_type = LITERAL;
	lex->literal_type = CHAR;
	lex->value.v_char = '0';
	print_token(lex);

	lex->line_number = 1;
	lex->token_type = SPECIAL_CHAR;
	lex->literal_type = NOT_LITERAL;
	lex->value.v_char = ':';
	print_token(lex);

	lex->line_number = 2;
	lex->token_type = LITERAL;
	lex->literal_type = BOOL;
	lex->value.v_bool = FALSE;
	print_token(lex);

	printf("\n");
}

void test_tree() {
	Node* root; 

	struct Lexeme* lex;
	lex = (struct Lexeme*) malloc(sizeof(struct Lexeme));

	lex->line_number = 1;
	lex->token_type = KEYWORD;
	lex->literal_type = NOT_LITERAL;
	lex->value.v_string = "case";
	root = new_node(lex);

	lex = (struct Lexeme*) malloc(sizeof(struct Lexeme));
	lex->line_number = 1;
	lex->token_type = LITERAL;
	lex->literal_type = CHAR;
	lex->value.v_char = '0';
	add_node(root, new_node(lex));

	lex = (struct Lexeme*) malloc(sizeof(struct Lexeme));
	lex->line_number = 1;
	lex->token_type = SPECIAL_CHAR;
	lex->literal_type = NOT_LITERAL;
	lex->value.v_char = ':';
	add_node(root, new_node(lex));

	lex = (struct Lexeme*) malloc(sizeof(struct Lexeme));
	lex->line_number = 2;
	lex->token_type = LITERAL;
	lex->literal_type = BOOL;
	lex->value.v_bool = FALSE;
	add_node(root, new_node(lex));

	descompila(root);

	libera(root);

	printf("\n");
}

int main() {
	test_tree();
	
}