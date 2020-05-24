#include "cursor.h"

unsigned int get_table_index(Cursor *c, unsigned int ncolumns) {
	return c -> x + c -> y * ncolumns;
}

bool is_winner(Cursor *c, char *table, unsigned int length, unsigned int w) {
	return true;
}

bool is_free(char *table, unsigned int index) {

	return table[index] == ' ';
}
