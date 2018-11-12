// João Vitor de Camargo
// Marcellus Farias

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/iloc.h"
#include "../include/codes.h"

void set_arg_to_freedom(iloc_arg* arg);
void free_op(iloc_operation* op);
void free_list_and_ops(iloc_op_list* list);

int op_counter = 0;
int num_freed_registers = 0;
iloc_arg** freed_registers = NULL;
int came_from_label = 0;

iloc_op_list* new_op_list() {
	iloc_op_list *list = (iloc_op_list*) malloc(sizeof(iloc_op_list));
	list->num_ops = 0;
	list->ops = NULL;
	return list;
}

iloc_op_list* concat_code(iloc_op_list* list1, iloc_op_list* list2) {
	iloc_op_list *mixed_list = new_op_list();
	int index;
	if (list1 != NULL) {
		for (index = 0; index < list1->num_ops; index++) {
			add_op(mixed_list, list1->ops[index]);
		}
	}
	if (list2 != NULL) {
		for (index = 0; index < list2->num_ops; index++) {
			add_op(mixed_list, list2->ops[index]);
		}
	}
	
	free_list_and_ops(list1);
	list1 = NULL;
	free_list_and_ops(list2);
	list2 = NULL;

	return mixed_list;
}

lbl_list* concat_labels(lbl_list* list1, lbl_list* list2) {
	lbl_list* mixed_list = new_label_list();
	int lbl_index;
	for (lbl_index = 0; lbl_index < list1->num_labels; lbl_index++) {
		add_label_to_list(mixed_list, strdup(list1->list[lbl_index]));
	}
	for (lbl_index = 0; lbl_index < list2->num_labels; lbl_index++) {
		add_label_to_list(mixed_list, strdup(list2->list[lbl_index]));
	}
	return mixed_list;
}

iloc_operation* new_op(int op_code) {
	iloc_operation *op = (iloc_operation*) malloc(sizeof(iloc_operation));
	op->op_code = op_code;
	op->num_args = 0;
	op->args = NULL;
	return op;
}

iloc_arg* new_arg(int type, void* argum) {
	iloc_arg *arg = (iloc_arg*) malloc(sizeof(iloc_arg));
	arg->type = type;
	if (type == CONSTANT) {
		arg->arg.int_const = *((int*) argum);
	} else {
		arg->arg.str_var = (char*) argum;
	}
	return arg;
}

void new_code(iloc_op_list* list) {
	list->ops = (iloc_operation**) malloc(sizeof(iloc_operation));
	return;
}

void add_op(iloc_op_list* list, iloc_operation* op) {
	if (list->ops == NULL) {		
		list->ops = (iloc_operation**) malloc(sizeof(iloc_operation));
	} else {
		list->ops = (iloc_operation**) realloc(list->ops, (list->num_ops+1) * sizeof(iloc_operation));
	} 
	list->ops[list->num_ops] = op;
	list->num_ops++;
}

void add_arg(iloc_operation* op, iloc_arg* arg) {
	if (op->args == NULL) {
		op->args = (iloc_arg**) malloc(sizeof(iloc_arg));
	} else {
		op->args = (iloc_arg**) realloc(op->args, (op->num_args+1) * sizeof(iloc_arg));
	}
	op->args[op->num_args] = arg;
	op->num_args++;
}

iloc_operation* new_1arg_op(int op_code, iloc_arg* arg1) {
	iloc_operation *op = new_op(op_code);
	add_arg(op, arg1);
	return op;
}

iloc_operation* new_2arg_op(int op_code, iloc_arg* arg1, iloc_arg* arg2) {
	iloc_operation *op = new_op(op_code);
	add_arg(op, arg1);
	add_arg(op, arg2);
	return op;
}

iloc_operation* new_3arg_op(int op_code, iloc_arg* arg1, iloc_arg* arg2, iloc_arg* arg3) {
	iloc_operation *op = new_op(op_code);
	add_arg(op, arg1);
	add_arg(op, arg2);
	add_arg(op, arg3);
	return op;
}

iloc_operation* new_nop() {
	return new_op(NOP);
}

char* new_reg() {
	char* reg = (char*) malloc(32);
	sprintf(reg, "%s%d", "r", reg_count);
	reg_count++;
	return reg;
}

char* new_lbl() {
	char* lbl = (char*) malloc(32);
	sprintf(lbl, "%s%d", "L", lbl_count);
	lbl_count++;
	return lbl;
}


lbl_list* new_label_list() {
	lbl_list* list = (lbl_list*) malloc(sizeof(lbl_list));
	list->num_labels = 0;
	list->list = NULL;
	return list;
}


void patch_arg(iloc_arg* arg, char* temp_label, char* real_label) {
	if (arg != NULL && arg->type == LABEL) {
		if (strcmp(arg->arg.str_var, temp_label) == 0) {
			arg->arg.str_var = real_label;
		}
	}
}

void patch_op(iloc_operation* op, lbl_list* list, char* real_label) {
	int lbl_index;
	int arg_index;
	if (list != NULL && op != NULL) {
		for (lbl_index = 0; lbl_index < list->num_labels; lbl_index++) {
			for (arg_index = 0; arg_index < op->num_args; arg_index++) {
				patch_arg(op->args[arg_index], list->list[lbl_index], real_label);
			}
		}
	}
}

void patch_list(iloc_op_list* code, lbl_list* list, char* real_label) {
	int op_index;
	if (code != NULL) {
		for (op_index = 0; op_index < code->num_ops; op_index++) {
			patch_op(code->ops[op_index], list, real_label);
		}
	}
}

void add_label_to_list(lbl_list* list, char* label) {
	if (list->num_labels == 0) {
		list->list = (char**) malloc(sizeof(char*));
	} else {
		list->list = (char**) realloc(list->list, (list->num_labels+1) * sizeof(char*));
	}
	list->list[list->num_labels] = label;
	list->num_labels++;
}


/* Instructions */

iloc_operation* halt() {
	return new_op(HALT);
}

iloc_operation* loadi(int value, char* reg) {
	return new_2arg_op(LOADI, new_arg(CONSTANT, (void*) &value), new_arg(REGISTER, reg));
}

iloc_operation* loadai(char* regop1, int value, char* regdst) {
	return new_3arg_op(LOADAI, new_arg(REGISTER, regop1), new_arg(CONSTANT, (void*) &value), new_arg(REGISTER, regdst));
}

iloc_operation* jumpi(char* label) {
	return new_1arg_op(JUMPI, new_arg(LABEL, label));
}

iloc_operation* store(char* regop1, char* regdst) {
	return new_2arg_op(STORE, new_arg(REGISTER, regop1), new_arg(REGISTER, regdst));
}

iloc_operation* storeai(char* regop1, int value, char* regdst) {
	return new_3arg_op(STOREAI, new_arg(REGISTER, regop1), new_arg(REGISTER, regdst), new_arg(CONSTANT, (void*) &value));
}

iloc_operation* and_op(char* regop1, char* regop2, char* regdst) {
	return new_3arg_op(AND, new_arg(REGISTER, regop1), new_arg(REGISTER, regop2), new_arg(REGISTER, regdst));
}

iloc_operation* add(char* regop1, char* regop2, char* regdst) {
	return new_3arg_op(ADD, new_arg(REGISTER, regop1), new_arg(REGISTER, regop2), new_arg(REGISTER, regdst));
}

iloc_operation* sub(char* regop1, char* regop2, char* regdst) {
	return new_3arg_op(SUB, new_arg(REGISTER, regop1), new_arg(REGISTER, regop2), new_arg(REGISTER, regdst));
}

iloc_operation* mult(char* regop1, char* regop2, char* regdst) {
	return new_3arg_op(MULT, new_arg(REGISTER, regop1), new_arg(REGISTER, regop2), new_arg(REGISTER, regdst));
}

iloc_operation* div_op(char* regop1, char* regop2, char* regdst) {
	return new_3arg_op(DIV, new_arg(REGISTER, regop1), new_arg(REGISTER, regop2), new_arg(REGISTER, regdst));
}

iloc_operation* cmp_gt(char* regop1, char* regop2, char* regdst) {
	return new_3arg_op(CMP_GT, new_arg(REGISTER, regop1), new_arg(REGISTER, regop2), new_arg(REGISTER, regdst));
}

iloc_operation* cmp_lt(char* regop1, char* regop2, char* regdst) {
	return new_3arg_op(CMP_LT, new_arg(REGISTER, regop1), new_arg(REGISTER, regop2), new_arg(REGISTER, regdst));
}

iloc_operation* cmp_le(char* regop1, char* regop2, char* regdst) {
	return new_3arg_op(CMP_LE, new_arg(REGISTER, regop1), new_arg(REGISTER, regop2), new_arg(REGISTER, regdst));
}

iloc_operation* cmp_ge(char* regop1, char* regop2, char* regdst) {
	return new_3arg_op(CMP_GE, new_arg(REGISTER, regop1), new_arg(REGISTER, regop2), new_arg(REGISTER, regdst));
}

iloc_operation* cmp_eq(char* regop1, char* regop2, char* regdst) {
	return new_3arg_op(CMP_EQ, new_arg(REGISTER, regop1), new_arg(REGISTER, regop2), new_arg(REGISTER, regdst));
}

iloc_operation* cmp_ne(char* regop1, char* regop2, char* regdst) {
	return new_3arg_op(CMP_NE, new_arg(REGISTER, regop1), new_arg(REGISTER, regop2), new_arg(REGISTER, regdst));
}

iloc_operation* cbr(char* regop1, char* lbl_true, char* lbl_false) {
	return new_3arg_op(CBR, new_arg(REGISTER, regop1), new_arg(LABEL, lbl_true), new_arg(LABEL, lbl_false));
}

iloc_operation* label(char* label_name) {
	return new_1arg_op(LABEL_INST, new_arg(LABEL, label_name));
}

/* Free + Print functions */

int is_supposed_to_free(char* arg_name) {
	if (strcmp(arg_name, "rfp") == 0 || strcmp(arg_name, "rbss") == 0)
		return 0;
	return 1;;
}

void add_to_freed_args(iloc_arg* arg) {
	if (arg == NULL)
		return;
	if (is_supposed_to_free(arg->arg.str_var)) {
		if (num_freed_registers == 0) {
			freed_registers = (iloc_arg**) malloc(sizeof(iloc_arg));
		} else {
			freed_registers = (iloc_arg**) realloc(freed_registers, (num_freed_registers+1) * sizeof(iloc_arg));
		}
		freed_registers[num_freed_registers] = arg;
		num_freed_registers++;
	}
}

int is_arg_freed(iloc_arg* arg) {
	int index;
	for (index = 0; index < num_freed_registers; index++) {
		if (strcmp(freed_registers[index]->arg.str_var, arg->arg.str_var) == 0) {
			return 1;
		}
	}
	return 0;
}

void read_arg(iloc_arg* arg) {
	if (arg->type == CONSTANT) {
		printf("%i", arg->arg.int_const);
	} else {
		printf("%s", arg->arg.str_var);
	}
}

void print_line_break() {
	if (op_counter > 0 && !came_from_label) {
		printf("\n");
	}
	op_counter++;
	came_from_label = 0;
}

void read_op(iloc_operation* op) {
	print_line_break();
	if(get_instruction_type(op->op_code) != LBL)
		printf("%s ", get_instruction_name(op->op_code));
	if (op->op_code != NOP) {
		switch(get_instruction_type(op->op_code)) {
			
			case ONE_IN_ONE_OUT:
				read_arg(op->args[0]);
				printf(" %s ", get_instruction_syntax(op->op_code));
				read_arg(op->args[1]);
				break;
			
			case ONE_IN_TWO_OUT:
				read_arg(op->args[0]);
				printf(" %s ", get_instruction_syntax(op->op_code));
				read_arg(op->args[1]);
				printf(", ");
				read_arg(op->args[2]);
				break;
			
			case TWO_IN_ONE_OUT:
				read_arg(op->args[0]);
				printf(", ");
				read_arg(op->args[1]);
				printf(" %s ", get_instruction_syntax(op->op_code));
				read_arg(op->args[2]);
				break;

			case ONE_OUT:
				printf("%s ", get_instruction_syntax(op->op_code));
				read_arg(op->args[0]);
				break;

			case LBL:
				read_arg(op->args[0]);
				printf(": ");
				came_from_label = 1;
				break;
			default: break;

		}
	}
}

void print_code(iloc_op_list* list) {
	if (list != NULL) {
		int op_index;
		for (op_index = 0; op_index < list->num_ops; op_index++) {
			if (list->ops[op_index] != NULL) {
				read_op(list->ops[op_index]);	
			}
		}
	} 
}

lbl_list* copy_label_list(lbl_list* list) {
	if (list == NULL)
		return NULL;
	lbl_list* new_list = (lbl_list*) malloc(sizeof(lbl_list));
	int index;

	new_list->num_labels = list->num_labels;
	if (list->num_labels > 0) {
		new_list->list = (char**) malloc(list->num_labels * sizeof(char*));
		for (index = 0; index < list->num_labels; index++) {
			new_list->list[index] = strdup(list->list[index]);
		}
	} else {
		new_list->list = NULL;
	}
	return new_list;
}

void free_label_list(lbl_list* list) {
	int index;
	for (index = 0; index < list->num_labels; index++) {
		free(list->list[index]);
		list->list[index] = NULL;
	}
	free(list);
	list = NULL;
}

void free_register_list() {
	int index;
	for (index = 0; index < num_freed_registers; index++) {
		if (freed_registers[index]->type == REGISTER) {
			if (freed_registers[index]->arg.str_var != NULL) {
				free(freed_registers[index]->arg.str_var);
				freed_registers[index]->arg.str_var = NULL;
			}
		}
		free(freed_registers[index]);
	}
	free(freed_registers);
	freed_registers = NULL;
	num_freed_registers = 0;
}

void free_op_list(iloc_op_list* list) {
	if (list != NULL) {
		int op_index;
		for (op_index = 0; op_index < list->num_ops; op_index++) {
			free_op(list->ops[op_index]);
		}
		free(list->ops);
		list->ops = NULL;
		free(list);
		list = NULL;
	}
	free_register_list();
}

void free_op(iloc_operation* op) {
	if (op != NULL) {
		int arg_index;
		for (arg_index = 0; arg_index < op->num_args; arg_index++) {
			set_arg_to_freedom(op->args[arg_index]);
		}
		free(op->args);
		op->args = NULL;
		free(op);
		op = NULL;
	}
}


void set_arg_to_freedom(iloc_arg* argum) {
	if (argum != NULL) {
		if (argum->type == REGISTER) {
			if (!is_arg_freed(argum)) {
				add_to_freed_args(argum);
			}
		} else {
			free(argum);
		}
		argum = NULL;
	}
}

void free_list_and_ops(iloc_op_list* list) {
	if (list != NULL) {
		free(list->ops);
		list->ops = NULL;
		free(list);
		list = NULL;
	}
}