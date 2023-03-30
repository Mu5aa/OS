#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char cowfile[20] = "default";
    char eyes[5] = "oo";
    int i;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0) {
            if (i+1 < argc) {
                strcpy(cowfile, argv[i+1]);
                i++;
            } else {
                printf("Error: no cowfile specified.\n");
                return 1;
            }
        } else if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--eyes") == 0) {
            if (i+1 < argc) {
                strcpy(eyes, argv[i+1]);
                i++;
            } else {
                printf("Error: no eye style specified.\n");
                return 1;
            }
        } else {
            printf("Usage: cowsay [-f cowfile] [-e eye_style] message\n");
            return 1;
        }
    }
    printf("  %s\n", "       \\   ^__^\n        \\  (%s)\\_______\n            (__)\\       )\\/\\\n                ||----w |\n                ||     ||\n", eyes);
    printf("  %s\n", argv[argc-1]);
    printf("  %s\n", "         \\   ^__^\n          \\  (%s)\\_______\n             (__)\\       )\\/\\\n                 ||----w |\n                 ||     ||\n", eyes);
    return 0;
}
