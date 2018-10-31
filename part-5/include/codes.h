// João Vitor de Camargo
// Marcellus Farias

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
#define LOADAI   16
#define LOADA0   17
#define CLOAD    18
#define CLOADAI  19
#define CLOADA0  20

#define STORE    21
#define STOREAI  22
#define STOREA0  23
#define CSTORE   24
#define CSTOREAI 25
#define CSTOREA0 26

/* Register copy operations */

#define I2I 27
#define C2C 28
#define C2I 29
#define I2C 30

/* Flow */

#define CMP_LT 31
#define CMP_LE 32
#define CMP_EQ 33
#define CMP_GE 34
#define CMP_GT 35
#define CMP_NE 36
#define CBR    37

/* Jumps */

#define JUMPI 38
#define JUMP  39

/* Logical */

#define AND  40
#define ANDI 41
#define OR   42
#define ORI  43
#define XOR  44
#define XORI 45

char* get_instruction_name(int code);