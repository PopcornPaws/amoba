#include <stdio.h>
#include <curses.h>

void main(void) {
	int nlines = 5;
	int ncolumns = 5;

	initscr();

	keypad(stdscr, TRUE);

	WINDOW *win = newwin(nlines, ncolumns, 0, 0);
	wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
	wrefresh(win);

	int ch;
	int cursor_x = 0;
	int cursor_y = 0;
	int play = 1;

	char marks[2] = {'x', 'o'};
	int player = 0;
	while((ch = getch()) != KEY_F(1)) {
		switch (ch) {
			case KEY_UP:
				if (cursor_y - 1 < 0) {
				} else {
					move(--cursor_y, cursor_x);
				}
				break;
			case KEY_DOWN:
				if (cursor_y + 1 > nlines) {
				} else {
					move(++cursor_y, cursor_x);
				}
				break;
			case KEY_LEFT:
				if (cursor_x - 1 < 0) {
				} else {
					move(cursor_y, --cursor_x);
				}
				break;
			case KEY_RIGHT:
				if (cursor_x + 1 > ncolumns) {
				} else {
					move(cursor_y, ++cursor_x);
				}
			case KEY_BACKSPACE
				addch(marks[player]);
				printw("%d", player);
				player = !player;
				printw("%d", player);
				break;
		}
		refresh();
	}

	endwin();

	printf("Finished\n");
	//printf("How many lines do you need?\n");
	//scanf("%d", &nlines); 
	//printf("How many rows do you need?\n");
	//scanf("%d", &rows); 

}
