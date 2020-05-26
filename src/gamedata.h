typedef struct GameData {
	Cursor *cursor;
	char *table;
} GameData;

void save_to_file(GameData *gd);

GameData load_from_file();

GameData init_game_data();
