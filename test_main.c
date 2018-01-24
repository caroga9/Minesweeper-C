#include "test_functions.h"

int main(void)
{
    Minesweeper m_mines = {3, 3, 3,.test = true};
    Minesweeper m_mask = {3, 3, .test = true};
    Minesweeper m_number = {3, 3, .test = true};
    Minesweeper m_filled = {3,3, .test = true};

    int i;
    m_mines.board = malloc((m_mines.rows + 2) * sizeof *m_mines.board);
    for (i = 0; i < (m_mines.rows + 2); i++)
    {
        m_mines.board[i] = malloc((m_mines.columns + 2) * sizeof *m_mines.board[i]);
    }

    m_mask.mask = malloc((m_mask.rows + 2) * sizeof *m_mask.mask);
    for (i = 0; i < (m_mask.rows + 2); i++)
    {
        m_mask.mask[i] = malloc((m_mask.columns + 2) * sizeof *m_mask.mask[i]);
    }

    m_number.board = malloc((m_number.rows + 2) * sizeof *m_number.board);
    for (i = 0; i < (m_number.rows + 2); i++)
    {
        m_number.board[i] = malloc((m_number.columns + 2) * sizeof *m_number.board[i]);
    }
    
    m_filled.board = malloc((m_filled.rows + 2) * sizeof *m_filled.board);
    for (i = 0; i < (m_filled.rows + 2); i++)
    {
        m_filled.board[i] = malloc((m_filled.columns + 2) * sizeof *m_filled.board[i]);
    }

    m_filled.mask = malloc((m_filled.rows + 2) * sizeof *m_filled.mask);
    for (i = 0; i < (m_filled.rows + 2); i++)
    {
        m_filled.mask[i] = malloc((m_filled.columns + 2) * sizeof *m_filled.mask[i]);
    }
    
    m_number.board[1][2] = MINE_TILE;
    m_number.board[2][1] = MINE_TILE;

    unsigned short int testsPassed = 0, testsFailed = 0;
    if (create_mines_test(m_mines, 1, 1))
    {
        testsPassed++;
        printf("create_mines:                                           \x1b[32m OK\x1b[0m \n");
    }
    else
    {
        testsFailed++;
        printf("create_mines:                                           \x1b[31m FAILED\x1b[0m \n");
    }

    if (create_mask_test(m_mask))
    {
        testsPassed++;
        printf("create_mask:                                            \x1b[32m OK\x1b[0m \n");
    }
    else
    {
        testsFailed++;
        printf("create_mask:                                            \x1b[31m FAILED\x1b[0m \n");
    }
    if (number_fields_test(m_number, false))
    {
        testsPassed++;
        printf("number_fields (no boundary-condition):                  \x1b[32m OK\x1b[0m \n");
    }
    else
    {
        testsFailed++;   
        printf("number_fields (no boundary-condition):                  \x1b[31m FAILED\x1b[0m \n");
    }
    if (number_fields_test(m_number, true))
    {
        testsPassed++;
        printf("number_fields (boundary-condition):                     \x1b[32m OK\x1b[0m \n");
    }
    else
    {
        testsFailed++;
        printf("number_fields (boundary-condition):                     \x1b[31m FAILED\x1b[0m \n");
    }
/*
    if (reveal_adjacent_tiles_test(m_filled, 3,3, true))
    {
        testsPassed++;
        printf("reveal_adjacent_tiles (boundary-condition):   OK\n");
    }

    else
    {
        testsFailed++;
        printf("reveal_adjacent_tiles (boundary-condition):           FAILED\n");
    }
*/ //macht eh nicht viel Sinn
    if (reveal_adjacent_tiles_test(m_filled, 3,3, false))
    {
        testsPassed++;
        printf("reveal_adjacent_tiles (no boundary-condition):          \x1b[32m OK\x1b[0m \n");
    }
    else
    {
        testsFailed++;
        printf("reveal_adjacent_tiles (no boundary-condition):          \x1b[31m FAILED\x1b[0m \n");
    }
    if(dig_under_open_tile_test(m_filled,2,1,true))
    {
        testsPassed++;
        printf("dig_under_open_tile (boundary-condition):               \x1b[32m OK\x1b[0m \n");
    }
    else
    {
        testsFailed++;
        printf("dig_under_open_tile (boundary-condition:                \x1b[31m FAILED\x1b[0m \n");
    }

    if(dig_under_open_tile_test(m_filled,2,1,false))
    {
        testsPassed++;
        printf("dig_under_open_tile (no boundary-condition):            \x1b[32m OK\x1b[0m \n");
    }
    else
    {
        testsFailed++;
        printf("dig_under_open_tile (no boundary-condition:             \x1b[31m FAILED\x1b[0m \n");
    }
    printf("----------------------------------------------------------------------------------------\n");
    printf("Tests run: %d, \x1b[31m failed\x1b[0m %d,\x1b[32m passed\x1b[0m: %d\n", testsFailed+testsPassed, testsFailed, testsPassed);

}