#include "../include/lexeme.h"
#include "../include/conversions.h"
#include <stdio.h>

int can_convert(int a, int b) {
	if (a == INT || a == FLOAT || a == BOOL)
		if (b == INT || b == FLOAT || b == BOOL) {
			return TRUE;
		}
	return FALSE;
}

int get_conversion(int expected_type, int attr_type) {
	if (expected_type == INT) {
		switch(attr_type) {
			case FLOAT: return FLOAT_TO_INT;
			case BOOL: return BOOL_TO_INT;
			case INT: return NO_CONVERSION;
			default: return CONVERSION_ERROR;
		}
	} else if (expected_type == FLOAT) {
		switch(attr_type) {
			case INT: return INT_TO_FLOAT;
			case BOOL: return BOOL_TO_FLOAT;
			case FLOAT: return NO_CONVERSION;
			default: return CONVERSION_ERROR;
		}
	} else if (expected_type == BOOL) {
		switch(attr_type) {
			case INT: return INT_TO_BOOL;
			case FLOAT: return FLOAT_TO_BOOL;
			case BOOL: return NO_CONVERSION;
			default: return CONVERSION_ERROR;
		}
	} else {
		if (expected_type == attr_type) {
			return NO_CONVERSION;
		} else {
			return CONVERSION_ERROR;
		}
	}
}