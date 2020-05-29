#include "cursor.h"

int get_table_index(int x, int y, int ncolumns) {
	return x + y * ncolumns;
}

int is_free(char *table, int index) {
	return table[index] == ' ';
}

int is_winner(Cursor *c, char *table) {
	int counter = 0; // counter of same consecutive marks
	int N = 0, S = 0, E = 0, W = 0; // norht, south, east, west absolute shift from center point
	int NW, NE, SW, SE; //northwest, northeast, southwest, southeast
	int i = 0;

	// find N, S, E, W tiles from w - 1 direction of the current position 
	// if we would violate the playing area constraints, then we stop the in- or decrementation
	while (i < (c -> marks_to_win) - 1) {
		i++;
		(c -> y - N) > 0 ? N++ : N;
		(c -> x - W) > 0 ? W++ : W;
		(c -> y + S) < (c -> nrows) ? S++ : S;
		(c -> x + E) < (c -> ncols) ? E++ : E;
	}
	// save the smaller value in diagonal direction
	NW = (N <= W ? N : W);
	NE = (N <= E ? N : E);
	SW = (S <= W ? S : W);
	SE = (S <= E ? S : E);
	// run checks in four directions (SW -> NE, W -> E, NW -> SW, N -> S)
	int table_index;
	int x, y;
	// SW -> NE
	counter = 0; // reset marker counter
	i = 0; // reset loop counter
	while (i <= SW + NE) {
		x = c -> x - SW + i; // south west is in negative x direction from current point
		y = c -> y + SW - i; // south west is in positive y direction from current point
		table_index = get_table_index(x, y, c -> ncols);
		counter += (table[table_index] == c -> marks[c -> player] ? : -counter);
		if (counter == c -> marks_to_win) return 1;
		i++;
	}
	// W -> E
	counter = 0; // reset marker counter
	i = 0; // reset loop counter
	while (i <= W + E) {
		x = c -> x - W + i; // west is in negative x direction from current point
		y = c -> y; // y doesn't change during horizontal movement
		table_index = get_table_index(x, y, c -> ncols);
		counter += (table[table_index] == c -> marks[c -> player] ? : -counter);
		if (counter == c -> marks_to_win) return 1;
		i++;
	}
	// NW -> SE
	counter = 0; // reset marker counter
	i = 0; // reset loop counter
	while (i <= NW + SE) {
		x = c -> x - NW + i; // south west is in negative x direction from current point
		y = c -> y - NW + i; // south west is in negative y direction from current point
		table_index = get_table_index(x, y, c -> ncols);
		counter += (table[table_index] == c -> marks[c -> player] ? : -counter);
		if (counter == c -> marks_to_win) return 1;
		i++;
	}
	// N -> S 
	counter = 0; // reset marker counter
	i = 0; // reset loop counter
	while (i <= N + S) {
		x = c -> x; // x doesn't change during vertical movement
		y = c -> y - N + i; // north is in negative y direction from current point
		table_index = get_table_index(x, y, c -> ncols);
		counter += (table[table_index] == c -> marks[c -> player] ? : -counter);
		if (counter == c -> marks_to_win) return 1;
		i++;
	}
	// if there are not enough markers in any direction we haven't won yet
	return 0;
}
