#include<stdio.h>
#include<stdlib.h>

#include"text.h"

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
    printf("Hilfstext\n");

    printf("\n");
   
}

void print_help()
{
    printf("Optional arguments: -r, -c, -m. (For rows, columns and mines) Each followed by a number.\n\
Example: ./minesweeper -r 10 -c 10 -m 9\n\
If you want to play the extended version with periodic boundary conditions, add '-b'.\n");

}