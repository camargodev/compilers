// João Vitor de Camargo
// Marcellus Farias

#include "../include/codes.h"

char* get_instruction_name(int code) {
	switch (code) {
		
		/*( Arithmetical expressions )*/
		case ADD:   return "ADD";
		case SUB:   return "SUB";
		case MULT:  return "MULT";
		case DIV:   return "DIV";
		case ADDI:  return "ADDI";
		case SUBI:  return "SUBI";
		case RSUBI: return "RSUBI";
		case MULTI: return "MULTI";
		case DIVI:  return "DIVI";
		case RDIVI: return "RDIVI";

		
		/*( Shifts )*/
		case LSHIFT:  return "LSHIFT";
		case LSHIFTI: return "LSHIFTI";
		case RSHIFT:  return "RSHIFT";
		case RSHIFTI: return "RSHIFTI";

		
		/*( Memory operations )*/
		case LOAD:    return "LOAD";
		case LOADAI:  return "LOADAI";
		case LOADA0:  return "LOADA0";
		case CLOAD:   return "CLOAD";
		case CLOADAI: return "CLOADAI";
		case CLOADA0: return "CLOADA0";

		case STORE:    return "STORE";
		case STOREAI:  return "STOREAI";
		case STOREA0:  return "STOREA0";
		case CSTORE:   return "CSTORE";
		case CSTOREAI: return "CSTOREAI";
		case CSTOREA0: return "CSTOREA0";

		
		/*( Register copy operations )*/
		case I2I: return "I2I";
		case C2C: return "C2C";
		case C2I: return "C2I";
		case I2C: return "I2C";

		
		/*( Flow )*/
		case CMP_LT: return "CMP_LT";
		case CMP_LE: return "CMP_LE";
		case CMP_EQ: return "CMP_EQ";
		case CMP_GE: return "CMP_GE";
		case CMP_GT: return "CMP_GT";
		case CMP_NE: return "CMP_NE";
		case CBR:    return "CBR";

		
			/*( Jumps )*/
		case JUMPI: return "JUMPI";
		case JUMP:  return "JUMP";

		
			/*( Logical )*/
		case AND: return "AND";
		case ANDI: return "ANDI";
		case OR: return "OR";
		case ORI: return "ORI";
		case XOR: return "XOR";
		case XORI: return "XORI";

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
	}
}


