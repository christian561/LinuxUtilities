#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }

    // If files are provided, read from them.
    for (int i = 1; i < argc; i++) {
        FILE *fptr2 = fopen(argv[i], "rb");
        int readnumber;
        int readchar;
        while (1) {
            // Read an integer
            size_t readInt = fread(&readnumber, sizeof(int), 1, fptr2);
            if (readInt != 1) {
                if (feof(fptr2))
                    break; // End of file reached
                perror("Failed to read an integer from the file!");
                fclose(fptr2);
                return 1;
            }
            
            // Read a character
            size_t readChar = fread(&readchar, sizeof(char), 1, fptr2);
            if (readChar != 1) {
                perror("Failed to read a character from the file!");
                fclose(fptr2);
                return 1;
            }
            // Print the read integer and character
            for(int i = 0; i < readnumber; i++){
                printf("%c", readchar);
            }
        }

        fclose(fptr2);
    }
    return 0;
}
