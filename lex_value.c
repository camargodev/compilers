// João Vitor de Camargo
// Marcellus Farias

#include <stdlib.h>
// string.h is necessary for using strdup
#include <string.h>
#include "lex_value.h"

/*
	Implementation of the method 
		defined on header lex_val.h
*/
struct lex_value* new_lex_value(int line_number, int token_type, int literal_type, void* value) {
	
	struct lex_value* lex_val = (struct lex_value*) malloc(sizeof(struct lex_value));
	
	lex_val->line_number = line_number;
	lex_val->token_type = token_type;
	lex_val->literal_type = literal_type;
	
	switch (literal_type) {
			case INT:
				lex_val->value.v_int 	= *((int*) value);
				break;
			case FLOAT:
				lex_val->value.v_float 	= *((float*) value);
				break;
			case CHAR:
				lex_val->value.v_char 	= *((char*) value);
				break;
			case BOOL:
				lex_val->value.v_bool 	= *((int*) value);
				break;
			case STRING:
				lex_val->value.v_string = strdup((char*) value);
				break;
			case NOT_LITERAL:
				lex_val->value.v_string = strdup((char*) value);
				break;
	}

	return lex_val;
}
