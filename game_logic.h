#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "text.h"


FILE *file ;


typedef struct Minesweeper
{
    unsigned short int rows;
    unsigned short int columns;
    unsigned short int mines;
    int **mask;
    int **board;

    bool boundary;

    bool first_round;
    bool *ptr_first_round;

    int number_tiles_armed;
    int *ptr_number_tiles_armed;

    long start_time;
    long *ptr_start_time;

} Minesweeper;

#define COVERED_TILE 64
#define EMPTY_TILE 32
#define MINE_TILE 42
#define ARMED_TILE 65
#define BORDER_TILE 149
#define WINNER_TILE 128

#define COLOR_COVERED_TILE "\x1b[47m"
#define COLOR_ARMED_TILE "\x1b[43m"
#define COLOR_LOSER_TILE "\x1b[101m"
#define COLOR_WON_MINE "\x1b[42m"
#define COLOR_MINE_TILE "\x1b[41m"
#define COLOR_8 "\x1b[91m"
#define COLOR_7 "\x1b[35m"
#define COLOR_6 "\x1b[31m"
#define COLOR_5 "\x1b[32m"
#define COLOR_4 "\x1b[33m"
#define COLOR_3 "\x1b[94m"
#define COLOR_2 "\x1b[92m"
#define COLOR_1 "\x1b[96m"
#define COLOR_RESET "\x1b[0m"


void dig_under_open_tile(Minesweeper m, int tile_row, int tile_column);
void check_revealed_tile(Minesweeper m, int tile_row, int tile_column);
void reveal_adjacent_tiles(Minesweeper m, int tile_row, int tile_column);
void reveal_tile(Minesweeper m);
void get_user_action(Minesweeper m);
void lost_game(Minesweeper m, int loser_row, int loser_column);
void won_game(Minesweeper m);
void arm_tile(Minesweeper m);
void disarm_tile(Minesweeper m);
void game_over(Minesweeper m);
void count_revealed_tiles(Minesweeper m, int tile_row, int tile_column);
void check_input_tile(Minesweeper m, int *tile_row, int *tile_column);
