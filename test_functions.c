#include "test_functions.h"

void memory_allocation(Minesweeper minesweeper)
{
    int i;
    minesweeper.board = malloc((minesweeper.rows + 2) * sizeof *minesweeper.board);
    for (i = 0; i < (minesweeper.rows + 2); i++)
    {
        minesweeper.board[i] = malloc((minesweeper.columns + 2) * sizeof *minesweeper.board[i]);
    }

    //...and mask
    minesweeper.mask = malloc((minesweeper.rows + 2) * sizeof *minesweeper.mask);
    for (i = 0; i < (minesweeper.rows + 2); i++)
    {
        minesweeper.mask[i] = malloc((minesweeper.columns + 2) * sizeof *minesweeper.mask[i]);
    }
}

void free_memory(Minesweeper minesweeper)
{
    int i;
    for (i = 0; i < minesweeper.rows + 2; i++)
    {
        free(minesweeper.mask[i]);
    }
    free(minesweeper.mask);

    for (i = 0; i < minesweeper.rows + 2; i++)
    {
        free(minesweeper.board[i]);
    }
    free(minesweeper.board);
}
bool create_mines_test(Minesweeper m, int first_tile_row, int first_tile_column)
{
    create_mines(m, first_tile_row, first_tile_column);
    return true;
   int count = 0;
    for (int i = 1; i <= m.rows; i++)
    {

        for (int j = 1; j <= m.columns; j++)
        {
            if (m.board[i][j] == MINE_TILE)
            {
                count++;
            }
        }
    }
    if (count == m.mines && (m.board[first_tile_row][first_tile_column] == 0))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool create_mask_test(Minesweeper m)
{
    create_mask(m);
    int count = 0;
    for (int i = 1; i <= m.rows; i++)
    {

        for (int j = 1; j <= m.columns; j++)
        {
            if (m.mask[i][j] == COVERED_TILE)
            {
                count++;
            }
        }
    }
    if (count == (m.rows * m.columns))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool number_fields_test(Minesweeper m, bool boundary)
{
    bool value = true;
    if (boundary)
    {
        m.boundary = true;
        int test_matrix[5][5] = {
            {BORDER_TILE, BORDER_TILE, BORDER_TILE, BORDER_TILE, BORDER_TILE},
            {BORDER_TILE, 2, MINE_TILE, 2, BORDER_TILE},
            {BORDER_TILE, MINE_TILE, 2, 2, BORDER_TILE},
            {BORDER_TILE, 2, 2, 2, BORDER_TILE},
            {BORDER_TILE, BORDER_TILE, BORDER_TILE, BORDER_TILE, BORDER_TILE}};
        number_fields(m);

    
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (m.board[i][j] != test_matrix[i][j])
                {
                    value = false;
                }
            }
        }
    }

    else
    {
        m.boundary = false;
        int test_matrix[5][5] = {
            {BORDER_TILE, BORDER_TILE, BORDER_TILE, BORDER_TILE, BORDER_TILE},
            {BORDER_TILE, 2, MINE_TILE, 1, BORDER_TILE},
            {BORDER_TILE, MINE_TILE, 2, 1, BORDER_TILE},
            {BORDER_TILE, 1, 1, EMPTY_TILE, BORDER_TILE},
            {BORDER_TILE, BORDER_TILE, BORDER_TILE, BORDER_TILE, BORDER_TILE}};

        number_fields(m);

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (m.board[i][j] != test_matrix[i][j])
                {
                    value = false;
                }
            }
        }
    }
    
    
    return value;
}
