#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ssize_t getline(char **lineptr, size_t *n, FILE *stream) {
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    if (lineptr == NULL) {
        return -1;
    }
    if (stream == NULL) {
        return -1;
    }
    if (n == NULL) {
        return -1;
    }
    bufptr = *lineptr;
    size = *n;

    c = fgetc(stream);
    if (c == EOF) {
        return -1;
    }
    if (bufptr == NULL) {
        bufptr = malloc(128);
        if (bufptr == NULL) {
            return -1;
        }
        size = 128;
    }
    p = bufptr;
    while(c != EOF) {
        if ((p - bufptr) > (size - 1)) {
            size = size + 128;
            bufptr = realloc(bufptr, size);
            if (bufptr == NULL) {
                return -1;
            }
        }
        *p++ = c;
        if (c == '\n') {
            break;
        }
        c = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}



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
