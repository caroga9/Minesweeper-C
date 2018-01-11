#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include <stdbool.h>

void third_test(bool ***first_round)
{
     if(***first_round)
    {
        
        printf("yes!");
    }
}
void second_test(bool **first_round)
{
   **first_round = false;
   third_test(&first_round);
    
}
void test_function(bool *first_round)
{
    
    second_test(&first_round);
}


int main(void)
{   
     // setze minesweeper als struct Typ Minesweeper fest
    /*m.ptr_nr_tiles_revealed = &m.number_tiles_revealed;
    *m.ptr_nr_tiles_revealed = 3;
    printf("%d", m.number_tiles_revealed);
    test_function(m);
    printf("%d", m.number_tiles_revealed);*/
    /*clock_t start_time = clock();
    printf("%lo\n", start_time);
    *m.ptr_start_time = start_time;*/
    bool first_round = true;
    printf("%d", first_round);
    //printf("%d", &first_round);
    
    test_function(&first_round);
   

}
