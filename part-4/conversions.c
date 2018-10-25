#include "lexeme.h"
#include <stdio.h>

int can_convert(int a, int b) {
	if (a == INT || a == FLOAT || a == BOOL)
		if (b == INT || b == FLOAT || b == BOOL) {
			return TRUE;
		}
	return FALSE;
}