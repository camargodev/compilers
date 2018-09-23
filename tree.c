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

void descompila(void *node);

void libera(void *node) ;

int main() {
	// To test the tree
	struct lex_value* lex_val;
	lex_val = (struct lex_value*) malloc(sizeof(struct lex_value));
	lex_val->line_number = 1;
	lex_val->token_type = KEYWORD;
	lex_val->literal_type = NOT_LITERAL;
	lex_val->value.v_string = "if";
	Tree_Node* node = new_node(lex_val);
}