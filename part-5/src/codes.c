// João Vitor de Camargo
// Marcellus Farias

#include "../include/codes.h"

char* get_instruction_name(int code) {
	switch (code) {

		case HALT:	return "halt";
		
		/*( Arithmetical expressions )*/
		case ADD:   return "add";
		case SUB:   return "sub";
		case MULT:  return "mul";
		case DIV:   return "div";
		case ADDI:  return "addI";
		case SUBI:  return "subI";
		case RSUBI: return "rsubI";
		case MULTI: return "multI";
		case DIVI:  return "divI";
		case RDIVI: return "rdivI";

		
		/*( Shifts )*/
		case LSHIFT:  return "lshift";
		case LSHIFTI: return "lshiftI";
		case RSHIFT:  return "rshift";
		case RSHIFTI: return "rshiftI";

		
		/*( Memory operations )*/
		case LOAD:    return "load";
		case LOADI:   return "loadI";
		case LOADAI:  return "loadAI";
		case LOADA0:  return "loadA0";
		case CLOAD:   return "cload";
		case CLOADAI: return "cloadAI";
		case CLOADA0: return "cloadA0";

		case STORE:    return "store";
		case STOREAI:  return "storeAI";
		case STOREA0:  return "storeA0";
		case CSTORE:   return "cstore";
		case CSTOREAI: return "cstoreAI";
		case CSTOREA0: return "cstoreA0";

		
		/*( Register copy operations )*/
		case I2I: return "i2i";
		case C2C: return "c2c";
		case C2I: return "c2i";
		case I2C: return "i2c";

		
		/*( Flow )*/
		case CMP_LT: return "cmp_LT";
		case CMP_LE: return "cmp_LE";
		case CMP_EQ: return "cmp_EQ";
		case CMP_GE: return "cmp_GE";
		case CMP_GT: return "cmp_GT";
		case CMP_NE: return "cmp_NE";
		case CBR:    return "cbr";

		
			/*( Jumps )*/
		case JUMPI: return "jumpI";
		case JUMP:  return "jump";

		
			/*( Logical )*/
		case AND: 	return "and";
		case ANDI: 	return "andI";
		case OR: 	return "or";
		case ORI: 	return "orI";
		case XOR: 	return "xor";
		case XORI: 	return "xorI";

		case LABEL_INST: return "LABEL_INST";

		default: return "NOP";
	}
}

int get_instruction_type(int code) {
	switch (code) {
		
		/*( Arithmetical expressions )*/
		case ADD:   return TWO_IN_ONE_OUT;
		case SUB:   return TWO_IN_ONE_OUT;
		case MULT:  return TWO_IN_ONE_OUT;
		case DIV:   return TWO_IN_ONE_OUT;
		case ADDI:  return TWO_IN_ONE_OUT;
		case SUBI:  return TWO_IN_ONE_OUT;
		case RSUBI: return TWO_IN_ONE_OUT;
		case MULTI: return TWO_IN_ONE_OUT;
		case DIVI:  return TWO_IN_ONE_OUT;
		case RDIVI: return TWO_IN_ONE_OUT;

		
		/*( Shifts )*/
		case LSHIFT:  return TWO_IN_ONE_OUT;
		case LSHIFTI: return TWO_IN_ONE_OUT;
		case RSHIFT:  return TWO_IN_ONE_OUT;
		case RSHIFTI: return TWO_IN_ONE_OUT;

		
		/*( Memory operations )*/
		case LOAD:    return ONE_IN_ONE_OUT;
		case LOADI:   return ONE_IN_ONE_OUT;
		case LOADAI:  return TWO_IN_ONE_OUT;
		case LOADA0:  return TWO_IN_ONE_OUT;
		case CLOAD:   return ONE_IN_ONE_OUT;
		case CLOADAI: return TWO_IN_ONE_OUT;
		case CLOADA0: return TWO_IN_ONE_OUT;

		case STORE:    return ONE_IN_ONE_OUT;
		case STOREAI:  return ONE_IN_TWO_OUT;
		case STOREA0:  return ONE_IN_TWO_OUT;
		case CSTORE:   return ONE_IN_ONE_OUT;
		case CSTOREAI: return ONE_IN_TWO_OUT;
		case CSTOREA0: return ONE_IN_TWO_OUT;

		
		/*( Register copy operations )*/
		case I2I: return ONE_IN_ONE_OUT;
		case C2C: return ONE_IN_ONE_OUT;
		case C2I: return ONE_IN_ONE_OUT;
		case I2C: return ONE_IN_ONE_OUT;

		
		/*( Flow )*/
		case CMP_LT: return TWO_IN_ONE_OUT;
		case CMP_LE: return TWO_IN_ONE_OUT;
		case CMP_EQ: return TWO_IN_ONE_OUT;
		case CMP_GE: return TWO_IN_ONE_OUT;
		case CMP_GT: return TWO_IN_ONE_OUT;
		case CMP_NE: return TWO_IN_ONE_OUT;
		case CBR:    return ONE_IN_TWO_OUT;

		
		/*( Jumps )*/
		case JUMPI: return ONE_OUT;
		case JUMP:  return ONE_OUT;

		
		/*( Logical )*/
		case AND:  return TWO_IN_ONE_OUT;
		case ANDI: return TWO_IN_ONE_OUT;
		case OR:   return TWO_IN_ONE_OUT;
		case ORI:  return TWO_IN_ONE_OUT;
		case XOR:  return TWO_IN_ONE_OUT;
		case XORI: return TWO_IN_ONE_OUT;

		case LABEL_INST: return LBL;
	}
}

char* get_instruction_syntax(int code) {
	switch (code) {
				
		/*( Flow )*/
		case CMP_LT: 
		case CMP_LE: 
		case CMP_EQ: 
		case CMP_GE: 
		case CMP_GT: 
		case CMP_NE: 
		case CBR:    return "->";

		
		/*( Jumps )*/
		case JUMPI: 
		case JUMP:  return "->";

		default:	return "=>";
	}
}


