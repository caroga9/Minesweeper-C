#include "game_logic.h"

void create_mines(Minesweeper m, int first_tile_row, int first_tile_column);

void number_fields(Minesweeper m);

void create_mask(Minesweeper m);

void initialize_field(Minesweeper m, int tile_row, int tile_column);

void create_boundary_condition(Minesweeper m, int *a, int *b);

void print_grid(Minesweeper m, int **grid, bool game_end, bool won_game, int loser_row, int loser_column);

void print_final_mask(Minesweeper m, int **array, bool won_game, int loser_row, int loser_column);

int get_int_len(int value);

int timer(Minesweeper m);
