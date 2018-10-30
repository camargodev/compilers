// João Vitor de Camargo
// Marcellus Farias

typedef struct error {
	int error_code;
	int line;
} Error;

Error* new_error(int error_code, int line);
void set_error(int error_code);
char* get_error_message(int error_code);