#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#define ANSI_COLOR_PURPLE "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define MINE_TILE 42
typedef struct TestMinesweeper
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
}Test;

int main(void)
{
	Test m_mines = {3,3,3};
	m_mines.board = malloc((m_mines.rows + 2) * sizeof *m_mines.board);
	int i;
    for (i = 0; i < (m_mines.rows + 2); i++)
    {
        m_mines.board[i] = malloc((m_mines.columns + 2) * sizeof *m_mines.board[i]);
    }

    //...and mask
    m_mines.mask = malloc((m_mines.rows + 2) * sizeof *m_mines.mask);
    for (i = 0; i < (m_mines.rows + 2); i++)
    {
        m_mines.mask[i] = malloc((m_mines.columns + 2) * sizeof *m_mines.mask[i]);
    }
	int test_matrix = m_mines.board;
}
