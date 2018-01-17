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
    printf("Hilfstext\n");

}