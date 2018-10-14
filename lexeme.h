// João Vitor de Camargo
// Marcellus Farias

#ifndef LEXEME_H
#define LEXEME_H

/*
	A token can be:
	1) a keyword
	2) a special character
	3) a math operator
	4) an identifier
	5) a literal
*/

#define KEYWORD			100
#define SPECIAL_CHAR	101
#define OPERATOR		102
#define IDENTIFIER		103
#define LITERAL 		104

/*
	A literal can be:
	1) an integer number 
	2) a floating point number
	3) a character
	4) a boolean
	5) a string of characteres
*/

#define INT 	105
#define FLOAT 	106
#define CHAR 	107
#define BOOL 	108
#define STRING 	109

#define NOT_LITERAL		110

#define FALSE			0
#define TRUE			1

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

typedef struct Lexeme {
	int 	line_number;
	int 	token_type;
	int 	literal_type;
	union 	Literal value;
} Lexeme;

/*
	Essa função recebe:
	- a linha do lexema
	- o tipo do token
	- o tipo do literal (ou NOT_LITERAL, se não for literal)
	- o valor

*/

#endif