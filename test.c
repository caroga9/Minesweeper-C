#include<stdio.h>
#include<time.h>
#include<stdlib.h>

typedef struct Minesweeper{
        unsigned short int rows;
        unsigned short int columns;
        unsigned short int mines;
        int **mask;
        int **board;

        int number_tiles_revealed;
        int *ptr_nr_tiles_revealed;

        long start_time;
        long *ptr_start_time;
        
        

    } Minesweeper;
    
void second_test(Minesweeper m)
{
    printf("%d", *m.ptr_nr_tiles_revealed);
}
void test_function(Minesweeper m)
{
    int test;
    do
    {
        scanf("%d", &test);
    }while(test != 3);
}

double timer(Minesweeper m);

int main(void)
{   
    Minesweeper m; // setze minesweeper als struct Typ Minesweeper fest
    /*m.ptr_nr_tiles_revealed = &m.number_tiles_revealed;
    *m.ptr_nr_tiles_revealed = 3;
    printf("%d", m.number_tiles_revealed);
    test_function(m);
    printf("%d", m.number_tiles_revealed);*/
    /*clock_t start_time = clock();
    printf("%lo\n", start_time);
    *m.ptr_start_time = start_time;*/
    m.ptr_start_time = &m.start_time;
    time_t start_time = time(0);
    *m.ptr_start_time = start_time;
    printf("start: %lo\n", *m.ptr_start_time);
    test_function(m);
    if()
    {
        printf("test");
    }
    timer(m);

}
double timer(Minesweeper m)
{
    /*clock_t current_time, time_passed;
    current_time = clock();
    time_passed = (double)(current_time - *m.ptr_start_time) / CLOCKS_PER_SEC;
    printf("%lo\n", CLOCKS_PER_SEC);
    printf("%lo\n", current_time);
    printf("%lo\n", time_passed);*/
    time_t now = time(0);
    printf("now: %lo\n", now);
    int time_passed;
    time_passed = now - m.start_time;
    printf("passed: %d\n", time_passed);

    return time_passed;
}