// João Vitor de Camargo
// Marcellus Farias

typedef struct node {
	struct 	Lexeme* token;
	int 	children_num;
	struct 	node **children;
} Node;

Node* new_node(struct Lexeme* token);

void add_node(Node *root, Node *child);

void print_token(struct Lexeme* lex_val);

/*
	The following functions may have
	automated use, so the portugues name
	will be preserved.
*/

void descompila(void *node);

void libera(void *node) ;