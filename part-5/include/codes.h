// João Vitor de Camargo
// Marcellus Farias

#define NOP  00000

/* Arithmetical expressions */

#define ADD   00001
#define SUB   00002
#define MULT  00003
#define DIV   00004
#define ADDI  00005
#define SUBI  00006
#define RSUBI 00007
#define MULTI 00008
#define DIVI  00009
#define RDIVI 00010

/* Shifts */

#define LSHIFT  00011
#define LSHIFTI 00012
#define RSHIFT  00013
#define RSHIFTI 00014

/* Memory operations */

#define LOAD     00015
#define LOADAI   00016
#define LOADA0   00017
#define CLOAD    00018
#define CLOADAI  00019
#define CLOADA0  00020

#define STORE    00021
#define STOREAI  00022
#define STOREA0  00023
#define CSTORE   00024
#define CSTOREAI 00025
#define CSTOREA0 00026

/* Register copy operations */

#define I2I 00027
#define C2C 00028
#define C2I 00029
#define I2C 00030

/* Flow */

#define CMP_LT 00031
#define CMP_LE 00032
#define CMP_EQ 00033
#define CMP_GE 00034
#define CMP_GT 00035
#define CMP_NE 00036
#define CBR    00037

/* Jumps */

#define JUMPI 00038
#define JUMP  00039

/* Logical */

#define AND  00040
#define ANDI 00041
#define OR   00042
#define ORI  00043
#define XOR  00044
#define XORI 00045

