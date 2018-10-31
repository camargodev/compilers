#include <stdio.h>
#include <stdlib.h>
#include "../include/iloc.h"
#include "../include/codes.h"

int main() {
	iloc_op_list* list = new_op_list();

	int fourteen = 14;
	int sixhun = 600;

	iloc_arg* r0 = new_arg(REGISTER, "r0");
	iloc_arg* r1 = new_arg(REGISTER, "r1");
	iloc_arg* r2 = new_arg(REGISTER, "r2");
	iloc_arg* r3 = new_arg(REGISTER, "r3");
	iloc_arg* r4 = new_arg(REGISTER, "r4");
	iloc_arg* r5 = new_arg(REGISTER, "r5");
	iloc_arg* r6 = new_arg(REGISTER, "r6");
	iloc_arg* r7 = new_arg(REGISTER, "r7");
	iloc_arg* i1 = new_arg(CONSTANT, (void*) &fourteen);
	iloc_arg* i2 = new_arg(CONSTANT, (void*) &sixhun);

	iloc_operation* add1 = new_3arg_op(ADD, r0, r1, r2);
	iloc_operation* add2 = new_3arg_op(ADD, r0, r2, r3);
	iloc_operation* sub1 = new_3arg_op(SUB, r3, r2, r4);
	iloc_operation* sub2 = new_3arg_op(SUB, r3, r2, r4);
	iloc_operation* add3 = new_3arg_op(ADD, r0, i2, r3);
	iloc_operation* sub3 = new_3arg_op(SUB, r7, r2, r4);
	iloc_operation* nop1 = new_nop();
	iloc_operation* jump1 = new_2arg_op(JUMP, r4, r5);
	iloc_operation* mult = new_3arg_op(MULT, r3, r5, r6);
	iloc_operation* jump2 = new_2arg_op(JUMP, r2, i1);
	iloc_operation* nop2 = new_nop();
	
	add_op(list, add1);
	add_op(list, add2);
	add_op(list, sub1);
	add_op(list, sub2);
	add_op(list, add3);
	add_op(list, sub3);
	add_op(list, nop1);
	add_op(list, jump1);
	add_op(list, mult);
	add_op(list, jump2);
	add_op(list, nop2);

	print_code(list);

	free_op_list(list);
}