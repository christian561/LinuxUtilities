#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
