// João Vitor de Camargo
// Marcellus Farias

#include <stdio.h>
#include <stdlib.h>
#include "../include/iloc.h"

void free_arg(iloc_arg* arg);
void free_op(iloc_operation* op);

iloc_op_list* new_op_list() {
	iloc_op_list *list = (iloc_op_list*) malloc(sizeof(iloc_op_list));
	list->num_ops = 0;
	list->ops = NULL;
	return list;
}

void add_op(iloc_op_list* list, iloc_operation* op) {
	if (list->ops == NULL) {
		list->ops = (iloc_operation**) malloc(sizeof(iloc_operation));
	} else {
		list->ops = (iloc_operation**) realloc(list->ops, list->num_ops * sizeof(iloc_operation));
	} 
	list->ops[list->num_ops] = op;
	list->num_ops++;
}

void add_arg(iloc_operation* op, iloc_arg* arg) {
	if (op->args == NULL) {
		op->args = (iloc_arg**) malloc(sizeof(iloc_arg));
	} else {
		op->args = (iloc_arg**) realloc(op->args, op->num_args * sizeof(iloc_arg));
	}
	op->args[op->num_args] = arg;
	op->num_args++;
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
}

void free_op(iloc_operation* op) {
	if (op != NULL) {
		int arg_index;
		for (arg_index = 0; arg_index < op->num_args; arg_index++) {
			free_arg(op->args[arg_index]);
		}
		free(op->args);
		op->args = NULL;
		free(op);
		op = NULL;
	}
}

void free_arg(iloc_arg* arg) {
	if (arg != NULL) {
		if (arg->type == CONSTANT || arg->type == LABEL) {
			free(arg->arg.str_var);
			arg->arg.str_var = NULL;
		}
		free(arg);
		arg = NULL;
	}
}