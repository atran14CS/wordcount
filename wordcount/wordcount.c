// "Copyright 2023 Akira Tran"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 500

// open the FILE fp process each line
// and return the total number of lines.
int countLines(FILE *fp) {
    int lines = 0;
    char line[MAX_LENGTH ];
    while (fgets(line, MAX_LENGTH, fp)) {
        lines++;
    }
    return lines;
}

// opens the FILE fp and keeps track of type of
// character to know if its a word and returns the
// total number of words.
int countWords(FILE *fp) {
    int words = 0;
    int in_word = 0;
    char c;
    while ((c = getc(fp)) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            words++;
        }
    }
    return words;
}

// opens FILE fp and goes through characters
// and return the total number of characters.
int countCharacters(FILE *fp) {
    int characters = 0;
    char c;
    while ((c = getc(fp)) != EOF) {
        characters++;
    }
    return characters;
}

// make sure the number of arguments is greater than 1
// If this is true check the option for file
// From this do the following functions
// report the stats at the end.
int main(int argc, char *argv[]) {
    int lines, words, characters;
    int total_lines = 1;
    int option = -1;
    int index = 1;
    FILE *fp;
    int i;
    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "-l", 2) == 0) {
            option = 0;
            index = i + 1;
            break;
        } else if (strncmp(argv[i], "-w", 2) == 0) {
            option = 1;
            index = i + 1;
            break;
        } else if (strncmp(argv[i], "-c", 2) == 0) {
            option = 2;
            index = i + 1;
            break;
        } else {
            break;
        }
    }
    if (index >= argc) {
        fprintf(stderr, "Usage: ./wordcount requires an input file.\n");
        return 1;
    }
    for (i = index; i < argc; i++) {
        if (strncmp(argv[i], "-l", 2) == 0 || strncmp(argv[i], "-w", 2) == 0 ||
            strncmp(argv[i], "-c", 2) == 0) {
            fprintf(stderr, "Usage: ./wordcount requires an input file.\n");
            return 1;
        }
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            fprintf(stderr, "%s will not open. Skipping..\n",
                    argv[i]);
            continue;
        }
        lines = countLines(fp);
        rewind(fp);
        words = countWords(fp);
        rewind(fp);
        characters = countCharacters(fp);
        switch (option) {
            case 0:
                printf("%d\n", lines);
                break;
            case 1:
                printf("%d\n", words);
                break;
            case 2:
                printf("%d\n", characters);
                break;
            default:
            printf(" %d %d %d %s\n", lines, words, characters, argv[i]);
        }
        total_lines += lines;
        fclose(fp);
    }
    if (argc - i > 1 && option == -1) {
        printf("Total Lines = %d\n", total_lines);
    }
    return 0;
}
