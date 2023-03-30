#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int ch, line_number = 1;
    FILE *fp;
    if (argc < 2) {
        printf("Usage: cat <file>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Error");
        return 1;
    }
    while ((ch = fgetc(fp)) != EOF) {
        if (line_number == 1) {
            printf("%d ", line_number);
        }
        putchar(ch);
        if (ch == '\n') {
            line_number++;
            if (argv[2] && (strcmp(argv[2], "-n") == 0 || strcmp(argv[2], "--number") == 0)) {
                printf("%d ", line_number);
            }
            if (argv[2] && (strcmp(argv[2], "-E") == 0 || strcmp(argv[2], "--show-ends") == 0)) {
                printf("$");
            }
        }
    }
    fclose(fp);
    return 0;
}
