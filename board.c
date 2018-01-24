#include "board.h"

//call all functions neccessary to create the board and mask
void initialize_field(Minesweeper m, int tile_row, int tile_column)
{

    create_mines(m, tile_row, tile_column);
    number_fields(m);

    printf("\n");
}

void create_mines(Minesweeper m, int first_tile_row, int first_tile_column)
{
    int position_row, position_column;

    //needed for random function. uses computer system time
    srand(time(NULL));

    //find a position for every mine
    for (int mine = 0; mine < m.mines; mine++)
    {

        //repeat search for position as long as its already occupied
        do
        {
            //get a random number between 1 and number of rows
            position_row = rand() % ((m.rows + 1) - 1) + 1;
            //same for columns
            position_column = rand() % ((m.columns + 1) - 1) + 1;

        } while (m.board[position_row][position_column] == MINE_TILE || (position_row == first_tile_row && position_column == first_tile_column));

        //place mine on respective position on the board
        m.board[position_row][position_column] = MINE_TILE;
    }
}

void create_mask(Minesweeper m)
{
    int i, j;

    //loop through all tiles
    for (i = 1; i <= m.rows; i++)
    {

        for (j = 1; j <= m.columns; j++)
        {
            //place a tile-cover on every position in the mask
            m.mask[i][j] = COVERED_TILE;
        }
    }
}

//a function to place numbers of adjacent mines on every tile on the board
void number_fields(Minesweeper m)
{
    int i, j;

    //loop through all tiles
    for (i = 1; i <= m.rows; i++)
    {
        for (j = 1; j <= m.columns; j++)
        {
            //only put numbers on empty fields
            if (m.board[i][j] != MINE_TILE)
            {

                int count = 0;

                //loop through all adjacent tiles
                for (int a = (i - 1); a <= (i + 1); a++)
                {
                    for (int b = (j - 1); b <= (j + 1); b++)
                    {
                        //this is only relevant if boundary conditions are active
                        int temp_a = a;
                        int temp_b = b;
                        if (m.boundary)
                        {
                            create_boundary_condition(m, &a, &b);
                        }

                        //if an adjacent tile has a mine, increment the counter
                        if (m.board[a][b] == MINE_TILE)
                        {
                            count++;
                        }

                        //boundary conditions will overwrite a and b
                        //and they need to be reset for the next iteration
                        a = temp_a;
                        b = temp_b;
                    }
                }

                //place the number of adjacent mines on the field
                m.board[i][j] = count;
            }
        }
    }

    // making sure border tiles that actually don't belong to the board don't get a 0
    // (will be relevant later)
    //loop through all columns in the first and last row
    for (i = 0; i <= (m.rows + 1); i += (m.rows + 1))
    {
        for (j = 0; j <= (m.columns + 1); j++)
        {
            m.board[i][j] = BORDER_TILE;
        }
    }

    //loop through all rows in the first and last column
    for (j = 0; j <= (m.columns + 1); j += (m.columns + 1))
    {
        for (i = 0; i <= (m.rows + 1); i++)
        {
            m.board[i][j] = BORDER_TILE;
        }
    }

    // turn all 0 tiles into actual empty tiles (for design purposes)
    //loop through all tiles on the board
    for (i = 1; i <= m.rows; i++)
    {

        for (j = 1; j <= m.columns; j++)
        {
            if (m.board[i][j] == 0)
            {
                m.board[i][j] = EMPTY_TILE;
            }
        }
    }
}

//having periodic boundary conditions means that the left border touches the right border etc.
//(see ReadMe)
void create_boundary_condition(Minesweeper m, int *a, int *b)
{
    //corner tiles
    if (*a == 0 && *b == 0)
    {
        *a = m.rows;
        *b = m.columns;
    }
    if (*a == m.rows + 1 && *b == m.columns + 1)
    {
        *a = 1;
        *b = 1;
    }
    if (*a == m.rows + 1 && *b == 0)
    {
        *a = 1;
        *b = m.columns;
    }
    if (*a == 0 && *b == m.columns + 1)
    {
        *a = m.rows;
        *b = 1;
    }

    //upper border
    if (*a == 0 && (0 < *b <= m.columns))
    {
        *a = m.rows;
    }
    //lower border
    if (*a == m.rows + 1 && (0 < *b <= m.columns))
    {
        *a = 1;
    }
    //left border
    if ((0 < *a <= m.rows) && *b == 0)
    {
        *b = m.columns;
    }
    //right border
    if ((0 < *a <= m.rows) && *b == m.columns + 1)
    {
        *b = 1;
    }
}

int timer(Minesweeper m)
{
    //call time() function to get current time
    time_t now = time(0);

    //calculate time passend since first call (stored as start time)
    int time_passed;
    time_passed = now - *m.ptr_start_time;

    return time_passed;
}

//a function to calculate the number of digits of a number
int get_int_len(int value)
{

    int len = 1;

    while (value > 9)
    {

        len++;

        value /= 10;
    }

    return len;
}

void print_grid(Minesweeper m, int **grid, bool game_end, bool won_game, int loser_row, int loser_column)
{
    if (!game_end)
    {
        printf("Number of mines: %d\nTiles marked as armed: %d\n\n", m.mines, *m.ptr_number_tiles_armed);
    }
    if (!*m.ptr_first_round)
    {
        printf("Time elapsed: %ds\n\n", timer(m));
    }
    int i, j;
    int padding;
    for (padding = 0; padding < get_int_len(m.rows); padding++)
    {
        printf(" ");
    }
    for (j = 1; j <= m.columns; j++)
    {
        for (padding = 0; padding + get_int_len(j) < get_int_len(m.columns); padding++)
        {
            printf(" ");
        }
        printf(" %d", j);
    }
    printf("\n");
    for (i = 1; i <= m.rows; i++)
    {
        for (padding = 0; padding + get_int_len(i) < get_int_len(m.rows); padding++)
        {

            printf(" ");
        }
        printf("%d", i);
        for (j = 1; j <= m.columns; j++)
        {
            if (game_end)
            {
                if (m.board[i][j] == MINE_TILE)
                {
                    grid[i][j] = MINE_TILE;
                }
            }
            printf("|");

            switch (grid[i][j])
            {
            case COVERED_TILE:
                printf(COLOR_COVERED_TILE);
                break;
            case MINE_TILE:
                printf(COLOR_MINE_TILE);
                break;
            case ARMED_TILE:
                printf(COLOR_ARMED_TILE);
                break;
            case 1:
                printf(COLOR_1);
                break;
            case 2:
                printf(COLOR_2);
                break;
            case 3:
                printf(COLOR_3);
                break;
            case 4:
                printf(COLOR_4);
                break;
            case 5:
                printf(COLOR_5);
                break;
            case 6:
                printf(COLOR_6);
                break;
            case 7:
                printf(COLOR_7);
                break;
            case 8:
                printf(COLOR_8);
                break;
            }

            if (grid[i][j] <= 8)
            {
                for (padding = 1; padding < get_int_len(m.columns); padding++)
                {
                    printf(" ");
                }
                printf("%d", grid[i][j]);
            }
            else
            {
                if (game_end)
                {
                    if (!won_game)
                    {
                        if (i == loser_row && j == loser_column)
                        {
                            printf(COLOR_LOSER_TILE);
                        }
                    }
                    if (won_game)
                    {
                        if (grid[i][j] == MINE_TILE)
                        {
                            printf(COLOR_WON_MINE);
                        }
                    }
                }
                for (padding = 1; padding < get_int_len(m.columns); padding++)
                {
                    printf(" ");
                }
                printf(" ");
            }

            printf(COLOR_RESET);
        }

        printf("|%d", i);
        printf("\n");
    }

    for (padding = 0; padding < get_int_len(m.rows); padding++)
    {
        printf(" ");
    }
    for (j = 1; j <= m.columns; j++)
    {

        for (padding = 0; padding + get_int_len(j) < get_int_len(m.columns); padding++)
        {
            printf(" ");
        }
        printf(" %d", j);
    }

    printf("\n");
}
