// João Vitor de Camargo
// Marcellus Farias

#include <stdlib.h>
#include <stdio.h>
#include "../include/error.h"

extern int yylineno;
Error* error = NULL;

Error* new_error(int error_code, int line) {
	Error* err = malloc(sizeof(Error));
	err->error_code = error_code;
	err->line = line;
	return err;
}

char* get_error_message(int error_code) {
	switch(error_code) {
		case ERR_UNDECLARED:
			return "Not previously declared";
		case ERR_DECLARED:
			return "Already declared";

		case ERR_VARIABLE:
			return "Bad usage of variable";
		case ERR_VECTOR:
			return "Bad usage of vector";
		case ERR_FUNCTION:
			return "Bad usage of function";
		case ERR_USER:
			return "Bad usage of user type";

		case ERR_WRONG_TYPE:
			return "Wrong type";
		case ERR_STRING_TO_X:
			return "String used incorrectly";
		case ERR_CHAR_TO_X:
			return "Char used incorrectly";
		case ERR_USER_TO_X:
			return "User type used incorrectly";

		case ERR_MISSING_ARGS:
			return "Missing arguments for function";
		case ERR_EXCESS_ARGS:
			return "Too many arguments for function";
		case ERR_WRONG_TYPE_ARGS:
			return "A function argument has wrong type";

		case ERR_WRONG_PAR_INPUT:
			return "Wrong type for input";
		case ERR_WRONG_PAR_OUTPUT:
			return "Wrong type for output";
		case ERR_WRONG_PAR_RETURN:
			return "Wrong type for return";
	}
}

void set_error(int error_code) {
	if(error == NULL) {
		error = new_error(error_code, yylineno);
	}
}

int raise_error(int print_error) {
	if (error != NULL) {
		int error_code = error->error_code;
		if (print_error)
			printf("ERROR %i - line %i = %s\n", error->error_code, error->line, get_error_message(error->error_code));
		free(error);
		return error_code;
	}
	return 0;
}