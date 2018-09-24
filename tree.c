// João Vitor de Camargo
// Marcellus Farias

#include <stdio.h>
#include <stdlib.h>
#include "lex_value.h"
#include "tree.h"

#define NO_CHILDREN		0

Tree_Node* new_node(struct lex_value* token) {
	
	Tree_Node* node = malloc(sizeof(Tree_Node));
	
	node->token = token;
	node->children_num = NO_CHILDREN;
	node->children = (Tree_Node**) malloc(sizeof(Tree_Node**));

	return node;
}

void add_node(Tree_Node *root, Tree_Node *child) {

	root->children_num++;
	root->children = (Tree_Node**) realloc(root->children, 
									root->children_num* sizeof(Tree_Node**));
	root->children[root->children_num - 1] = child;
}

void print_string(char* str) {
	printf("%s ", str);
}

void print_char(char c) {
	printf("%c ", c);
}

void print_int(int i) {
	printf("%i\n", i);
}

void print_float(int f) {
	printf("%i\n", f);
}

void print_bool(int b) {
	printf("%s\n", b == 0 ? "FALSE" : "TRUE");
}

void print_token(struct lex_value* lex_val) {
	
	if (lex_val->token_type == KEYWORD || lex_val->token_type == OPERATOR || lex_val->token_type == IDENTIFIER) {
		print_string(lex_val->value.v_string);
	} else if (lex_val->token_type == SPECIAL_CHAR) {
		print_char(lex_val->value.v_char);
	} else if (lex_val->token_type == LITERAL) {
		switch (lex_val->literal_type) {
			case INT:
				print_int(lex_val->value.v_int);
				break;
			case FLOAT:
				print_float(lex_val->value.v_float);
				break;
			case CHAR:
				print_char(lex_val->value.v_char);
				break;
			case BOOL:
				print_bool(lex_val->value.v_bool);
				break;
			case STRING:
				print_string(lex_val->value.v_string);
				break;
		}
	}
}

void descompila(void *node);

void libera(void *node) ;

/*
	Temporary main to test the printing methods
*/

int main() {

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
	lex_val->value.v_int = 0;
	print_token(lex_val);

	printf("\n");
}