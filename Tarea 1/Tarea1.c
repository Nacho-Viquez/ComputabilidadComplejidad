#include <stdio.h>
#include <stdlib.h>

int leerArchivo(){
   char ch, file_name[25];
   FILE *fp;

   fp = fopen("numbers.txt", "r"); // read mode

   if (fp == NULL)
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }

   printf("The contents of numbers file are:\n");

   while((ch = fgetc(fp)) != EOF)
      printf("%c", ch);

   fclose(fp);
   return 0;
}

int main(int argc, char const *argv[])
{
	leerArchivo();
	return 0;
}