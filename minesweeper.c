#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct Minesweeper{
        unsigned short int nRows;
        unsigned short int nCols;
        unsigned short int nMines;
        int **mask;
        int **board;

    } Minesweeper;

void test_function(Minesweeper mine);


int main(void)
{   
    
    Minesweeper minesweeper;
    
    minesweeper.nRows = 6;
    minesweeper.nCols = 5;
    
    int i;
    minesweeper.board = malloc(minesweeper.nRows * sizeof * minesweeper.board);
        for (i = 0; i < minesweeper.nRows; i++) {
            minesweeper.board[i] = malloc(minesweeper.nCols * sizeof * minesweeper.board[i]);
        }
    test_function(minesweeper);
    //minesweeper.board[1][1] = 3;
    printf("%d", minesweeper.board[1][1]);


}

void test_function(Minesweeper mine)
{
   
    mine.board[1][1] = 3;
}