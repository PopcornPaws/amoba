#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

#include "cursor.h"
#include "gamedata.h"

void main(void) {
	// Saving and loading files is possible through a designated GameData struct that
	// holds two pointers: one to a Cursor struct that describes the cursor's location, 
	// which player's turn it is, etc..., and one to the table which is a 1D array representation of
	// the game area. It may hold a ' ' (space) character to indicate the tile is free. Characters
	// 'x' and 'o' indicate that the tile is occupied by one of the players already.
	GameData gd;
	
	// user may choose to start a new game, load an existing game or exit
	int gamemode;

	printf("Welcome to Noughts and Crosses game!\n");
	printf("Please choose a number to play:\n");
	printf("0 -> Start new game\n");
	printf("1 -> Load game\n");
	printf("_ -> Exit\n");
	scanf("%d", &gamemode);
	switch (gamemode) {
		case 0:
			gd = init_game_data();
			break;
		case 1:
			gd = load_from_file();
			break;
		default:
			printf("Exiting game!\n");
			exit(0);
	}

	// Create local instances of cursor and table to avoid having to use double pointers
	// through GameData. This makes the code a bit easier to read, although it uses more
	// memory because we are copying data from the memory where the cursor and table 
	// objects were read from file.
	Cursor cursor;
	cursor.x = gd.cursor -> x;
	cursor.y = gd.cursor -> y;
	cursor.ncols = gd.cursor -> ncols;
	cursor.nrows = gd.cursor -> nrows;
	cursor.marks_to_win = gd.cursor -> marks_to_win;
	cursor.rounds_played = gd.cursor -> rounds_played;
	cursor.player = gd.cursor -> player;
	strcpy(cursor.marks, gd.cursor -> marks);

	char table[cursor.ncols * cursor.nrows + 1];
	memcpy(table, gd.table, cursor.ncols * cursor.nrows + 2);

	initscr(); // initialize curses
	noecho(); // don't echo keystrokes (so it won't output what the user is typing)
	raw(); // disable all default key commands (e.g. Ctrl + c)
	start_color(); // enable coloring in terminal

	init_pair(1, COLOR_BLUE, COLOR_WHITE); // player 1 has blue colored marks on a white background
	init_pair(2, COLOR_RED, COLOR_WHITE); // player 2 has red colored marks on a white background

	keypad(stdscr, TRUE); // enable special keys (such as F1 to exit)

	WINDOW *win = newwin(cursor.nrows, cursor.ncols, 0, 0);

	// initialize variables
	int ch;
	int flag = 0;
	int table_index;
	// fill up game area with marks already in the table
	for (int row = 0; row < cursor.nrows; row++) {
		for (int col = 0; col < cursor.ncols; col++) {
			move(row, col);
			table_index = get_table_index(col, row, cursor.ncols);
			switch (table[table_index]) {
				case 'x':
					attron(COLOR_PAIR(1)); // switch color pair to match the player's
					mvaddch(row, col, 'x'); // add character mark to curses game area
					attroff(COLOR_PAIR(1)); // switch color pair to match the player's
					break;
				case 'o':
					attron(COLOR_PAIR(2)); // switch color pair to match the player's
					mvaddch(row, col, 'o'); // add character mark to curses game area
					attroff(COLOR_PAIR(2)); // switch color pair to match the player's
					break;
				default:
					break;
			}
		}
	}
	// print "user manual"
	mvprintw(1, cursor.ncols + 3, "%c's turn!", cursor.marks[cursor.player]);
	mvaddstr(3, cursor.ncols + 3, "ARROWS    - move");
	mvaddstr(4, cursor.ncols + 3, "ENTER     - place mark");
	mvaddstr(5, cursor.ncols + 3, "BACKSPACE - save and quit");
	mvaddstr(6, cursor.ncols + 3, "F1        - quit");

	move(cursor.y, cursor.x); // move cursor to specific location
	while((ch = getch()) != KEY_F(1)) {
		switch (ch) {
			case KEY_UP:
				cursor.y - 1 < 0 ? : cursor.y--; 
				break;
			case KEY_DOWN:
				cursor.y + 1 >= cursor.nrows ? : cursor.y++;
				break;
			case KEY_LEFT:
				cursor.x - 1 < 0 ? : cursor.x--;
				break;
			case KEY_RIGHT:
				cursor.x + 1 >= cursor.ncols ? : cursor.x++;
				break;
			case KEY_BACKSPACE:
				// save to file and quit
				flag = -1;
				break;
			case 10: // ENTER = 10;
				table_index = get_table_index(cursor.x, cursor.y, cursor.ncols);

				if (is_free(table, table_index)) {
					attron(COLOR_PAIR(cursor.player + 1)); // switch color pair to match the player's
					mvaddch(cursor.y, cursor.x, cursor.marks[cursor.player]); // add character mark to curses game area
					attroff(COLOR_PAIR(cursor.player + 1)); // switch color pair to match the player's
					table[table_index] = cursor.marks[cursor.player]; // fill table with the placed mark
					flag = is_winner(&cursor, table);
					if (flag) break; // if we won, exit
					cursor.player = !cursor.player; // switch players
					cursor.rounds_played++; // a mark was set, so a round was played
				}
				break;
		}
		// print who's turn it is
		mvprintw(1, cursor.ncols + 3, "%c's turn!", cursor.marks[cursor.player]);
		move(cursor.y, cursor.x); // move cursor back to the playing area
		refresh(); // refresh window
		if (flag) {
			// we have a winner
			break;
		} else if (cursor.rounds_played == cursor.nrows * cursor.ncols) {
			// all tiles has been filled
			break;
		}
	}
	endwin(); // close window and end ncurses session
	printf("Finished.\n");
	GameData savegame = {&cursor, table};
	switch (flag) {
		case 0:
			printf("Draw!\n");
			break;
		case 1:
			printf("Winner is %c!\n", cursor.marks[cursor.player]);
			break;
		case -1:
			save_to_file(&savegame);
			break;
		default:
			printf("Bye!\n");
			break;
	}
}
