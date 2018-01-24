#include "test_functions.h"

int main(void)
{
    Minesweeper m_mines = {3, 3, 3};
    Minesweeper m_mask = {3, 3};
    Minesweeper m_number = {3, 3};

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
    

    m_number.board[1][2] = MINE_TILE;
    m_number.board[2][1] = MINE_TILE;

    unsigned short int testsPassed = 0, testsFailed = 0;
    if (create_mines_test(m_mines, 1, 1))
    {
        testsPassed++;
        printf("create_mines:          OK\n");
    }
    else
    {
        testsFailed++;
        printf("create_mines:          FAILED\n");
    }

    if (create_mask_test(m_mask))
    {
        testsPassed++;
        printf("create_mask:           OK\n");
    }
    else
    {
        testsFailed++;
        printf("create_mask:           FAILED\n");
    }
    if (number_fields_test(m_number, false))
    {
        testsPassed++;
        printf("number_fields (no boundary-condition):   OK\n");
    }
    else
    {
        testsFailed++;
        printf("number_fields (no boundary-condition):           FAILED\n");
    }
    if (number_fields_test(m_number, true))
    {
        testsPassed++;
        printf("number_fields (boundary-condition):   OK\n");
    }
    else
    {
        testsFailed++;
        printf("number_fields (boundary-condition):           FAILED\n");
    }

}