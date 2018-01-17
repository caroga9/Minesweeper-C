#include"game_logic.h"

void create_mines(Minesweeper m);


void number_fields(Minesweeper m);


void create_mask(Minesweeper m);


void initialize_field(Minesweeper m);

void create_boundary_condition(Minesweeper m, int *a, int *b);

void print_grid(Minesweeper m, int** array);

void print_final_mask(Minesweeper m, int** array, bool won_game, int loser_row, int loser_column);

int get_int_len (int value);

int timer(Minesweeper m);

