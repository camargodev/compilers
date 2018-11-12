#include <stdio.h>
#include <stdlib.h>
#include "../include/iloc.h"
#include "../include/codes.h"

int main() {
	iloc_op_list* list = new_op_list();
	iloc_op_list* list2 = new_op_list();
	lbl_list* true_list = new_label_list();
	int fourteen = 14;
	int sixhun = 600;

	add_label_to_list(true_list, new_lbl());
	add_label_to_list(true_list, new_lbl());
	add_label_to_list(true_list, new_lbl());
	add_label_to_list(true_list, new_lbl());
	iloc_arg* r0 = new_arg(REGISTER, new_reg());
	iloc_arg* r0c = new_arg(REGISTER, "r0");
	iloc_arg* r1 = new_arg(REGISTER, new_reg());
	iloc_arg* r2 = new_arg(REGISTER, new_reg());
	iloc_arg* r3 = new_arg(REGISTER, new_reg());
	iloc_arg* r4 = new_arg(REGISTER, new_reg());
	iloc_arg* r5 = new_arg(REGISTER, new_reg());
	iloc_arg* r6 = new_arg(REGISTER, new_reg());
	iloc_arg* r7 = new_arg(REGISTER, new_reg());
	iloc_arg* l0 = new_arg(LABEL, true_list->list[0]);
	iloc_arg* l1 = new_arg(LABEL, true_list->list[1]);
	iloc_arg* l2 = new_arg(LABEL, true_list->list[2]);
	iloc_arg* l3 = new_arg(LABEL, true_list->list[3]);
	iloc_arg* i1 = new_arg(CONSTANT, (void*) &fourteen);
	iloc_arg* i2 = new_arg(CONSTANT, (void*) &sixhun);

	iloc_operation* add1 = new_3arg_op(ADD, r0, r1, r2);
	iloc_operation* add2 = new_3arg_op(ADD, r0c, r2, r3);
	iloc_operation* sub1 = new_3arg_op(SUB, r3, l0, r4);
	iloc_operation* sub2 = new_3arg_op(SUB, r3, r2, r4);
	iloc_operation* add3 = new_3arg_op(ADDI, r0, i2, l1);
	iloc_operation* sub3 = new_3arg_op(SUB, r7, r2, r4);
	iloc_operation* nop1 = new_nop();
	iloc_operation* jmp1 = new_1arg_op(JUMP, l2);
	iloc_operation* mult = new_3arg_op(MULT, r3, r5, r6);
	iloc_operation* jmp2 = new_1arg_op(JUMPI, i1);
	iloc_operation* stri = new_3arg_op(STOREAI, l3, r5, r6);
	iloc_operation* nop2 = new_nop();
	
	add_op(list, add1);
	add_op(list, add2);
	add_op(list, sub1);
	add_op(list, sub2);
	add_op(list, add3);
	add_op(list, sub3);
	add_op(list, nop1);
	
	add_op(list2, jmp1);
	add_op(list2, mult);
	add_op(list2, jmp2);
	add_op(list2, stri);
	add_op(list2, nop2);

	iloc_op_list* final = concat_code(list, list2);

	print_code(final);
	patch_list(final, true_list, "lreal");
	print_code(final);

	free_op_list(final);
	free_label_list(true_list);
}