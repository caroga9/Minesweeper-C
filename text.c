#include<stdio.h>
#include<stdlib.h>

#include"text.h"

void print_minesweeper()
{
    printf("#     #                                                                  \n");
    printf("##   ## # #    # ######  ####  #    # ###### ###### #####  ###### #####  \n");
    printf("# # # # # ##   # #      #      #    # #      #      #    # #      #    # \n");
    printf("#  #  # # # #  # #####   ####  #    # #####  #####  #    # #####  #    # \n");
    printf("#     # # #  # # #           # # ## # #      #      #####  #      #####  \n");
    printf("#     # # #   ## #      #    # ##  ## #      #      #      #      #   #  \n");
    printf("#     # # #    # ######  ####  #    # ###### ###### #      ###### #    # \n");
}

void print_lost()
{
    printf("#     #                                             \n");
    printf(" #   #   ####  #    #    #       ####   ####  ##### \n");
    printf("  # #   #    # #    #    #      #    # #        #   \n");
    printf("   #    #    # #    #    #      #    #  ####    #   \n");
    printf("   #    #    # #    #    #      #    #      #   #   \n");
    printf("   #    #    # #    #    #      #    # #    #   #   \n");
    printf("   #     ####   ####     ######  ####   ####    #   \n");
}

void print_won()
{
    printf("#     #                                       \n");
    printf(" #   #   ####  #    #    #    #  ####  #    # \n");
    printf("  # #   #    # #    #    #    # #    # ##   # \n");
    printf("   #    #    # #    #    #    # #    # # #  # \n");
    printf("   #    #    # #    #    # ## # #    # #  # # \n");
    printf("   #    #    # #    #    ##  ## #    # #   ## \n");
    printf("   #     ####   ####     #    #  ####  #    # \n");
}
