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
	char input[100];
	scanf("%s", input);
	int count =0;
	count = 0;
	int position = 0;
	for(int i = 0; i < strlen(input); i++)
	{
		if(input[i] == ',')
		{
			count++;
			position = i;
		}
	}
	printf("comma:%d\n", position);
	char *ptr;
	char *ptr2;
	int number = 0;
	int number2 = 0;

	ptr = &input[0];
	ptr2 = &input[2];
	number = atoi(ptr);
	number2 = atoi(ptr2);
	printf("%d\n", number);
	printf("%d\n", number2);

	if(number <= 0)
	{
		printf("This is not valid.");

	}

}