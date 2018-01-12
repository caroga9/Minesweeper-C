#include <stdio.h>
#include <setjmp.h>

#define TRY do{ jmp_buf ex_buf__; if( !setjmp(ex_buf__) ){
#define CATCH } else {
#define ETRY } }while(0)
#define THROW longjmp(ex_buf__, 1)

int
main(int argc, char** argv)
{
   TRY
   {    
        int tile_row, tile_column;
        printf("Which tile do you want to reveal?\n");
        scanf("%d %d", &tile_row, &tile_column);
        printf("In Try Statement\n");

        printf("I do not appear\n");
   }
   CATCH
   {
      printf("Got Exception!\n");
   }
   ETRY;

   return 0;
}