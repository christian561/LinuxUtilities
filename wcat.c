#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  FILE *fptr;

  for(int i = 1; i<argc;i++){
    fptr = fopen(argv[i],"r");
    if (fptr == NULL) {
      printf("wcat: cannot open file\n");
      exit(1);
    }
    
    char myString[200];
    while(fgets(myString, 200, fptr) != NULL){
      printf("%s",myString);
    }

    fclose(fptr);
  }
  return 0;
}
