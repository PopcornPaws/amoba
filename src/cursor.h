#include <stdbool.h>

typedef struct Cursor {
	int x; // x coordinate of the cursor
	int y; // y coordinate of the cursor
	unsigned int player; // player switch (0-1 value)
	char marks[2]; // char array containing 'x' and 'o' (symbols can be arbitrary)
} Cursor;

unsigned int get_table_index(Cursor *c, unsigned int ncolumns);

bool is_winner(Cursor *c, char *table, unsigned int length, unsigned int w);

bool is_free(char *table, unsigned int index);
