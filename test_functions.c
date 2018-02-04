#include "test_functions.h"

void initialize_filled(Minesweeper m)
{

    m.board[1][1] = 1;
    m.board[1][2] = MINE_TILE;
    m.board[1][3] = 1;

    for (int j = 0; j <= m.columns + 1; j++)
    {
        m.board[0][j] = BORDER_TILE;
        m.board[2][j] = 1;
        if (m.boundary)
        {
            m.board[3][j] = 1;
        }
        else
        {
            m.board[3][j] = EMPTY_TILE;
        }
        m.board[m.rows + 1][j] = BORDER_TILE;
    }
    for (int i = 0; i <= m.rows + 1; i++)
    {
        m.board[i][0] = BORDER_TILE;
        m.board[i][m.columns + 1] = BORDER_TILE;
    }

    for (int i = 1; i <= m.rows; i++)
    {
        for (int j = 1; j <= m.columns; j++)
        {
            //place a tile-cover on every position in the mask
            m.mask[i][j] = COVERED_TILE;
        }
    }
}

bool create_mines_test(Minesweeper m, int first_tile_row, int first_tile_column)
{
    create_mines(m, first_tile_row, first_tile_column);

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

        for (int i = 0; i < m.rows + 1; i++)
        {
            for (int j = 0; j < m.columns + 1; j++)
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

        for (int i = 0; i <= m.rows + 1; i++)
        {
            for (int j = 0; j <= m.columns + 1; j++)
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

bool reveal_adjacent_tiles_test(Minesweeper m, int tile_row, int tile_column, bool boundary)
{

    bool value = true;
    if (!boundary)
    {

        m.boundary = false;
        initialize_filled(m);
        reveal_adjacent_tiles(m, tile_row, tile_column);
        int test_matrix_1[5][5] = {
            {COVERED_TILE, COVERED_TILE, COVERED_TILE, COVERED_TILE, COVERED_TILE},
            {COVERED_TILE, COVERED_TILE, COVERED_TILE, COVERED_TILE, COVERED_TILE},
            {COVERED_TILE, 1, 1, 1, COVERED_TILE},
            {COVERED_TILE, EMPTY_TILE, EMPTY_TILE, EMPTY_TILE, COVERED_TILE},
            {COVERED_TILE, COVERED_TILE, COVERED_TILE, COVERED_TILE, COVERED_TILE}};

        for (int i = 1; i <= m.rows; i++)
        {
            for (int j = 1; j <= m.columns; j++)
            {
                if (m.mask[i][j] != test_matrix_1[i][j])
                {
                    value = false;
                }
            }
        }
    }
    else
    {

        m.boundary = true;
        initialize_filled(m);
        reveal_adjacent_tiles(m, tile_row, tile_column);

        int test_matrix[5][5] = {
            {COVERED_TILE, COVERED_TILE, COVERED_TILE, COVERED_TILE, COVERED_TILE},
            {COVERED_TILE, COVERED_TILE, COVERED_TILE, COVERED_TILE, COVERED_TILE},
            {COVERED_TILE, COVERED_TILE, COVERED_TILE, COVERED_TILE, COVERED_TILE},
            {COVERED_TILE, COVERED_TILE, COVERED_TILE, 1, COVERED_TILE},
            {COVERED_TILE, COVERED_TILE, COVERED_TILE, COVERED_TILE, COVERED_TILE}};
        for (int i = 1; i <= m.rows; i++)
        {
            for (int j = 1; j <= m.columns; j++)
            {
                if (m.mask[i][j] != test_matrix[i][j])
                {
                    value = false;
                }
            }
        }
    }
    return value;
}

bool dig_under_open_tile_test(Minesweeper m, int tile_row, int tile_column, bool boundary)
{
    bool value = true;
    if (!boundary)
    {

        m.boundary = false;
        initialize_filled(m);
        m.mask[2][1] = m.board[2][1];
        m.mask[1][2] = ARMED_TILE;

        dig_under_open_tile(m, tile_row, tile_column);
        int test_matrix_1[5][5] = {
            {COVERED_TILE, COVERED_TILE, COVERED_TILE, COVERED_TILE, COVERED_TILE},
            {COVERED_TILE, 1, ARMED_TILE, COVERED_TILE, COVERED_TILE},
            {COVERED_TILE, 1, 1, 1, COVERED_TILE},
            {COVERED_TILE, EMPTY_TILE, EMPTY_TILE, EMPTY_TILE, COVERED_TILE},
            {COVERED_TILE, COVERED_TILE, COVERED_TILE, COVERED_TILE, COVERED_TILE}};

        for (int i = 1; i <= m.rows; i++)
        {
            for (int j = 1; j <= m.columns; j++)
            {
                if (m.mask[i][j] != test_matrix_1[i][j])
                {
                    value = false;
                }
            }
        }
    }
    else
    {

        m.boundary = true;
        initialize_filled(m);
        m.mask[2][1] = m.board[2][1];
        m.mask[1][2] = ARMED_TILE;
        dig_under_open_tile(m, tile_row, tile_column);
        int test_matrix[5][5] = {
            {COVERED_TILE, COVERED_TILE, COVERED_TILE, COVERED_TILE, COVERED_TILE},
            {COVERED_TILE, 1, ARMED_TILE, 1, COVERED_TILE},
            {COVERED_TILE, 1, 1, 1, COVERED_TILE},
            {COVERED_TILE, 1, 1, 1, COVERED_TILE},
            {COVERED_TILE, COVERED_TILE, COVERED_TILE, COVERED_TILE, COVERED_TILE}};
        for (int i = 1; i <= m.rows; i++)
        {
            for (int j = 1; j <= m.columns; j++)
            {
                if (m.mask[i][j] != test_matrix[i][j])
                {
                    value = false;
                }
            }
        }
    }
    return value;
}