// João Vitor de Camargo
// Marcellus Farias

#include "../include/codes.h"

char* get_instruction_name(int code) {
	switch (code) {
		
		/*( Arithmetical expressions )*/
		case ADD: return "ADD";
		case SUB: return "SUB";
		case MULT: return "MULT";
		case DIV: return "DIV";
		case ADDI: return "ADDI";
		case SUBI: return "SUBI";
		case RSUBI: return "RSUBI";
		case MULTI: return "MULTI";
		case DIVI: return "DIVI";
		case RDIVI: return "RDIVI";

		
		/*( Shifts )*/
		case LSHIFT: return "LSHIFT";
		case LSHIFTI: return "LSHIFTI";
		case RSHIFT: return "RSHIFT";
		case RSHIFTI: return "RSHIFTI";

		
		/*( Memory operations )*/
		case LOAD: return "LOAD";
		case LOADAI: return "LOADAI";
		case LOADA0: return "LOADA0";
		case CLOAD: return "CLOAD";
		case CLOADAI: return "CLOADAI";
		case CLOADA0: return "CLOADA0";

		case STORE: return "STORE";
		case STOREAI: return "STOREAI";
		case STOREA0: return "STOREA0";
		case CSTORE: return "CSTORE";
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
		case CBR: return "CBR";

		
			/*( Jumps )*/
		case JUMPI: return "JUMPI";
		case JUMP: return "JUMP";

		
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


