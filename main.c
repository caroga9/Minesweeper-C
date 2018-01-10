#include"board.h"
//TODO: Problem mit doppelt printen lösen
//      Argumente aus Kommandozeile evaluieren (+ getopt Funktion anschauen)
//      angezeigtes Feld verschönern, vor allem alle Felder einheitliche Größe
//      fancy you won/you lost printen
//      timer erst nach erstem Aufdecken starten


//Jan fragen:   wieso geht das mit dem Timer nicht an anderer Stelle?
//              wieso printed der doppelt?
//              


int main(int argc, char *argv[])
{   
    
    Minesweeper minesweeper; // setze minesweeper als struct Typ Minesweeper fest
    
    // argv Eingabe überprüfen
    minesweeper.rows = atoi(argv[1]);
    minesweeper.columns = atoi(argv[2]);;
    minesweeper.mines = atoi(argv[3]);

    minesweeper.ptr_number_tiles_revealed = &minesweeper.number_tiles_revealed;
    minesweeper.ptr_start_time = &minesweeper.start_time;
    minesweeper.ptr_number_tiles_armed = &minesweeper.number_tiles_armed;

    *minesweeper.ptr_number_tiles_armed = 0;
    *minesweeper.ptr_number_tiles_revealed = 0;
    
    bool first_round;
    bool ptr_first_round = &first_round;
    *ptr_first_round = true;
    
    
    time_t start_time = time(0);
    *minesweeper.ptr_start_time = start_time;
    printf("start: %lo\n", *minesweeper.ptr_start_time);

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
    initialize_field(minesweeper);
    
    get_user_action(minesweeper, first_round);
   
    

    for (i = 0; i < minesweeper.rows; i++) {
        free(minesweeper.mask[i]);
    }
    free(minesweeper.mask);

    for (i = 0; i < minesweeper.rows; i++) {
        free(minesweeper.board[i]);
    }
    free(minesweeper.board);
    
}

