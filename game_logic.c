#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <stdbool.h>

#include"board.h"

//warum kommt die Frage doppelt? hat was mit Enter zu tun nehme ich an
void get_user_action(Minesweeper m, bool ptr_first_round)
{   
    char action;
    do
    {   
        print_grid(m, m.mask);
        printf("What would you like to do?\nYour options are: r (reveal tile), a (arm tile), d (disarm tile), h (get help), q (quit game).\n ");
        scanf("%c", &action);

        if(action == 'r')
        {
            reveal_tile(m, ptr_first_round);
            
        }
        if(action == 'a')
        {
            arm_tile(m);
            
        }
        if(action == 'd')
        {
            disarm_tile(m);
            
        }
        if(action == 'h')
        {
            print_inGame_help();
            
        }
        if(action == 'q')
        {
            game_over(m);
            break;
        }

    }while(true);
  

}

void reveal_tile(Minesweeper m, bool ptr_first_round)
{   
    int tile_row, tile_column;
    do
    {   // wie fängt man Falschinput ab in diesem Fall? zb ein Buchstabe
        printf("Which tile do you want to reveal?\n");
        scanf("%d %d", &tile_row, &tile_column);
        
        if((m.rows < tile_row ) || (0 >= tile_row) || (m.columns < tile_column) || (tile_column <= 0))
        {
            printf("This is not on the board.\n");
        }
    }while((m.rows < tile_row ) || (0 >= tile_row) || (m.columns < tile_column) || (tile_column <= 0));

    if(*ptr_first_round)
    {
        while(m.board[tile_row][tile_column] == MINE_TILE)
        {   
            int i,j;
            for(i = 1; i <= m.rows; i++)
            {
                for(j = 1; j <= m.columns; j++)
                {
                    
                    m.board[i][j] = 0;
                    
                }  
            }

            initialize_field(m);
        }


        *ptr_first_round = false;

    }
    check_revealed_tile(m, tile_row, tile_column);
}

void check_revealed_tile(Minesweeper m, int tile_row, int tile_column)
{   

    int chosen_tile = m.board[tile_row][tile_column];

    if(m.mask[tile_row][tile_column] == ARMED_TILE)
    {   
        char answer;
        
        printf("This tile is set as armed. Do you wish to disarm it?\n");
        do
        {
            scanf("%s", &answer);

            // warning multi character constant lösen
            if(answer == 'y')
            {
                m.mask[tile_row][tile_column] = COVERED_TILE;
                *m.ptr_number_tiles_armed -= 1;
                get_user_action(m, false);
                break;
            }
            if(answer == 'n')
            {
                get_user_action(m, false);
            }
            else
            {
                printf("Please answer y for yes or n for no.\n");
            }

        }while(true);
    }
    if(m.mask[tile_row][tile_column] != COVERED_TILE)
    {
        dig_under_open_tile(m, tile_row, tile_column);
    }

    if(chosen_tile == MINE_TILE)
    {
        lost_game(m, tile_row, tile_column);
    }

    else
    {   
        if(*m.ptr_number_tiles_revealed == (m.rows*m.columns - m.mines))
        {
            won_game(m, tile_row, tile_column);
        }
        else
        {   
            if(chosen_tile == EMPTY_TILE)
            {
                //flood-fill
                m.mask[tile_row][tile_column] = m.board[tile_row][tile_column];
                reveal_adjacent_tiles(m, tile_row, tile_column);
                
            }
            else
            {
                *m.ptr_number_tiles_revealed += 1; 
                m.mask[tile_row][tile_column] = m.board[tile_row][tile_column];
                
            }
            
        }
    }
}
void dig_under_open_tile(Minesweeper m, int tile_row, int tile_column)
{   
    int chosen_tile = m.mask[tile_row][tile_column];

    if (m.mask[tile_row][tile_column] != EMPTY_TILE)
    {   
        int count = 0;
        for(int a = (tile_row -1); a <= (tile_row +1); a++)
        { 
            for(int b =(tile_column -1); b<= (tile_column +1); b++)
            {
                if (m.mask[a][b] == ARMED_TILE)
                {
                    count++;
                }

            }
        }

        if(chosen_tile <= count)
        {
            reveal_adjacent_tiles(m, tile_row, tile_column);
        }
    }
}

void reveal_adjacent_tiles(Minesweeper m, int tile_row, int tile_column)
{
    
    for(int a = (tile_row -1); a <= (tile_row +1); a++)
    { 
        for(int b =(tile_column -1); b<= (tile_column +1); b++)
        {  
            if(m.mask[a][b] != COVERED_TILE)
            {
                continue;
            }

            //irrelevant for empty tiles but important for digging
            if(m.board[a][b] == MINE_TILE)
            {
                lost_game(m, a, b);
            }

            m.mask[a][b] = m.board[a][b];
            *m.ptr_number_tiles_revealed += 1; 

            if(m.board[a][b] == EMPTY_TILE)
            {
               reveal_adjacent_tiles(m, a, b);
            }
        }
    }

}
void lost_game(Minesweeper m,int loser_row, int loser_column)
{   
    // Feld nochmal printen mit loser_tile und Farben
    print_lost();
    
    game_over(m);
}

void arm_tile(Minesweeper m)
{
    int tile_row, tile_column;
    do
    {
        printf("Which tile do you want to set as armed?\n");
        scanf("%d %d", &tile_row, &tile_column);
        
        if((m.rows < tile_row ) || (0 >= tile_row) || (m.columns < tile_column) || (tile_column <= 0))
        {
            printf("This is not on the board.\n");
        }
    }while((m.rows < tile_row ) || (0 >= tile_row) || (m.columns < tile_column) || (tile_column <= 0));

    m.mask[tile_row][tile_column] = ARMED_TILE;

    *m.ptr_number_tiles_armed += 1;
    
}

void disarm_tile(Minesweeper m)
{
    
    if(*m.ptr_number_tiles_armed == 0)
    {
        printf("There are no armed tiles to disarm.\n");
        printf("\n");
    }

    else
    {
        int tile_row, tile_column;
        do
        {   
            printf("Which tile do you want to disarm?\n");
            scanf("%d %d", &tile_row, &tile_column);
            
            if((m.rows < tile_row ) || (0 >= tile_row) || (m.columns < tile_column) || (tile_column <= 0))
            {
                printf("This is not on the board.\n");
            }

            if(m.mask[tile_row][tile_column] != ARMED_TILE)
            {
                printf("This tile is not armed.\n");
            }
        }while(((m.rows < tile_row ) || (0 >= tile_row) || (m.columns < tile_column) || (tile_column <= 0)) || (m.mask[tile_row][tile_column] != ARMED_TILE));

        m.mask[tile_row][tile_column] = COVERED_TILE;

        *m.ptr_number_tiles_armed -= 1;
        
    }
}

void print_inGame_help()
{
    printf("Hilfstext\n");
    printf("\n");
   
}




void won_game(Minesweeper m, int winner_row, int winner_column)
{   
    //Feld nochmal printen mit winner_tile und Farben
    print_won();
    game_over(m);
}

void game_over(Minesweeper m)
{
    int i;

    for (i = 0; i < m.rows; i++) 
    {
    free(m.mask[i]);
    }

    free(m.mask);

    for (i = 0; i < m.rows; i++) 
    {
        free(m.board[i]);
    }

    free(m.board);

    exit(0);
}

