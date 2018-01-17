#include "board.h"

//TODO:
//      Kommentare !!  (bevor ich es Sina zeige)
//      Testfunktionen schreiben !!
//      Argumente aus Kommandozeile besser evaluieren (+ getopt Funktion anschauen) !!
//      Hilfstexte schreiben !
//      evtl. beide print_grid Funktionen zusammenführen
//      ReadMe
//      (angezeigtes Feld verschönern)

int main(int argc, char *argv[])
{
    //declare minesweeper as struct of type Minesweeper
    Minesweeper minesweeper;

    //parse command line arguments
    //check number of arguments
    if (argc == 2)
    {
        if (*argv[1] == 'h')
        {
            print_help();
            exit(0);
        }

        //if there aren't enough arguments given, start default game
        else
        {
            minesweeper.rows = 8;
            minesweeper.columns = 8;
            minesweeper.mines = 7;
            minesweeper.boundary = false;
        }
    }

    //if there aren't enough arguments given, start default game
    if (argc == 3 || argc == 1)
    {
        minesweeper.rows = 8;
        minesweeper.columns = 8;
        minesweeper.mines = 7;
        minesweeper.boundary = false;
    }

    //if there are enough arguments, check for reasonable numbers
    if (argc == 4)
    {
        if (atoi(argv[1]) > 99 || atoi(argv[2]) > 99)
        {
            printf("This field is too large (under 100 is fine)");
            exit(0);
        }
        if (atoi(argv[3]) >= atoi(argv[1]) * atoi(argv[2]))
        {
            printf("You cannot have a field full of mines.");
            exit(0);
        }

        //set given numbers as field parameters
        minesweeper.rows = atoi(argv[1]);
        minesweeper.columns = atoi(argv[2]);
        minesweeper.mines = atoi(argv[3]);
        minesweeper.boundary = false;
    }

    //same as before but including argument for game with boundary conditions
    if (argc == 5)
    {
        if (atoi(argv[1]) > 99 || atoi(argv[2]) > 99)
        {
            printf("This field is too large (under 100 is fine)");
            exit(0);
        }
        if (atoi(argv[3]) >= atoi(argv[1]) * atoi(argv[2]))
        {
            printf("You cannot have a field full of mines.");
            exit(0);
        }

        minesweeper.rows = atoi(argv[1]);
        minesweeper.columns = atoi(argv[2]);
        minesweeper.mines = atoi(argv[3]);

        //include boundary conditions
        minesweeper.boundary = true;
    }

    //give useful information on how to give command line arguments
    if (argc > 5)
    {
        printf("Enter either nothing to start default game or numbers in the following order:\n");
        printf("rows rolumns mines (optional: any number for game with boundary conditions)\n");
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
    initialize_field(minesweeper);

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
