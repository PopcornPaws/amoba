typedef struct Cursor {
	unsigned int x; // x coordinate of the cursor
	unsigned int y; // y coordinate of the cursor
	unsigned int ncols; // max x coordinate of cursor
	unsigned int nrows; // max y coordinate of cursor
	unsigned int player; // player switch (0-1 value)
	char marks[2]; // char array containing 'x' and 'o' (symbols can be arbitrary)
} Cursor;

unsigned int get_table_index(unsigned int x, unsigned int y, unsigned int ncolumns);

int is_winner(Cursor *c, char *table, unsigned int w);

int is_free(char *table, unsigned int index);
