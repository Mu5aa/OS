#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int ch;
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
        putchar(ch);
    }
    fclose(fp);
    return 0;
}
