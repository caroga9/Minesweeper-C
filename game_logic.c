#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "board.h"

void get_user_action(Minesweeper m)
{
    char action[100];
    //system("clear"); // in anderem Betriebssystem anpassen --> readme
    print_grid(m, m.board);
    print_grid(m, m.mask);
    printf("\nWhat would you like to do?\n");
    do
    {
        printf("Your options are: r (reveal tile), a (arm tile), d (disarm tile), h (get help), q (quit game).\n");
        scanf("%s", action);
        if (strlen(action) != 1)
        {
            printf("This is not a valid input.\n");
            continue;
        }

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

    } while (true);
}

void reveal_tile(Minesweeper m)
{
    int tile_row, tile_column;
    do
    {
        printf("Which tile do you want to reveal?\n");
        check_input_tile(m, &tile_row, &tile_column);

        if ((m.rows < tile_row) || (0 >= tile_row) || (m.columns < tile_column) || (tile_column <= 0))
        {
            printf("This is not on the board.\n");
        }
    } while ((m.rows < tile_row) || (0 >= tile_row) || (m.columns < tile_column) || (tile_column <= 0));

    if (*m.ptr_first_round)
    {
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

            initialize_field(m);
        }

        time_t start_time = time(0);
        *m.ptr_start_time = start_time;

        *m.ptr_first_round = false;
    }

    check_revealed_tile(m, tile_row, tile_column);
}

void check_revealed_tile(Minesweeper m, int tile_row, int tile_column)
{

    int chosen_tile = m.board[tile_row][tile_column];

    if (m.mask[tile_row][tile_column] == ARMED_TILE)
    {
        char answer[100];

        printf("This tile is set as armed. Do you wish to disarm it?\n");
        do
        {
            scanf("%s", answer);
            while (strlen(answer) != 1)
            {
                printf("Please answer y for yes or n for no.\n");
                scanf("%s", answer);
            }

            if (*answer == 'y')
            {
                m.mask[tile_row][tile_column] = COVERED_TILE;
                *m.ptr_number_tiles_armed -= 1;
                get_user_action(m);
                break;
            }
            if (*answer == 'n')
            {
                get_user_action(m);
                break;
            }
            else
            {
                printf("Please answer y for yes or n for no.\n");
            }

        } while (true);
    }
    if (m.mask[tile_row][tile_column] != COVERED_TILE)
    {
        dig_under_open_tile(m, tile_row, tile_column);
    }

    if (chosen_tile == MINE_TILE)
    {
        lost_game(m, tile_row, tile_column);
    }

    else
    {
        if (chosen_tile == EMPTY_TILE)
        {
            m.mask[tile_row][tile_column] = m.board[tile_row][tile_column];
            reveal_adjacent_tiles(m, tile_row, tile_column);
        }
        else
        {
            m.mask[tile_row][tile_column] = m.board[tile_row][tile_column];
        }
    }

    count_revealed_tiles(m, tile_row, tile_column);
    get_user_action(m);
}
void dig_under_open_tile(Minesweeper m, int tile_row, int tile_column)
{
    int chosen_tile = m.mask[tile_row][tile_column];

    if (m.mask[tile_row][tile_column] == EMPTY_TILE)
    {
        printf("You cannot dig under an empty tile.");
        get_user_action(m);
    }
    else
    {
        int count = 0;
        for (int a = (tile_row - 1); a <= (tile_row + 1); a++)
        {
            for (int b = (tile_column - 1); b <= (tile_column + 1); b++)
            {
                int temp_a = a;
                int temp_b = b;

                if (m.boundary)
                {
                    create_boundary_condition(m, &a, &b);
                }
                if (m.mask[a][b] == ARMED_TILE)
                {
                    count++;
                }
                a = temp_a;
                b = temp_b;
            }
        }

        if (chosen_tile <= count)
        {
            reveal_adjacent_tiles(m, tile_row, tile_column);
        }
        else
        {
            printf("There aren't enough surrounding armed tiles to dig");
            get_user_action(m);
        }
    }
}

void reveal_adjacent_tiles(Minesweeper m, int tile_row, int tile_column)
{

    for (int a = (tile_row - 1); a <= (tile_row + 1); a++)
    {
        for (int b = (tile_column - 1); b <= (tile_column + 1); b++)
        {
            int temp_a = a;
            int temp_b = b;
            if (m.boundary)
            {
                create_boundary_condition(m, &a, &b);
            }

            if (m.mask[a][b] != COVERED_TILE)
            {
                a = temp_a;
                b = temp_b;
                continue;
            }

            //irrelevant for empty tiles but important for digging
            if (m.board[a][b] == MINE_TILE)
            {
                lost_game(m, a, b);
            }

            m.mask[a][b] = m.board[a][b];
            if (m.board[a][b] == EMPTY_TILE)
            {
                reveal_adjacent_tiles(m, a, b);
            }
            a = temp_a;
            b = temp_b;
        }
    }
}

void count_revealed_tiles(Minesweeper m, int tile_row, int tile_column)
{
    int number_tiles_revealed = 0;
    int i, j;
    for (i = 1; i <= m.rows; i++)
    {

        for (j = 1; j <= m.columns; j++)
        {
            if (m.mask[i][j] == m.board[i][j])
            {
                number_tiles_revealed++;
            }
        }

        if (number_tiles_revealed == (m.rows * m.columns - m.mines))
        {
            won_game(m);
        }
    }
}

void arm_tile(Minesweeper m)
{
    int tile_row, tile_column;
    do
    {
        printf("Which tile do you want to set as armed?\n");
        check_input_tile(m, &tile_row, &tile_column);

        if (m.mask[tile_row][tile_column] == m.board[tile_row][tile_column])
        {
            printf("You cannot arm an open tile.\n");
        }

    } while (m.mask[tile_row][tile_column] == m.board[tile_row][tile_column]);

    m.mask[tile_row][tile_column] = ARMED_TILE;

    *m.ptr_number_tiles_armed += 1;
    get_user_action(m);
}

void disarm_tile(Minesweeper m)
{

    if (*m.ptr_number_tiles_armed == 0)
    {
        printf("There are no armed tiles to disarm.\n");
        sleep(2);
    }

    else
    {
        int tile_row, tile_column;
        do
        {
            printf("Which tile do you want to disarm?\n");
            check_input_tile(m, &tile_row, &tile_column);

            if (m.mask[tile_row][tile_column] != ARMED_TILE)
            {
                printf("This tile is not armed.\n");
            }

        } while (((m.rows < tile_row) || (0 >= tile_row) || (m.columns < tile_column) || (tile_column <= 0)) || (m.mask[tile_row][tile_column] != ARMED_TILE));

        m.mask[tile_row][tile_column] = COVERED_TILE;

        *m.ptr_number_tiles_armed -= 1;
    }
    get_user_action(m);
}

void won_game(Minesweeper m)
{
    system("clear"); // in anderem Betriebssystem anpassen --> readme
    print_won();
    printf("\n");
    print_final_mask(m, m.board, true, 0, 0);
    game_over(m);
}

void lost_game(Minesweeper m, int loser_row, int loser_column)
{
    system("clear"); // in anderem Betriebssystem anpassen --> readme
    print_lost();
    printf("\n");
    print_final_mask(m, m.mask, false, loser_row, loser_column);
    game_over(m);
}

void game_over(Minesweeper m)
{
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

    exit(0);
}

void check_input_tile(Minesweeper m, int *tile_row, int *tile_column)
{

    while (true)
    {
        //char input[100];
        //dachte das hilft vielleicht damit nichts doppelt geprinted wird
        char *input = malloc(sizeof(char) * 100);

        scanf("%s", input);

        char *ptr;
        char *ptr2;

        int count = 0;
        int position = 0;

        for (int i = 0; i < strlen(input); i++)
        {
            if (input[i] == ',')
            {
                count++;
                position = i;
            }
        }
        if (count != 1 || position == 0 || position == (strlen(input) - 1))
        {
            printf("Please use one comma to sepereate the number of row and column.\n");
            //hilft aber nicht
            free(input);
            continue;
        }

        if (strlen(input) > (get_int_len(m.rows) + get_int_len(m.columns) + 1) || strlen(input) < 3)
        {
            printf("This can't be right.\n");
            free(input);
            continue;
        }
        ptr = &input[0];
        ptr2 = &input[position + 1];

        *tile_row = atoi(ptr);
        *tile_column = atoi(ptr2);

        if (*tile_row <= 0 || *tile_column <= 0)
        {
            printf("This is not valid.\n");
            free(input);
            continue;
        }

        if ((m.rows < *tile_row) || (0 >= *tile_row) || (m.columns < *tile_column) || (*tile_column <= 0))
        {
            printf("This is not on the board.\n");
            free(input);
            continue;
        }

        else
        {
            break;
        }

        //for whatever reason suddenly not needed
        /*
        int count = 0;
        for(int i = 0; i < strlen(input); i++)
        {
            if(input[i] == ',')
            {
                count++;
            }
        }
        

        
        
        if(position == 1)
        {
            ptr = &input[0];
            number = atoi(ptr);
            if(0 >= number > 9)
            {
                printf("This is not valid.");
                continue;
            }
            ptr1 = &input[2];
            number1 = atoi(ptr1);
            if(number1 > 9)
            {
                printf("This is not valid.");
                continue;
            }
            *tile_column = number1;

            if(strlen(input) == 4)
            {
                ptr2 = &input[3];
                number2 = atoi(ptr2);
                if(number2 > 9)
                {
                    printf("This is not valid.");
                    continue;
                }
                *tile_column = (number1*10 + number2);
            }

            *tile_row = number;
            break;
            
        }
        if(position == 2)
        {
            ptr = &input[0];
            number = atoi(ptr);
            if(0 >= number > 9)
            {
                printf("This is not valid.");
                continue;
            }
            ptr1 = &input[1];
            number1 = atoi(ptr1);
            if(number1 > 9)
            {
                printf("This is not valid.");
                continue;
            }
            ptr2 = &input[3];
            number2 = atoi(ptr2);
            if(number2 > 9)
            {
                printf("This is not valid");
                continue;
            }

            *tile_column = number2;
            if(strlen(input) == 5)
            {
                ptr3 = &input[4];
                number3 = atoi(ptr3);
                if(number3 > 9)
                {
                    printf("This is not valid.");
                    continue;
                }
                *tile_column = (number2*10 + number3);
            }
            *tile_row = (number*10 + number1);
            break;
            
        }
        */
    }
}