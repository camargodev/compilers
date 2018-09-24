#include "lex_value.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

void test_lex_val() {
	struct lex_value* lex_val;
	lex_val = (struct lex_value*) malloc(sizeof(struct lex_value));

	lex_val->line_number = 1;
	lex_val->token_type = KEYWORD;
	lex_val->literal_type = NOT_LITERAL;
	lex_val->value.v_string = "case";
	print_token(lex_val);

	lex_val->line_number = 1;
	lex_val->token_type = LITERAL;
	lex_val->literal_type = CHAR;
	lex_val->value.v_char = '0';
	print_token(lex_val);

	lex_val->line_number = 1;
	lex_val->token_type = SPECIAL_CHAR;
	lex_val->literal_type = NOT_LITERAL;
	lex_val->value.v_char = ':';
	print_token(lex_val);

	lex_val->line_number = 2;
	lex_val->token_type = LITERAL;
	lex_val->literal_type = BOOL;
	lex_val->value.v_bool = FALSE;
	print_token(lex_val);

	printf("\n");
}

void test_tree() {
	Tree_Node* root; 

	struct lex_value* lex_val;
	lex_val = (struct lex_value*) malloc(sizeof(struct lex_value));

	lex_val->line_number = 1;
	lex_val->token_type = KEYWORD;
	lex_val->literal_type = NOT_LITERAL;
	lex_val->value.v_string = "case";
	root = new_node(lex_val);

	lex_val = (struct lex_value*) malloc(sizeof(struct lex_value));
	lex_val->line_number = 1;
	lex_val->token_type = LITERAL;
	lex_val->literal_type = CHAR;
	lex_val->value.v_char = '0';
	add_node(root, new_node(lex_val));

	lex_val = (struct lex_value*) malloc(sizeof(struct lex_value));
	lex_val->line_number = 1;
	lex_val->token_type = SPECIAL_CHAR;
	lex_val->literal_type = NOT_LITERAL;
	lex_val->value.v_char = ':';
	add_node(root, new_node(lex_val));

	lex_val = (struct lex_value*) malloc(sizeof(struct lex_value));
	lex_val->line_number = 2;
	lex_val->token_type = LITERAL;
	lex_val->literal_type = BOOL;
	lex_val->value.v_bool = FALSE;
	add_node(root, new_node(lex_val));

	descompila(root);

	libera(root);

	printf("\n");
}

int main() {
	test_tree();
	
}