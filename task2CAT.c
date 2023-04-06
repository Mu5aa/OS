#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    char c;
    int line_number = 1;
    int show_line_numbers = 0;
    int show_non_blank_numbers = 0;
    int show_non_printable = 0;
    
    // Parse options and arguments
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            // This is an option
            if (strcmp(argv[i], "-n") == 0) {
                show_line_numbers = 1;
            } else if (strcmp(argv[i], "-b") == 0) {
                show_non_blank_numbers = 1;
            } else if (strcmp(argv[i], "-v") == 0) {
                show_non_printable = 1;
            } else {
                printf("Unknown option: %s\n", argv[i]);
                exit(EXIT_FAILURE);
            }
        } else {
            // This is an argument (filename)
            fp = fopen(argv[i], "r");
            if (fp == NULL) {
                perror("Error opening file");
                exit(EXIT_FAILURE);
            }
            while ((c = getc(fp)) != EOF) {
                if (show_non_printable && !isprint(c)) {
                    printf("^%d", (int)c);
                } else {
                    putchar(c);
                }
                if (c == '\n') {
                    line_number++;
                }
            }
            fclose(fp);
        }
    }

    exit(EXIT_SUCCESS);
}


/*cat:
-n: displays line numbers alongside the contents of the file
-b: displays line numbers only for non-blank lines
-v: displays non-printable characters as ^ followed by the character's ASCII code*/
