#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include <string.h>
#include <unistd.h>
#define ANSI_COLOR_PURPLE     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int test(int *a, int *b)
{
  *a = 3;
  *b = 4;

}
int main (void) {
int a=2;

switch(a) {
	case 1: printf("a ist eins\n"); break;
	case 2: printf("a ist zwei\n"); break;
	case 3: printf("a ist drei\n"); break;
	default: printf("a ist irgendwas\n"); continu;
}
}