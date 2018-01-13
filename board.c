#include"board.h"

void create_boundary_coundition(Minesweeper m)
{
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
    }
}

void initialize_field(Minesweeper m)
{   

    create_mines(m);
    if(m.boundary)
    {
        create_boundary_coundition(m);
    }
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
                        if (m.board[a][b] == MINE_TILE)
                        {
                            count++;
                        }

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
void print_grid(Minesweeper m, int** grid, bool **first_round)
{   

    printf("Number of mines: %d\nTiles marked as armed: %d\n", m.mines, *m.ptr_number_tiles_armed );
    //printf("Number tiles revealed: %d", *m.ptr_number_tiles_revealed);
    if(!**first_round)
    {
        printf("Time elapsed: %ds\n ",timer(m));
    }
    int i,j;
    for(j=1; j<= m.columns ; j++)
        {
            printf("  %d", j);
        }
    printf("\n");
    printf(" \n");
    for(i = 1; i<= m.rows ; i++)
    {   
        printf("%d ", i);
        for(j=1; j<= m.columns ; j++)
        {   
            if((grid[i][j] == COVERED_TILE) || (grid[i][j] == MINE_TILE) || (grid[i][j] == ARMED_TILE) || (grid[i][j] == BORDER_TILE) || (grid[i][j] == EMPTY_TILE))
            {
                printf("| %c", grid[i][j]);
            }
            else
            {
                printf("| %d", grid[i][j]);
            }
            
        }
        printf("|\n");
    }
    
}