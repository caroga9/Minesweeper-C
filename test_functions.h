#include "board.h"
void memory_allocation(Minesweeper minesweeper);
void free_memory(Minesweeper minesweeper);
bool create_mines_test(Minesweeper m, int first_tile_row, int first_tile_column);

bool create_mask_test(Minesweeper m);
void RunTests(void);
bool number_fields_test(Minesweeper m, bool boundary);