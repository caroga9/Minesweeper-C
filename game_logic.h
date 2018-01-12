#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <stdbool.h>

#include <unistd.h>

#include"text.h"

typedef struct Minesweeper{
        unsigned short int rows;
        unsigned short int columns;
        unsigned short int mines;
        int **mask;
        int **board;

        //int number_tiles_revealed;
        //int *ptr_number_tiles_revealed;
        bool boundary;
        
        int number_tiles_armed;
        int *ptr_number_tiles_armed;

        long start_time;
        long *ptr_start_time;

    } Minesweeper;



#define COVERED_TILE 64
#define EMPTY_TILE 143
#define MINE_TILE 42
#define ARMED_TILE 65
#define BORDER_TILE 149
#define WINNER_TILE 128

void initialize_field(Minesweeper m);
void dig_under_open_tile(Minesweeper m, int tile_row, int tile_column);
void check_revealed_tile(Minesweeper m, int tile_row, int tile_column);
void reveal_adjacent_tiles(Minesweeper m, int tile_row, int tile_column);
void reveal_tile(Minesweeper m, bool **ptr_first_round);
void get_user_action(Minesweeper m, bool *first_round);
void lost_game(Minesweeper m, int loser_row, int loser_column);
void won_game(Minesweeper m);
void arm_tile(Minesweeper m);
void disarm_tile(Minesweeper m);
void print_inGame_help();
void game_over(Minesweeper m);
//void flood_fill(Minesweeper m, int tile_row, int tile_column);
void count_revealed_tiles(Minesweeper m, int tile_row, int tile_column);