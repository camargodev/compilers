// João Vitor de Camargo
// Marcellus Farias

typedef struct node {
	struct 	lex_value* token;
	int 	children_num;
	struct 	node **children;
} Tree_Node;

Tree_Node* new_node(struct lex_value* token);

void add_node(Tree_Node *root, Tree_Node *child);

/*
	The following functions may have
	automated use, so the portugues name
	will be preserved.
*/

void descompila(void *node);

void libera(void *node) ;