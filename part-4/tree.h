// João Vitor de Camargo
// Marcellus Farias

typedef struct node {
	struct 	Lexeme* token;
	int		conversion;
	int		type;
	char*	user_type;
	int		is_literal;
	int		point;
	int 	children_num;
	struct 	node **children;
} Node;

Node* new_node(struct Lexeme* token);

void set_node_type(Node* token, int type);

void set_node_conversion(Node* token, int conversion);

void add_node(Node *root, Node *child);

void print_token(struct Lexeme* lex_val);

/*
	The following functions may have
	automated use, so the portugues name
	will be preserved.
*/

void descompila(void *node);

void libera(void *node) ;