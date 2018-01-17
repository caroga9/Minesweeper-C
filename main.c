#include"board.h"

//TODO: 
//      Kommentare !!  (bevor ich es Sina zeige)
//      Test.c nochmal anschauen und game_logic.c anpassen. Wieso geht das auf einmal??
//      Testfunktionen schreiben !!
//      Argumente aus Kommandozeile besser evaluieren (+ getopt Funktion anschauen) !!
//      Hilfstexte schreiben !
//      evtl. beide print_grid Funktionen zusammenführen
//      ReadMe
//      (angezeigtes Feld verschönern)


int main(int argc, char *argv[])
{   
    
    Minesweeper minesweeper; // setze minesweeper als struct Typ Minesweeper fest
    
    // argv Eingabe überprüfen
    if(argc == 2)
    {
        if(*argv[1] == 'h')
        {
            print_help();
            exit(0);
        }       else
        {
            minesweeper.rows = 8;
            minesweeper.columns = 8;
            minesweeper.mines = 7;
            minesweeper.boundary = false;
        }
    }

    if(argc == 3 || argc == 1)
    {
        minesweeper.rows = 8;
        minesweeper.columns = 8;
        minesweeper.mines = 7;
        minesweeper.boundary = false;

    }
    if(argc == 4)
    {
        if(atoi(argv[1]) > 99 || atoi(argv[2]) > 99)
        {
            printf("This field is too large (under 100 is fine)");
            exit(0);
        }
        if(atoi(argv[3]) >= atoi(argv[1])*atoi(argv[2]))
        {
            printf("You cannot have a field full of mines.");
            exit(0);
        }
        minesweeper.rows = atoi(argv[1]);
        minesweeper.columns = atoi(argv[2]);
        minesweeper.mines = atoi(argv[3]);
        minesweeper.boundary = false;
    }
    if(argc == 5)
    {
        if(atoi(argv[1]) > 99 || atoi(argv[2]) > 99)
        {
            printf("This field is too large (under 100 is fine)");
            exit(0);
        }
        if(atoi(argv[3]) >= atoi(argv[1])*atoi(argv[2]))
        {
            printf("You cannot have a field full of mines.");
            exit(0);
        }
        minesweeper.rows = atoi(argv[1]);
        minesweeper.columns = atoi(argv[2]);
        minesweeper.mines = atoi(argv[3]);
        minesweeper.boundary = true;
    }
    if(argc > 5)
    {
        printf("Enter either nothing to start default game or numbers in the following order:\n"); 
        printf("rows rolumns mines (optional: any number for game with boundary conditions)\n");
        exit(0);
    }

    //minesweeper.ptr_number_tiles_revealed = &minesweeper.number_tiles_revealed;
    minesweeper.ptr_start_time = &minesweeper.start_time;
    minesweeper.ptr_number_tiles_armed = &minesweeper.number_tiles_armed;

    *minesweeper.ptr_number_tiles_armed = 0;
    //*minesweeper.ptr_number_tiles_revealed = 0;
    
    bool first_round = true;


    int i;
    minesweeper.board = malloc((minesweeper.rows +2) * sizeof *minesweeper.board);
    for (i = 0; i < (minesweeper.rows +2); i++) {
        minesweeper.board[i] = malloc((minesweeper.columns+2) * sizeof *minesweeper.board[i]);
    }

    minesweeper.mask = malloc((minesweeper.rows +2)* sizeof *minesweeper.mask);
    for (i = 0; i < (minesweeper.rows +2); i++) {
        minesweeper.mask[i] = malloc((minesweeper.columns +2) * sizeof *minesweeper.mask[i]);
    }

    print_minesweeper();
    sleep(3);
    initialize_field(minesweeper);
    
    get_user_action(minesweeper, &first_round);
   
    

    for (i = 0; i < minesweeper.rows+2; i++) {
        free(minesweeper.mask[i]);
    }
    free(minesweeper.mask);

    for (i = 0; i < minesweeper.rows+2; i++) {
        free(minesweeper.board[i]);
    }
    free(minesweeper.board);
    
}

