#include"board.h"

void create_boundary_condition(Minesweeper m, int *a, int *b)
{
    if(*a == 0 && *b == 0)
    {
        *a = m.rows;
        *b = m.columns;
    }
    if(*a == m.rows +1 && *b == m.columns +1)
    {
        *a = 1;
        *b = 1;
    }
    if(*a == m.rows +1 && *b == 0)
    {
        *a = 1;
        *b = m.columns;
    }
    if(*a == 0 && *b == m.columns +1)
    {
        *a = m.rows;
        *b = 1;
    }
    if(*a == 0 && (0 < *b <= m.columns))
    {
        *a = m.rows;
    }
    if(*a == m.rows +1 && (0 < *b <= m.columns))
    {
        *a = 1;
    }
    if((0 < *a <= m.rows) && *b == 0)
    {
        *b = m.columns;
    }
    if((0 < *a <= m.rows) && *b == m.columns + 1)
    {
        *b = 1;
    }
/*
    //making sure corner tiles get correct neighbours
    m.board[0][0] = m.board[m.rows][m.columns];
    m.board[0][m.columns + 1] = m.board[m.rows][1];
    m.board[m.rows +1][0] = m.board[1][m.columns];
    m.board[m.rows +1][m.columns +1] = m.board[1][1];

    int j;
    // same for other border tiles
    
    for(j = 1; j <= (m.columns); j++)
    {
        //first row
        m.board[0][j] = m.board[m.rows][j];
        //last row
        m.board[m.rows+1][j] = m.board[1][j];
    }


    for(j = 1; j <= (m.rows); j++)
    {
        //first column
        m.board[j][0] = m.board[j][m.columns];
        //last column
        m.board[j][m.columns + 1] = m.board[j][1];
    }*/
}

void initialize_field(Minesweeper m)
{   

    create_mines(m);
    /*if(m.boundary)
    {
        create_boundary_coundition(m);
    }*/
    number_fields(m);
    create_mask(m);
    
    printf("\n");
    
}

void create_mask(Minesweeper m)
{
    int i, j;
    for(i = 1; i <= m.rows; i++)
    {
        
        for(j = 1; j <= m.columns; j++)
        {
            m.mask[i][j] = COVERED_TILE; // 64 in Ascii ist @
            
        }  
    }
}

void create_mines(Minesweeper m)
{
    int position_row, position_column; 
    srand(time(NULL)); 

    for(int mine = 0; mine < m.mines; mine++)
    {
        
        do {
            position_row = rand() % ((m.rows + 1) - 1) + 1;
            position_column = rand() % ((m.columns + 1) - 1) +1;

           } while (m.board[position_row][position_column] == MINE_TILE); // 42 in Ascii ist *
        
        m.board[position_row][position_column] = MINE_TILE;
        //printf("Mine: %d, %d\n", position_row, position_column);

    }

    
}

// könnte effizienter gemacht werden mit Jans Art
void number_fields(Minesweeper m)
{   
    int i,j;
    for(i = 1; i <= m.rows; i++)
    {
        for(j = 1; j <= m.columns; j++)
        {
            if (m.board[i][j] != MINE_TILE)
            {   
                
                int count = 0;
                for(int a = (i-1); a <= (i+1); a++)
                { 
                    for(int b =(j-1); b<= (j+1); b++)
                    {   
                        int temp_a = a;
                        int temp_b = b;
                        if(m.boundary)
                        {
                            create_boundary_condition(m, &a, &b);
                        }
                        if (m.board[a][b] == MINE_TILE)
                        {
                            count++;

                        }
                        a = temp_a;
                        b = temp_b;
                    }
                }
                m.board[i][j] = count;
            }

        }
    }

    // making sure border tiles that actually don't belong to the board don't get a 0
    for(i = 0; i<= (m.rows +1); i += (m.rows +1))
    {
        for(j = 0; j <= (m.columns +1); j++)
        {
            m.board[i][j] = BORDER_TILE;
        }
    }

    for(j = 0; j<= (m.columns +1); j += (m.columns +1))
    {
        for(i = 0; i<=(m.rows +1); i++)
        {
            m.board[i][j] = BORDER_TILE;
        }
    }

    // turning all 0 tiles into actual empty tiles
    for(i = 1; i <= m.rows; i++)
    {
        
        for(j = 1; j <= m.columns; j++)
        {
            if(m.board[i][j] == 0)
            {
                m.board[i][j] = EMPTY_TILE;
            } 
            
        }  
    }
}


int timer(Minesweeper m)
{
    /*clock_t current_time, time_passed;
    current_time = clock();
    time_passed = (double)(current_time - *m.ptr_start_time) / CLOCKS_PER_SEC;
    printf("%lo\n", CLOCKS_PER_SEC);
    printf("%lo\n", current_time);
    printf("%lo\n", time_passed);*/
    time_t now = time(0);
    
    int time_passed;
    time_passed = now - *m.ptr_start_time;
    

    return time_passed;
}
int get_int_len (int value)
{

    int len = 1;

    while(value > 9) {

        len++;

        value/=10;

    }

    return len;

}
void print_grid(Minesweeper m, int** grid, bool **first_round)
{   

    printf("Number of mines: %d\nTiles marked as armed: %d\n\n", m.mines, *m.ptr_number_tiles_armed );
    //printf("Number tiles revealed: %d", *m.ptr_number_tiles_revealed);
    if(!**first_round)
    {
        printf("Time elapsed: %ds\n\n",timer(m));
    }
    int i,j;
    for(int x = 0; x< get_int_len(m.columns); x++)
    {
        printf(" ");
    }
    for(j=1; j<= m.columns ; j++)
        {
            //printf("_%c[4m%d%c[0m", 27, j, 27);
            for (int padding = 0; padding + get_int_len(j) < get_int_len(m.columns); padding++)
            {
                printf(" ");
            }
            printf(" %d", j);
        }
    printf("\n");
    for(i = 1; i<= m.rows ; i++)
    {   
        for (int padding = 0; padding + get_int_len(i) < get_int_len(m.rows); padding++) 
        {

            printf(" ");

        }
        printf("%d", i);
        for(j=1; j<= m.columns ; j++)
        {   
            //if((grid[i][j] == COVERED_TILE) || (grid[i][j] == MINE_TILE) || (grid[i][j] == ARMED_TILE) || (grid[i][j] == BORDER_TILE) || (grid[i][j] == EMPTY_TILE))
            //{   

                //printf("| %c", grid[i][j]);
                //printf("%c[4m%c%c[0m", 27, grid[i][j], 27);
                //printf("%c", grid[i][j]);
                printf("|");
                
                switch(grid[i][j]) 
                {
                    case COVERED_TILE: printf(COLOR_COVERED_TILE); break;
                    case MINE_TILE: printf(COLOR_MINE_TILE); break;
                    case ARMED_TILE: printf(COLOR_ARMED_TILE); break;
                    case 1: printf(COLOR_1); break;
                    case 2: printf(COLOR_2); break;
                    case 3: printf(COLOR_3); break;
                    case 4: printf(COLOR_4); break;
                    case 5: printf(COLOR_5); break;
                    case 6: printf(COLOR_6); break;
                    case 7: printf(COLOR_7); break;
                    case 8: printf(COLOR_8); break;

                }
                for(int x = 1; x< get_int_len(m.columns); x++)
                {
                    printf(" ");
                }

                if(grid[i][j] <= 8)
                {
                    printf("%d", grid[i][j]);
                }
                else
                {
                    printf(" ");
                }
                printf(COLOR_RESET);

            /*}
            else
            {
                //printf("|%c[4m%d%c[0m", 27, grid[i][j], 27);
                printf("|%d", grid[i][j]);
            }*/
            
        }
        
        printf("|\n");
    }
    for(int x = 0; x< get_int_len(m.columns); x++)
    {
        printf(" ");
    }
    for(j=1; j<= m.columns ; j++)
        {
            //printf("_%c[4m%d%c[0m", 27, j, 27);
            for (int padding = 0; padding + get_int_len(j) < get_int_len(m.columns); padding++)
            {
                printf(" ");
            }
            printf(" %d", j);
        }
    printf("\n");
}

void print_final_mask(Minesweeper m, int **grid, bool won_game, int loser_row, int loser_column)
{
    int i,j;
    printf("   ");
    for(j=1; j<= m.columns ; j++)
    {
        for (int padding = 0; padding + get_int_len(j) < get_int_len(m.columns); padding++)
        {
            printf(" ");
        }
        
        printf(" %d", j);
    }
    printf("\n");
    for(i = 1; i<= m.rows ; i++)
    {   
        for(int padding = 0; padding + get_int_len(i) < get_int_len(m.rows); padding++) 
        {

            printf(" ");

        }
        printf("%d ", i);
        for(j=1; j<= m.columns ; j++)
        {       
            if(m.board[i][j] == MINE_TILE)
            {
                grid[i][j] = MINE_TILE;
            }
                printf("|");
                switch(grid[i][j]) 
                {
                    case MINE_TILE: printf(COLOR_MINE_TILE); break;
                    case COVERED_TILE: printf(COLOR_COVERED_TILE); break;
                    case 1: printf(COLOR_1); break;
                    case 2: printf(COLOR_2); break;
                    case 3: printf(COLOR_3); break;
                    case 4: printf(COLOR_4); break;
                    case 5: printf(COLOR_5); break;
                    case 6: printf(COLOR_6); break;
                    case 7: printf(COLOR_7); break;
                    case 8: printf(COLOR_8); break;

                }

                if(grid[i][j] <= 8)
                {   
                    for(int x = 1; x< get_int_len(m.columns); x++)
                    {
                        printf(" ");
                    }
                    printf("%d", grid[i][j]);
                }
                else
                {   
                    if(!won_game)
                    {
                        if(i == loser_row && j == loser_column)
                        {
                            printf(COLOR_LOSER_TILE);
                        }
                    }
                    if(won_game)
                    {
                        if(grid[i][j] == MINE_TILE)
                        {
                            printf(COLOR_WON_MINE);
                        }
                    }
                     for(int x = 1; x< get_int_len(m.columns); x++)
                    {
                        printf(" ");
                    }
                    printf(" ");
                }
                printf(COLOR_RESET);
            /*}
            else
            {
                //printf("|%c[4m%d%c[0m", 27, grid[i][j], 27);
                printf("|%d", grid[i][j]);
            }*/
            
        }
        printf("|\n");
    }
    printf(" ");
    for(int x = 0; x< get_int_len(m.columns); x++)
    {
        printf(" ");
    }
    for(j=1; j<= m.columns ; j++)
        {
            //printf("_%c[4m%d%c[0m", 27, j, 27);
            for (int padding = 0; padding + get_int_len(j) < get_int_len(m.columns); padding++)
            {
                printf(" ");
            }
            printf(" %d", j);
        }
    printf("\n");
}