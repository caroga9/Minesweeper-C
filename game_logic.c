#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "board.h"

//this is the heart of the program
void get_user_action(Minesweeper m)
{
    //string to store user input in
    char action[100];

    //clear the terminal to create illusion of a static field (might not work in other operating systems than ubuntu)
    system("clear");
    //system("cls"); //windows

    //noch rausnehmen vor Abgabe
    //print_grid(m, m.board);

    print_grid(m, m.mask, false, false, 0, 0);
    printf("\nWhat would you like to do?\n");
    do
    {
        printf("Your options are: r (reveal tile), a (arm tile), d (disarm tile), h (get help), q (quit game).\n");

        //get user input and store it
        scanf("%s", action);

        //give feedback for invalid input
        //check for right length
        if (strlen(action) != 1)
        {
            printf("This is not a valid input.\n");
            continue;
        }

        //evaluate input and call respective function

        if (*action == 'r')
        {
            reveal_tile(m);
            break;
        }
        if (*action == 'a')
        {
            arm_tile(m);
            break;
        }
        if (*action == 'd')
        {
            disarm_tile(m);
            break;
        }
        if (*action == 'h')
        {
            print_inGame_help();
            break;
        }
        if (*action == 'q')
        {
            game_over(m);
            break;
        }

        //loop will continue if input doesn't correspond to any of the options

    } while (true);
}

void reveal_tile(Minesweeper m)
{
    int tile_row, tile_column;

    printf("Which tile do you want to reveal?\n(row,column)\n");

    //call a function to evaluate input given for tile row and column
    check_input_tile(m, &tile_row, &tile_column);

    //user cannot lose by revealing the very first tile
    if (*m.ptr_first_round)
    {
        //if the chosen tile (in the first round) has a mine, the field will be reset
        //this will be repeated until the chosen tile is safe
        while (m.board[tile_row][tile_column] == MINE_TILE)
        {
            int i, j;
            //reset field to all zeroes (deletes mines)
            for (i = 1; i <= m.rows; i++)
            {
                for (j = 1; j <= m.columns; j++)
                {

                    m.board[i][j] = 0;
                }
            }

            //create a new field
            initialize_field(m);
        }

        //set start time
        time_t start_time = time(0);
        *m.ptr_start_time = start_time;

        //this is the end of the first round
        *m.ptr_first_round = false;
    }

    //call a function to evaluate what's going to happen when the chosen tile is revealed
    check_revealed_tile(m, tile_row, tile_column);
}

void check_revealed_tile(Minesweeper m, int tile_row, int tile_column)
{
    //get content of chosen tile
    int chosen_tile = m.board[tile_row][tile_column];

    //check whether the tile has been marked as armed
    if (m.mask[tile_row][tile_column] == ARMED_TILE)
    {
        char answer[100];

        printf("This tile is set as armed. Do you wish to disarm it?\n");

        //get user input and repeat question until the answer is valid
        do
        {
            scanf("%s", answer);

            //check for right length
            while (strlen(answer) != 1)
            {
                printf("Please answer y for yes or n for no.\n");
                scanf("%s", answer);
            }

            if (*answer == 'y')
            {
                //disarm tile and display it as a covered tile again
                m.mask[tile_row][tile_column] = COVERED_TILE;

                //there's one less armed tile now
                *m.ptr_number_tiles_armed -= 1;

                get_user_action(m);
                break;
            }

            if (*answer == 'n')
            {
                // don't do anything and get new user action if answer is 'no'
                get_user_action(m);
                break;
            }
            else
            {
                //give feedback for false input
                printf("Please answer y for yes or n for no.\n");
            }

        } while (true);
    }

    //if the tile has already been revealed, there is the option of digging (see ReadMe)
    if (m.mask[tile_row][tile_column] != COVERED_TILE)
    {
        dig_under_open_tile(m, tile_row, tile_column);
    }

    //the game is lost if there is a mine on this tile
    if (chosen_tile == MINE_TILE)
    {
        lost_game(m, tile_row, tile_column);
    }

    //if none of the above conditions are met, the tile is revealed
    else
    {
        //if there is a 0 tile underneath, adjacent tiles get revealed as well
        if (chosen_tile == EMPTY_TILE)
        {
            m.mask[tile_row][tile_column] = m.board[tile_row][tile_column];
            reveal_adjacent_tiles(m, tile_row, tile_column);
        }
        //reveal a number tile
        else
        {
            m.mask[tile_row][tile_column] = m.board[tile_row][tile_column];
        }
    }

    //need to keep track of the nuber of revealed tiles to determine the end fo the game
    count_revealed_tiles(m, tile_row, tile_column);

    get_user_action(m);
}

void dig_under_open_tile(Minesweeper m, int tile_row, int tile_column)
{
    int chosen_tile = m.mask[tile_row][tile_column];

    //if the open tile that has been chosen to dig under is a 0 tile, all adjacent tiles are already revealed
    if (m.mask[tile_row][tile_column] == EMPTY_TILE)
    {
        printf("You cannot dig under an empty tile.");
        get_user_action(m);
    }

    else
    {
        int count = 0;
        //loop through all adjacent tiles
        for (int a = (tile_row - 1); a <= (tile_row + 1); a++)
        {
            for (int b = (tile_column - 1); b <= (tile_column + 1); b++)
            {
                //relevant for boundary conditions
                int temp_a = a;
                int temp_b = b;

                if (m.boundary)
                {
                    //call function for periodic boundary conditions
                    //to be able to properly reveal adjacent tiles
                    create_boundary_condition(m, &a, &b);
                }

                //count all armed tiles that surround the chosen tile
                if (m.mask[a][b] == ARMED_TILE)
                {
                    count++;
                }
                //boundary conditions will overwrite a and b
                //and they need to be reset for the next iteration
                a = temp_a;
                b = temp_b;
            }
        }

        //call the function to reveal adjacent tiles
        //if there are enough surrounding tiles marked as armed
        if (chosen_tile <= count)
        {
            reveal_adjacent_tiles(m, tile_row, tile_column);
        }
        else
        {
            printf("There aren't enough surrounding armed tiles to dig\n");
            get_user_action(m);
        }
    }
}

void reveal_adjacent_tiles(Minesweeper m, int tile_row, int tile_column)
{
    //loop through all adjacent tiles
    for (int a = (tile_row - 1); a <= (tile_row + 1); a++)
    {
        for (int b = (tile_column - 1); b <= (tile_column + 1); b++)
        {
            //relevant for boundary conditions
            int temp_a = a;
            int temp_b = b;
            if (m.boundary)
            {
                create_boundary_condition(m, &a, &b);
            }

            //skip the tile if it is either already open or an armed tile
            if (m.mask[a][b] != COVERED_TILE)
            {
                //boundary conditions will overwrite a and b
                //and they need to be reset for the next iteration
                a = temp_a;
                b = temp_b;
                continue;
            }

            //irrelevant for empty tiles but important for digging
            //if there was a mistake in arming the tiles the player loses
            if (m.board[a][b] == MINE_TILE)
            {
                lost_game(m, a, b);
            }

            //reveal tile
            m.mask[a][b] = m.board[a][b];

            //cascade-effect. if an empty tile gets revealed, all its adjacent tiles will be revealed as well
            if (m.board[a][b] == EMPTY_TILE)
            {
                reveal_adjacent_tiles(m, a, b);
            }

            //reset a and b for next iteration
            a = temp_a;
            b = temp_b;
        }
    }
}

void arm_tile(Minesweeper m)
{
    int tile_row, tile_column;
    do
    {

        printf("Which tile do you want to set as armed?\n(row,column)\n");

        //check user input for row and column of tile to arm
        check_input_tile(m, &tile_row, &tile_column);

        //check whether the tile has already been opened
        if (m.mask[tile_row][tile_column] == m.board[tile_row][tile_column])
        {
            printf("You cannot arm an open tile.\n");
        }

    } while (m.mask[tile_row][tile_column] == m.board[tile_row][tile_column]);

    //arm tile
    m.mask[tile_row][tile_column] = ARMED_TILE;

    //there's one more armed tile now
    *m.ptr_number_tiles_armed += 1;

    get_user_action(m);
}

void disarm_tile(Minesweeper m)
{
    //check whether there are any armed tiles to disarm
    if (*m.ptr_number_tiles_armed == 0)
    {
        printf("There are no armed tiles to disarm.\n");

        //delay next move for feedback to be displayed
        sleep(2);
    }

    else
    {
        int tile_row, tile_column;
        do
        {
            printf("Which tile do you want to disarm?\n(row,column)\n");

            //check user input for row and column of tile to disarm
            check_input_tile(m, &tile_row, &tile_column);

            //check whether it is armed
            if (m.mask[tile_row][tile_column] != ARMED_TILE)
            {
                printf("This tile is not armed.\n");
            }
        } while (((m.rows < tile_row) || (0 >= tile_row) || (m.columns < tile_column) || (tile_column <= 0)) || (m.mask[tile_row][tile_column] != ARMED_TILE));

        //disarm tile
        m.mask[tile_row][tile_column] = COVERED_TILE;

        //there's one less amred tile now
        *m.ptr_number_tiles_armed -= 1;
    }
    get_user_action(m);
}

void count_revealed_tiles(Minesweeper m, int tile_row, int tile_column)
{
    int number_tiles_revealed = 0;
    int i, j;

    //loop through all tiles
    for (i = 1; i <= m.rows; i++)
    {

        for (j = 1; j <= m.columns; j++)
        {
            //if the content of the mask is the same as the board, the tile is revealed
            if (m.mask[i][j] == m.board[i][j])
            {
                number_tiles_revealed++;
            }
        }

        //the game is won if all tiles have been revealed except for only the mine tiles
        if (number_tiles_revealed == (m.rows * m.columns - m.mines))
        {
            won_game(m);
        }
    }
}

//a function to keep the program from crashing if wrong input is given for row and column of a tile
void check_input_tile(Minesweeper m, int *tile_row, int *tile_column)
{

    while (true)
    {
        char input[100];
        scanf("%s", input);

        char *ptr;
        char *ptr2;

        int count = 0;
        int position = 0;

        //check whether and where there is a comma to indicate seperation of row and column
        for (int i = 0; i < strlen(input); i++)
        {
            if (input[i] == ',')
            {
                count++;
                position = i;
            }
        }

        //give feedback if there is no comma given or if it is obviously in the wrong place
        if (count != 1 || position == 0 || position == (strlen(input) - 1))
        {
            printf("Please use one comma to sepereate the number of row and column.\n");
            continue;
        }

        //give feedback if there is oviously something wrong with the numbers
        if (strlen(input) > (get_int_len(m.rows) + get_int_len(m.columns) + 1) || strlen(input) < 3)
        {
            printf("This can't be right.\n");
            continue;
        }

        //create a pointer to the number before and after the comma
        ptr = &input[0];
        ptr2 = &input[position + 1];

        //convert number string to an integer and store in respective variable
        *tile_row = atoi(ptr);
        *tile_column = atoi(ptr2);

        //there is no index 0 on the board, also letters get converted to a 0
        if (*tile_row <= 0 || *tile_column <= 0)
        {
            printf("This is not valid.\n");
            continue;
        }

        //check whether the given indices actually point to a tile on the board
        if ((m.rows < *tile_row) || (0 >= *tile_row) || (m.columns < *tile_column) || (*tile_column <= 0))
        {
            printf("This is not on the board.\n");
            continue;
        }

        else
        {
            //break out of the loop if everything is fine
            break;
        }
    }
}

void won_game(Minesweeper m)
{

    system("clear");

    //tell the player they have won
    print_won();
    printf("\n");

    //print the board one last time with all mines marked
    print_grid(m, m.board, true, true, 0, 0);
    game_over(m);
}

void lost_game(Minesweeper m, int loser_row, int loser_column)
{
    system("clear");

    //tell the player they have lost
    print_lost();
    printf("\n");

    //print the board one last time with all mines marked
    //and an indicator of the tile that made the player lose
    print_grid(m, m.mask, true, false, loser_row, loser_column);
    game_over(m);
}

void game_over(Minesweeper m)
{
    //free the memory when the game is over
    int i;

    for (i = 0; i < m.rows + 2; i++)
    {
        free(m.mask[i]);
    }

    free(m.mask);

    for (i = 0; i < m.rows + 2; i++)
    {
        free(m.board[i]);
    }

    free(m.board);

    //exit the program
    exit(0);
}
