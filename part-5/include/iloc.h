// João Vitor de Camargo
// Marcellus Farias

/*  Just integer constants and
	identifiers will be used for now */
union argument {
	int 	int_const;
	char* 	str_var;
};

/* Possible values for iloc_arg->type */
#define CONSTANT 122
#define LABEL	 123
#define REGISTER 124

typedef struct i_arg {
	int type;
	union argument arg; 
} iloc_arg;

typedef struct i_operation {
	int op_code;
	int num_args;
	iloc_arg** args;
} iloc_operation;

typedef struct i_op_list {
	int num_ops;
	iloc_operation** ops;
} iloc_op_list;

iloc_op_list* new_op_list();
void add_op(iloc_op_list* list, iloc_operation* op);
void add_arg(iloc_operation* op, iloc_arg* arg);
void free_op_list(iloc_op_list* list);