#include <stdio.h>
#include <stdlib.h>

#include "text.h"

void print_minesweeper()
{
    printf("\x1b[34m");
    printf("#     #                                                                  \n");
    printf("##   ## # #    # ######  ####  #    # ###### ###### #####  ###### #####  \n");
    printf("# # # # # ##   # #      #      #    # #      #      #    # #      #    # \n");
    printf("#  #  # # # #  # #####   ####  #    # #####  #####  #    # #####  #    # \n");
    printf("#     # # #  # # #           # # ## # #      #      #####  #      #####  \n");
    printf("#     # # #   ## #      #    # ##  ## #      #      #      #      #   #  \n");
    printf("#     # # #    # ######  ####  #    # ###### ###### #      ###### #    # \n");
    printf("\x1b[0m");
}

void print_lost()
{
    printf("\x1b[31m");
    printf("#     #                                             \n");
    printf(" #   #   ####  #    #    #       ####   ####  ##### \n");
    printf("  # #   #    # #    #    #      #    # #        #   \n");
    printf("   #    #    # #    #    #      #    #  ####    #   \n");
    printf("   #    #    # #    #    #      #    #      #   #   \n");
    printf("   #    #    # #    #    #      #    # #    #   #   \n");
    printf("   #     ####   ####     ######  ####   ####    #   \n");
    printf("\x1b[0m");
}

void print_won()
{
    printf("\x1b[32m");
    printf("#     #                                       \n");
    printf(" #   #   ####  #    #    #    #  ####  #    # \n");
    printf("  # #   #    # #    #    #    # #    # ##   # \n");
    printf("   #    #    # #    #    #    # #    # # #  # \n");
    printf("   #    #    # #    #    # ## # #    # #  # # \n");
    printf("   #    #    # #    #    ##  ## #    # #   ## \n");
    printf("   #     ####   ####     #    #  ####  #    # \n");
    printf("\x1b[0m");
}

void print_inGame_help()
{
    printf("How to play the game?\n\
On your first round you chose a tile of your choice. It doesn't matter which one.\n\
Now you have several options: \n\
- If there is a mine under the tile you opened, you automatically lose. \n\
- If the tile you opened is an empty tile, then all the adjacent tiles, which are not mines or armed, get revealed.  \n \
- If there is a number under the tile you opned, you now know how many adjacent tiles are mines. \n \
- You also can arm a tile under which you think may be a mine. With that choice it is easier to get an overview of the mines on the field. \n \
To win the game you have to open all tiles, which are not mines or armed tiles. \n \
You lose the game if you found a mine. \n");
    printf("Press any button to get back to the game.\n");
    char action[100];
    scanf("%s", action);
}

void print_help()
{
    printf("Optional arguments: -r, -c, -m. (For rows, columns and mines) Each followed by a number.\n\
Example: ./minesweeper -r 10 -c 10 -m 9\n\
If you want to play the extended version with periodic boundary conditions, add '-b'.\n");
}