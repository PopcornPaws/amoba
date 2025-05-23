#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cursor.h"
#include "gamedata.h"

void save_to_file(GameData *gd) {
	char path[] = "data/"; 
	char filename[30];
	printf("Please type the name of the file:\n");
	scanf("%s", filename); 
	strcat(filename, ".dat");
	strcat(path, filename);

	FILE *fp;
	fp = fopen(path, "w");
	if (fp == NULL) {
		fclose(fp);
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

GameData load_from_file() {
	char path[] = "data/"; 
	char filename[30];
	printf("Please type the name of the file:\n");
	scanf("%s", filename); 
	strcat(filename, ".dat");
	strcat(path, filename);

	FILE *fp;
	fp = fopen(path, "r");
	if (fp == NULL) {
		fclose(fp);
		printf("File does not exist!\n");
		exit(1);
	}

	Cursor cursor;
	char *table;

	fread(&cursor, sizeof(Cursor), 1, fp);
	int table_len = cursor.ncols * cursor.nrows + 1;

	fseek(fp, 1, SEEK_CUR); // add an offset to file pointer's current location to "jump over" the additional newline character
	table = (char *)malloc(table_len);
	fread(table, sizeof(char), table_len, fp);

	fclose(fp);
	printf("Game loaded successfully!\n");

	GameData gd;
	gd.cursor = &cursor;
	gd.table = table;
	return gd;
}

GameData init_game_data() {
	int nrows;
	int ncolumns;
	int marks_to_win;
	
	printf("Starting new game!\n");
	printf("How many columns do you need?\n");
	scanf("%d", &ncolumns); 
	printf("How many rows do you need?\n");
	scanf("%d", &nrows); 
	printf("How many consecutive marks should win?\n");
	scanf("%d", &marks_to_win); 
	
	// check if input makes sense
	if(nrows < 3) nrows = 3;
	if (ncolumns < 3) ncolumns = 3;
	if (marks_to_win < 3) marks_to_win = 3;

	Cursor cursor;
	cursor.x = ncolumns / 2 + 1;
	cursor.y = nrows / 2 + 1;
	cursor.ncols = ncolumns;
	cursor.nrows = nrows;
	cursor.marks_to_win = marks_to_win;
	cursor.rounds_played = 0;
	cursor.player = 0;
	strcpy(cursor.marks, "xo");

	int ntiles = nrows * ncolumns;
	char table[ntiles + 1];
	for (int i = 0; i < ntiles; i++) table[i] = ' ';
	table[ntiles] = '\0';

	GameData gd;
	gd.cursor = &cursor;
	gd.table = table;
	return gd;
}
