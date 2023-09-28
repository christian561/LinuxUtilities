#include<stdio.h>

int main () {
  char str[] = "8a";

  //fwrite(str , 1 , sizeof(str) , fptr );
  //append int as binary to file
  // FILE *fptr;
  // fptr = fopen( "file" , "ab" );
  // int number = 8;
  // size_t written = fwrite(&number, sizeof(int), 1, fptr);
  // if (written != 1) {
  //     perror("Failed to write the integer to the file!");
  //     fclose(fptr);
  //     return 1;
  // }
  // fclose(fptr);
  // //append char to file
  // fptr = fopen( "file" , "a" );
  // fprintf(fptr, "%c\n",'a');
  // fclose(fptr);

  //write to stdout
  int number = 8;
  fwrite(&number, sizeof(int), 1, stdout);
  //write to stdout
  char character = 'a';
  fprintf(stdout, "%c\n",character);



  // //read as binary
  FILE *fptr2 = fopen("file", "rb");
  int readnumber;
  size_t read = fread(&readnumber, sizeof(int), 1, fptr2);
  printf("The number read in is: %d", readnumber);
  fclose(fptr2);
  return(0);
}