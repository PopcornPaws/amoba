#include <stdio.h>
#include <string.h>
#include <curses.h>

typedef struct Cursor {
	unsigned int x; // x coordinate of the cursor
	unsigned int y; // y coordinate of the cursor
	unsigned int player; // player switch (0-1 value)
	char marks[2]; // char array containing 'x' and 'o' (symbols can be arbitrary)
} Cursor;

void main(void) {
	//printf("How many lines do you need?\n");
	//scanf("%d", &nlines); 
	//printf("How many rows do you need?\n");
	//scanf("%d", &rows); 
	int nlines = 5;
	int ncolumns = 5;

	initscr(); // initialize curses
	noecho(); // don't echo keystrokes (so it won't output what the user is typing)
	raw(); // disable all default key commands (e.g. Ctrl + c)
	start_color();

	init_pair(1, COLOR_BLUE, COLOR_WHITE);
	init_pair(2, COLOR_RED, COLOR_WHITE);

	keypad(stdscr, TRUE); // enable special keys (such as F1 to exit)

	WINDOW *win = newwin(nlines, ncolumns, nlines / 2, ncolumns / 2);
	wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
	wrefresh(win);

	Cursor cursor;
	getyx(stdscr, cursor.y, cursor.x);
	cursor.player = 0;
	strcpy(cursor.marks, "xo");

	unsigned int tiles = nlines * ncolumns;
	char table[tiles];
	for (int i; i < tiles; tiles++) { table[i] = ' '; }

	int ch;
	while((ch = getch()) != KEY_F(1)) {
		switch (ch) {
			case KEY_UP:
				cursor.y - 1 < 0 ? : cursor.y--; 
				break;
			case KEY_DOWN:
				cursor.y + 1 > nlines ? : cursor.y++;
				break;
			case KEY_LEFT:
				cursor.x - 1 < 0 ? : cursor.x--;
				break;
			case KEY_RIGHT:
				cursor.x + 1 > ncolumns ? : cursor.x++;
				break;
			case KEY_BACKSPACE:
				attron(COLOR_PAIR(cursor.player + 1));
				mvaddch(cursor.y, cursor.x, cursor.marks[cursor.player]);
				cursor.player = !cursor.player;
				break;
		}
		move(cursor.y, cursor.x);
		refresh(); // refresh window
	}
	endwin(); // close curses
	printf("Finished.\n");
}
