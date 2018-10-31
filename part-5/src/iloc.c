// João Vitor de Camargo
// Marcellus Farias

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/iloc.h"
#include "../include/codes.h"

void set_arg_to_freedom(iloc_arg* arg);
void free_op(iloc_operation* op);

int num_freed_registers = 0;
iloc_arg** freed_registers = NULL;

iloc_op_list* new_op_list() {
	iloc_op_list *list = (iloc_op_list*) malloc(sizeof(iloc_op_list));
	list->num_ops = 0;
	list->ops = NULL;
	return list;
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

void add_to_freed_args(iloc_arg* arg) {
	if (num_freed_registers == 0) {
		freed_registers = (iloc_arg**) malloc(sizeof(iloc_arg));
	} else {
		freed_registers = (iloc_arg**) realloc(freed_registers, (num_freed_registers+1) * sizeof(iloc_arg));
	}
	freed_registers[num_freed_registers] = arg;
	num_freed_registers++;
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

void print_code(iloc_op_list* list) {
	int op_index;
	for (op_index = 0; op_index < list->num_ops; op_index++) {
		iloc_operation *tmp_op = list->ops[op_index];
		printf("%s ", get_instruction_name(tmp_op->op_code));
		if (tmp_op->op_code != NOP) {
			if (tmp_op->num_args == 3) {
				printf("%s, %s, %s", tmp_op->args[0]->arg.str_var, tmp_op->args[1]->arg.str_var, tmp_op->args[2]->arg.str_var);
			} else if (tmp_op->num_args == 2) {
				printf("%s, %s", tmp_op->args[0]->arg.str_var, tmp_op->args[1]->arg.str_var);
			}
		}
		tmp_op = NULL;
		printf("\n");
	}
}

void free_register_list() {
	int index;
	for (index = 0; index < num_freed_registers; index++) {
		free(freed_registers[index]);
	}
	free(freed_registers);
	freed_registers = NULL;
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
		if (!is_arg_freed(argum)) {
			if (argum->type != CONSTANT) {
				add_to_freed_args(argum);
			}
		}
		argum = NULL;
	}
}