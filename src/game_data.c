#include "cursor.h"

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

GameData init_game_data() {
	unsigned int nrows;
	unsigned int ncolumns;
	unsigned int marks_to_win;
	
	printf("How many columns do you need?\n");
	scanf("%d", &ncolumns); 
	printf("How many rows do you need?\n");
	scanf("%d", &rows); 
	printf("How many consecutive marks should win?\n");
	scanf("%d", &marks_to_win); 
	// TODO check if marks_to_win is at least 3 or 4, but not exceeding nrows or ncolumns

	Cursor cursor;
	cursor.x = ncolumns / 2;
	cursor.y = nrows / 2;
	cursor.ncols = ncolumns;
	cursor.nrows = nrows;
	cursor.player = 0;
	strcpy(cursor.marks, "xo");

	unsigned int ntiles = nrows * ncolumns;
	char table[ntiles + 1];
	for (int i = 0; i < ntiles; i++) table[i] = ' ';
	table[ntiles] = '\0';

	GameData gd;
	gd.cursor = &cursor;
	gd.table = table;

	return gd;
}
