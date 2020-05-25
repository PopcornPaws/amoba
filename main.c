#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

#include "cursor.h"

typedef struct GameData {
	Cursor *cursor;
	char *table;
} GameData;

void save_to_file(GameData *gd) {
	char path[] = "data/"; 
	char filename[10];
	//printf("Please type the name of the file:\n");
	//scanf("%s", filename); 
	strcpy(filename, "test");
	strcat(filename, ".dat");
	strcat(path, filename);

	FILE *fp;
	fp = fopen(path, "w");
	if (fp == NULL) {
		printf("Couldn't open file!");
		return;
	}
	int table_len = gd -> cursor -> ncols * gd -> cursor -> nrows + 1;
	fwrite(gd -> cursor, sizeof(Cursor), 1, fp);
	fputs("\n", fp);
	fwrite(gd -> table, sizeof(char), table_len, fp);
	fclose(fp);
	printf("Saved data to: %s\n", path);
}

GameData read_from_file() {
	char path[] = "data/"; 
	char filename[10];
	//printf("Please type the name of the file:\n");
	//scanf("%s", filename); 
	strcpy(filename, "test");
	strcat(filename, ".dat");
	strcat(path, filename);

	FILE *fp;
	fp = fopen(path, "r");
	if (fp == NULL) {
		printf("File does not exist!\n");
		exit(1);
	}

	Cursor cursor;
	char *table;

	fread(&cursor, sizeof(Cursor), 1, fp);
	int table_len = cursor.ncols * cursor.nrows + 1;
	printf("len = %d\n", table_len);

	fseek(fp, 1, SEEK_CUR); // add an offset to file pointer to "jump over" the additional newline character
	table = (char *)malloc(table_len);
	fread(table, sizeof(char), table_len, fp);

	GameData gd;
	gd.cursor = &cursor;
	gd.table = table;
	return gd;
}

//GameData init_game_data(unsigned int nr; unsigned int nc, unsigned int mw) {
//}

void main(void) {
	//printf("How many lines do you need?\n");
	//scanf("%d", &nlines); 
	//printf("How many rows do you need?\n");
	//scanf("%d", &rows); 
	unsigned int nrows = 5;
	unsigned int ncolumns = 5;
	unsigned int marks_to_win = 4;

	initscr(); // initialize curses
	noecho(); // don't echo keystrokes (so it won't output what the user is typing)
	raw(); // disable all default key commands (e.g. Ctrl + c)
	start_color();

	init_pair(1, COLOR_BLUE, COLOR_WHITE);
	init_pair(2, COLOR_RED, COLOR_WHITE);

	keypad(stdscr, TRUE); // enable special keys (such as F1 to exit)

	WINDOW *win = newwin(nrows, ncolumns, 0, 0);
	//wborder(win, '*', '*', '*', '*', '*', '*', '*', '*');

	Cursor cursor;
	getyx(stdscr, cursor.y, cursor.x);
	cursor.ncols = ncolumns;
	cursor.nrows = nrows;
	cursor.player = 0;
	strcpy(cursor.marks, "xo");

	unsigned int ntiles = nrows * ncolumns;
	char table[ntiles + 1];
	for (int i = 0; i < ntiles; i++) table[i] = 'x';
	table[ntiles] = '\0';

	endwin();
	printf("%s\n", table);

	/*
	int ch;
	int flag = 0;
	unsigned int rounds = 0;
	unsigned int table_index;

	while((ch = getch()) != KEY_F(1)) {
		switch (ch) {
			case KEY_UP:
				cursor.y - 1 < 0 ? : cursor.y--; 
				break;
			case KEY_DOWN:
				cursor.y + 1 >= nrows ? : cursor.y++;
				break;
			case KEY_LEFT:
				cursor.x - 1 < 0 ? : cursor.x--;
				break;
			case KEY_RIGHT:
				cursor.x + 1 >= ncolumns ? : cursor.x++;
				break;
			case KEY_BACKSPACE:
				table_index = get_table_index(cursor.x, cursor.y, cursor.ncols);

				if (is_free(table, table_index)) {
					attron(COLOR_PAIR(cursor.player + 1));
					mvaddch(cursor.y, cursor.x, cursor.marks[cursor.player]);
					table[table_index] = cursor.marks[cursor.player];
					flag = is_winner(&cursor, table, marks_to_win);
					if (flag) break;
					cursor.player = !cursor.player;
					rounds++;
				}
				break;
		}
		move(cursor.y, cursor.x);
		refresh(); // refresh window
		if (flag) {
			break;
		} else if (rounds == ntiles) {
			break;
		}
	}
	endwin(); // close window and end ncurses session
	printf("Finished.\n");
	if (flag) {
		printf("Winner is %c!\n", cursor.marks[cursor.player]);
	} else {
		printf("Draw!\n", cursor.marks[cursor.player]);
	}
	*/
	GameData gd_w = {&cursor, table};
	save_to_file(&gd_w);

	GameData gd_r = read_from_file();
	printf("%s\n", gd_r.table);
	//cursor.x = 0;
	//cursor.y = 3;
	//printf("x = %d, y = %d, i = %d\n", cursor.x, cursor.y, get_table_index(cursor.x, cursor.y, cursor.ncols));
	//table[0] = 'x';
	//table[5] = 'o';
	//table[10] = 'o';
	//table[15] = 'o';
	//for (int i = 0; i < tiles; i++) {
	//	printf("t[%d] = %c\n", i, table[i]);
	//}
	//cursor.player = !cursor.player;
	//printf("winner = %d\n", is_winner(&cursor, &table, marks_to_win));
}
