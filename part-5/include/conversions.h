#define CONVERSION_ERROR	-1
#define NO_CONVERSION		0
#define INT_TO_FLOAT 		1
#define INT_TO_BOOL			2
#define FLOAT_TO_BOOL		3
#define FLOAT_TO_INT		4
#define BOOL_TO_INT			5
#define BOOL_TO_FLOAT		6

int can_convert(int a, int b);
int get_conversion(int expected_type, int attr_type);
int infer_without_error(int type_a, int type_b);
int infer(int type_a, int type_b);