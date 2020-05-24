#include <stdio.h>
#include <string.h>
#include <curses.h>

#include "cursor.h"


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

	WINDOW *win = newwin(nlines, ncolumns, 0, 0);

	Cursor cursor;
	getyx(stdscr, cursor.y, cursor.x);
	cursor.player = 0;
	cursor.marks[0] = 'x';
	cursor.marks[1] = 'o';

	unsigned int tiles = nlines * ncolumns;
	char table[tiles];
	for (int i = 0; i < tiles; i++) { table[i] = ' '; }

	int ch;
	unsigned int table_index;

	while((ch = getch()) != KEY_F(1)) {
		switch (ch) {
			case KEY_UP:
				cursor.y - 1 < 0 ? : cursor.y--; 
				break;
			case KEY_DOWN:
				cursor.y + 1 >= nlines ? : cursor.y++;
				break;
			case KEY_LEFT:
				cursor.x - 1 < 0 ? : cursor.x--;
				break;
			case KEY_RIGHT:
				cursor.x + 1 >= ncolumns ? : cursor.x++;
				break;
			case KEY_BACKSPACE:
				table_index = get_table_index(&cursor, ncolumns);

				if (is_free(table, table_index)) {
					attron(COLOR_PAIR(cursor.player + 1));
					mvaddch(cursor.y, cursor.x, cursor.marks[cursor.player]);
					table[table_index] = cursor.marks[cursor.player];
					cursor.player = !cursor.player;
				}

				break;
		}
		move(cursor.y, cursor.x);
		wborder(win, '*', '*', '*', '*', '*', '*', '*', '*');
		refresh(); // refresh window
	}
	endwin(); // close window and end ncurses session
	printf("Finished.\n");

	//printf("x = %d, y = %d\n", cursor.x, cursor.y);
	//printf("%d\n", get_table_index(&cursor, ncolumns));
	//for (int i = 0; i < tiles; i++) {
	//	printf("t[%d] = %c\n", i, table[i]);
	//}
}
