#include "../include/lexeme.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Lexeme* copy_lexeme(struct Lexeme* token) {
	if (token != NULL) {
		struct Lexeme* lex = (struct Lexeme*) malloc(sizeof(struct Lexeme));
		lex->line_number = token->line_number;
		lex->token_type = token->token_type;
		lex->literal_type = token->literal_type;
		if (lex->token_type == LITERAL) {
			switch(token->literal_type) {
				case INT:
					lex->value.v_int = token->value.v_int; break;
				case FLOAT:
					lex->value.v_float = token->value.v_float; break;
				case CHAR:
					lex->value.v_char = token->value.v_char; break;
				case BOOL:
					lex->value.v_bool = token->value.v_bool; break;
				case STRING:
					lex->value.v_string = strdup(token->value.v_string); break;
			}
		} else if(token->token_type == SPECIAL_CHAR) {
			lex->value.v_char = token->value.v_char;
		} else {
			lex->value.v_string = strdup(token->value.v_string);
		}
		return lex;
	} else {
		return NULL;
	}
}