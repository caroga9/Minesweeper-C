#include "board.h"

int main(int argc, char *argv[])
{
    //create error-file for this run
    file = fopen("erro_file.txt", "w");

    //declare minesweeper as struct of type Minesweeper
    Minesweeper minesweeper;

    //default parameters
    int option = 0;
    minesweeper.rows = 8;
    minesweeper.columns = 8;
    minesweeper.mines = 7;
    minesweeper.boundary = false;
    minesweeper.test = false;

    //parse input and 
    while ((option = getopt(argc, argv, "r:c:m:hb")) != -1)
    {
        switch (option)
        {
        case 'r':
            if(!(minesweeper.rows = abs(atoi(optarg))))
            {
                fprintf(file, "In 'main': wrong command line argument: %s", optarg);
                exit(0);
            }
            break;
        case 'c':
            if(!(minesweeper.columns = abs(atoi(optarg))))
            {
                fprintf(file, "In 'main': wrong command line argument: %s", optarg);
                exit(0);
            }
            break;
        case 'm':
            if(!(minesweeper.mines = abs(atoi(optarg))))
            {
                fprintf(file, "In 'main': wrong command line argument: %s", optarg);
                exit(0);
            }
            break;
        case 'h':
            print_help();
            exit(0);
            break;
        case 'b':
            minesweeper.boundary = true;
            break;
        default:
            break;
        }
    }

    if(minesweeper.mines >= (minesweeper.rows*minesweeper.columns))
    {
        printf("At least one tile must be mine-free.\n");
        exit(0);
    }

    //declare pointers to struct parameters that need to be changed during the game
    minesweeper.ptr_start_time = &minesweeper.start_time;
    minesweeper.ptr_number_tiles_armed = &minesweeper.number_tiles_armed;
    minesweeper.ptr_first_round = &minesweeper.first_round;

    //initialize pointers
    *minesweeper.ptr_number_tiles_armed = 0;
    *minesweeper.ptr_first_round = true;

    //allocate memory for the board
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

    //print welcome message with time delay (otherwise you wouldn't see it)
    print_minesweeper();
    sleep(3);

    //start game
    create_mask(minesweeper);
    get_user_action(minesweeper);

    //free memory when game is over
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
