// João Vitor de Camargo
// Marcellus Farias

/*
	A token can be:
	1) a keyword
	2) a special character
	3) a math operator
	4) an identifier
	5) a literal
*/

#define KEYWORD			0
#define SPECIAL_CHAR	1
#define OPERATOR		2
#define IDENTIFIER		3
#define LITERAL 		4

/*
	A literal can be:
	1) an integer number 
	2) a floating point number
	3) a character
	4) a boolean
	5) a string of characteres
*/

#define INT 	10
#define FLOAT 	11
#define CHAR 	12
#define BOOL 	13
#define STRING 	14

#define NOT_LITERAL		15

#define FALSE			000
#define TRUE			100

union Literal {
	int 	v_int;
	float 	v_float;
	char 	v_char;
	int 	v_bool;
	char* 	v_string;
};

/*
	O tipo do valor_lexico (e por consequência o valor que será
		retido) deve ser uma estrutura de dados que contém os
		seguintes campos:
		- número da linha do lexema
		- tipo do token
		- valor do token
*/

struct Lexeme {
	int 	line_number;
	int 	token_type;
	int 	literal_type;
	union 	Literal value;
};

/*
	Essa função recebe:
	- a linha do lexema
	- o tipo do token
	- o tipo do literal (ou NOT_LITERAL, se não for literal)
	- o valor

*/