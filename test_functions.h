#include "board.h"

bool create_mines_test(Minesweeper m, int first_tile_row, int first_tile_column);
bool create_mask_test(Minesweeper m);
void initialize_filled(Minesweeper m);
bool number_fields_test(Minesweeper m, bool boundary);
bool reveal_adjacent_tiles_test(Minesweeper m, int tile_row, int tile_column, bool boundary);
bool dig_under_open_tile_test(Minesweeper m, int tile_row, int tile_column, bool boundary);