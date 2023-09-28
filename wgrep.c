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


void searchInFile(FILE *fptr, const char *searchTerm, size_t searchTermLength) {
    char *buffer = NULL;
    size_t bufsize = 0;
    size_t charactersRead;
    //read each line
    while ((charactersRead = getline(&buffer, &bufsize, fptr)) != -1) {
        int k = 0;
        int f = 0; // flag for found match
        //loop over each char in the line
        for (int m = 0; m < charactersRead; ++m) {
            if (searchTerm[k] == buffer[m]) {
                k++;
            } else if (k == searchTermLength) {
                f = 1;
                break;
            } else
                k = 0;
        }
        if (f == 1)
            printf("%s", buffer);
    }
    if (buffer) {
        free(buffer);
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }
    char *searchTerm = argv[1];
    size_t searchTermLength = strlen(searchTerm);

    if (argc == 2) { // No files provided, read from standard input.
        searchInFile(stdin, searchTerm, searchTermLength);
        return 0;
    }

    // If files are provided, read from them.
    for (int i = 2; i < argc; i++) {
        FILE *fptr = fopen(argv[i], "r");
        if (fptr == NULL) {
            printf("wgrep: cannot open file\n");
            exit(1);
        }
        searchInFile(fptr, searchTerm, searchTermLength);
        fclose(fptr);
    }
    return 0;
}
