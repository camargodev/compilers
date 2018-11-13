// João Vitor de Camargo
// Marcellus Farias

#include <stdio.h>
#include <stdlib.h>
#include "../include/lexeme.h"
#include "../include/iloc.h"
#include "../include/tree.h"
#include "../include/conversions.h"

#define NO_CHILDREN		0

char* get_name(int type);
void print_string(char* str);
void print_special_char(char c);
void print_char(char c);
void print_int(int i);
void print_float(float f);
void print_bool(int b);

Node* new_node(struct Lexeme* token) {
	
	Node* node = malloc(sizeof(Node));
	
	node->token = token;
	node->children_num = NO_CHILDREN;
	node->type = UNDECLARED_TYPE;
	node->user_type = NULL;
	node->code = NULL;
	node->result_reg = NULL;
	node->conversion = NO_CONVERSION;
	node->point = -1;
	node->is_literal = FALSE;
	node->children = (Node**) malloc(sizeof(Node**));
	node->true_list = NULL;
	node->false_list = NULL;

	return node;
}

void set_node_type(Node* token, int type) {
	token->type = type;
}

void set_node_conversion(Node* token, int conversion) {
	token->conversion = conversion;
}

void add_node(Node *root, Node *child) {

	root->children_num++;
	root->children = (Node**) realloc(root->children, 
									root->children_num* sizeof(Node**));
	
	root->children[root->children_num - 1] = child;
}

void print_token(struct Lexeme* lex_val) {
	printf("\n"); 
	if (lex_val->token_type == KEYWORD || lex_val->token_type == OPERATOR || lex_val->token_type == IDENTIFIER) {
		print_string(lex_val->value.v_string);
	} else if (lex_val->token_type == SPECIAL_CHAR) {
		print_special_char(lex_val->value.v_char);
		//if (lex_val->value.v_char == '{' || lex_val->value.v_char == '}' || lex_val->value.v_char == ';')
		//	printf("\n"); 
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
			if (tree_node->type != -1)
				printf(" : %s", get_name(tree_node->type));
			if (tree_node->conversion != NO_CONVERSION)
				printf(" - Conv = %i", tree_node->conversion);
		}
		
		while(children_counter > NO_CHILDREN) {
			descompila(tree_node->children[tree_node->children_num - children_counter]);
			children_counter--;
		}
	}
}

void libera(void *node) {
	
	Node *tree_node = (Node*) node;

	if (tree_node != NULL) {
	
		int children_counter = tree_node->children_num;


		while(children_counter > NO_CHILDREN) {
			libera(tree_node->children[tree_node->children_num - children_counter]);
			children_counter--;
		}

		if (tree_node->token != NULL) {
			if (tree_node->token->token_type == KEYWORD || tree_node->token->token_type == OPERATOR || tree_node->token->token_type == IDENTIFIER) {
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

		if (tree_node->true_list != NULL) {
			free_label_list(tree_node->true_list);
			tree_node->true_list = NULL;
		}

		if (tree_node->false_list != NULL) {
			free_label_list(tree_node->false_list);
			tree_node->false_list = NULL;
		}

		if (tree_node->result_reg != NULL) {
			tree_node->result_reg = NULL;
		}

		free(tree_node->children);
		free(tree_node);
	} 

}

char* get_name(int type) {
	switch (type) {
		case INT:
			return "int";
		case FLOAT:
			return "float";
		case BOOL:
			return "bool";
		case CHAR:
			return "char";
		case STRING:
			return "string";
		case USER_TYPE:
			return "user type";
		default:
			return "invalid";
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