// João Vitor de Camargo
// Marcellus Farias

/*Possible operation types */
#define ONE_IN_ONE_OUT 1010
#define ONE_IN_TWO_OUT 1020
#define TWO_IN_ONE_OUT 2010
#define ONE_OUT        0010
#define LBL		   	   1000

/* Instructions */
#define NOP  0

/* Arithmetical expressions */

#define ADD    1
#define SUB    2
#define MULT   3
#define DIV    4
#define ADDI   5
#define SUBI   6
#define RSUBI  7
#define MULTI  8
#define DIVI   9
#define RDIVI 10

/* Shifts */

#define LSHIFT  11
#define LSHIFTI 12
#define RSHIFT  13
#define RSHIFTI 14

/* Memory operations */

#define LOAD     15
#define LOADI    16
#define LOADAI   17
#define LOADA0   18
#define CLOAD    19
#define CLOADAI  20
#define CLOADA0  21

#define STORE    22
#define STOREAI  23
#define STOREA0  24
#define CSTORE   25
#define CSTOREAI 26
#define CSTOREA0 27

/* Register copy operations */

#define I2I 28
#define C2C 29
#define C2I 30
#define I2C 31

/* Flow */

#define CMP_LT 32
#define CMP_LE 33
#define CMP_EQ 34
#define CMP_GE 35
#define CMP_GT 36
#define CMP_NE 37
#define CBR    38

/* Jumps */

#define JUMPI 39
#define JUMP  40

/* Logical */

#define AND  41
#define ANDI 42
#define OR   43
#define ORI  44
#define XOR  45
#define XORI 46

/* Label */
#define LABEL_INST 47

char* get_instruction_name(int code);
int   get_instruction_type(int code);