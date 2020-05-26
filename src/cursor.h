typedef struct Cursor {
	int x; // x coordinate of the cursor
	int y; // y coordinate of the cursor
	int ncols; // max x coordinate of cursor
	int nrows; // max y coordinate of cursor
	int marks_to_win; // max y coordinate of cursor
	int rounds_played; // rounds played so far
	int player; // player switch (0-1 value)
	char marks[3]; // char array containing 'x' and 'o' (symbols can be arbitrary)
} Cursor;

int get_table_index(int x, int y, int ncolumns);

int is_winner(Cursor *c, char *table);

int is_free(char *table, int index);
