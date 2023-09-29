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
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    // If files are provided, read from them.
    char *buffer = NULL;
    size_t bufferLength = 0; // keep track of the total length of buffer.
    for (int i = 1; i < argc; i++) {
        FILE *fptr = fopen(argv[i], "r");
        if (fptr == NULL) {
            printf("wzip: cannot open file\n");
            exit(1);
        }
        //add each char into the buffer
        int readCharacter;
        while ((readCharacter = fgetc(fptr)) != EOF) {
            buffer = realloc(buffer, bufferLength + 1); // add one byte for the new character
            buffer[bufferLength] = (char)readCharacter; // append the character to buffer.
            bufferLength++;
        }
        fclose(fptr);
    }
    
    if (buffer != NULL) {
        buffer[bufferLength] = '\0'; // null-terminate the buffer.
    }
    //process buffer
    int k = 1; //counter for repeating characters
    //loop over each char in the line
    for (int m = 0; m < bufferLength; ++m) {
        if (buffer[m] == buffer[m + 1]) {
            k++;
        }
        else{
            //write counter to stdout as binary
            fwrite(&k, sizeof(int), 1, stdout);
            //write char stdout
            fprintf(stdout, "%c",buffer[m]);
            k = 1; //reset counter
        }

    }
    if (buffer != NULL) {
        free(buffer); // don't forget to free the buffer when done.
    }
    return 0;
}
