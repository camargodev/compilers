// João Vitor de Camargo
// Marcellus Farias

#include <stdio.h>
#include <stdlib.h>
#include "lexeme.h"
#include "tree.h"

#define NO_CHILDREN		0

void print_string(char* str);
void print_special_char(char c);
void print_char(char c);
void print_int(int i);
void print_float(float f);
void print_bool(int b);
void adicionaPtrNode(Node* newNode);


Node **arrayNodes;
extern struct Lexeme **arrayTokens;

Node* new_node(struct Lexeme* token) {
	
	Node* node = malloc(sizeof(Node));
	
	node->token = token;
	node->children_num = NO_CHILDREN;
	node->children = (Node**) malloc(sizeof(Node**));

	return node;
}

void add_node(Node *root, Node *child) {

	root->children_num++;
	root->children = (Node**) realloc(root->children, 
									root->children_num* sizeof(Node**));
	
	root->children[root->children_num - 1] = child;

	adicionaPtrNode(child);
}

void adicionaPtrNode(Node* newNode)
{
	int numPointers;

	//root->children = (Node**) realloc(root->children, 
	//								root->children_num* sizeof(Node**));

	if(arrayNodes == NULL)
	{
		//printf("arraNodes é NULL\n");
		arrayNodes = (Node **)malloc(sizeof(Node **));	
		arrayNodes[0] = newNode;
	}
	else
	{
		numPointers = sizeof(**arrayNodes) / sizeof(Node);

		arrayNodes = (Node **)realloc(arrayNodes, numPointers * sizeof(Node **) + sizeof(Node **));	

		printf("size realloc: %ld\n", numPointers * sizeof(Node **) + sizeof(Node **));

		printf("numPointers: %i\n", numPointers);
	
		printf("sizeof arrayNodes **: %ld\n", sizeof(**arrayNodes));
		printf("sizeof Node**: %ld\n", sizeof(Node **));
		printf("sizeof Node*: %ld\n", sizeof(Node *));
		printf("sizeof Node: %ld\n", sizeof(Node));

		print_token(arrayNodes[numPointers - 1]->token);
	
		arrayNodes[numPointers - 1] = newNode;		
	}
}

void printArrayNodes()
{
	int numPointers = sizeof(arrayNodes) / sizeof(Node);
	int i = 0;
	Node* node;
	
	for(i = 0; i < numPointers; i++)
	{
		*node = *arrayNodes[i * sizeof(Node)];
		printf("Cheguei aqui\n");
		print_token(node->token);
	}
}

void print_token(struct Lexeme* lex_val) {
	
	if (lex_val->token_type == KEYWORD || lex_val->token_type == OPERATOR || lex_val->token_type == IDENTIFIER) {
		print_string(lex_val->value.v_string);
	} else if (lex_val->token_type == SPECIAL_CHAR) {
		print_special_char(lex_val->value.v_char);
		
		if (lex_val->value.v_char == '{' || lex_val->value.v_char == '}' || lex_val->value.v_char == ';')
			printf("\n"); 
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

void descompila(void *node) {

	Node *tree_node = (Node*) node;

	if (tree_node != NULL) {
	
		int children_counter = tree_node->children_num;
		
		if (tree_node->token != NULL) {
			print_token(tree_node->token);
		}
		
		while(children_counter > NO_CHILDREN) {
			descompila(tree_node->children[tree_node->children_num - children_counter]);
			children_counter--;
		}
	}
}

void libera(void *node) {
	
	//printArrayNodes();

	Node *tree_node = (Node*) node;

	if (tree_node != NULL) {
	
		int children_counter = tree_node->children_num;


		while(children_counter > NO_CHILDREN) {
			libera(tree_node->children[tree_node->children_num - children_counter]);
			children_counter--;
		}

		if (tree_node->token != NULL) {
			if (tree_node->token->token_type == KEYWORD
				|| tree_node->token->token_type == OPERATOR
				|| tree_node->token->token_type == IDENTIFIER) {
				free(tree_node->token->value.v_string);
			} else if (tree_node->token->token_type == LITERAL) {			
				switch (tree_node->token->literal_type) {
					case STRING:
						free(tree_node->token->value.v_string);
						break;
				}
			}
			free(tree_node->token);
		}

		free(tree_node->children);
		free(tree_node);

		free(*arrayNodes);
		free(*arrayTokens);
	} 

}

void print_string(char* str) {
	printf("%s ", str);
}

void print_special_char(char c) {
	printf("%c ", c);
}

void print_char(char c) {
	printf("\'%c\' ", c);
}

void print_int(int i) {
	printf("%i ", i);
}

void print_float(float f) {
	printf("%f ", f);
}

void print_bool(int b) {
	printf("%s ", b == FALSE ? "false" : "true");
}