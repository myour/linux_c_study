#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <conio.h>


int main(void)
{
   char str[] = "I like china contry";
   char* p ;

   p = strtok(str," ");

   while(p != NULL)
   {

	printf("%s\n",p);
	p = strtok(NULL," ");
   }

   getchar();

   return 0;

}




