#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {
    char cow[100][100], message[100], option[10], custom_cow[100];
    int i, j, len, width = 40, height = 5, random = 0;
    char eye = 'o', sound[20] = "", font[20] = "";
    if (argc < 2) {
        printf("Usage: cowsay [options] message\n");
        exit(EXIT_FAILURE);
    }
    for (i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "-w") == 0 && i+1 < argc) {
                width = atoi(argv[i+1]);
                i++;
            } else if (strcmp(argv[i], "-h") == 0 && i+1 < argc) {
                height = atoi(argv[i+1]);
                i++;
            } else if (strcmp(argv[i], "-r") == 0) {
                // Select random cow
                srand(time(NULL));
                random = 1;
            } else if (strcmp(argv[i], "-p") == 0 && i+1 < argc) {
                // Use custom cow
                strcpy(custom_cow, argv[i+1]);
                i++;
            } else if (strcmp(argv[i], "-s") == 0) {
                // Add sound effect
                strcpy(sound, "moo");
            } else if (strcmp(argv[i], "-f") == 0 && i+1 < argc) {
                // Use custom font
                strcpy(font, argv[i+1]);
                i++;
            } else {
                printf("Invalid option: %s\n", argv[i]);
                exit(EXIT_FAILURE);
            }
        } else {
            // Copy message into a separate variable
            strcpy(message, argv[i]);
            for (j = i+1; j < argc; j++) {
                strcat(message, " ");
                strcat(message, argv[j]);
            }
            break;
        }
    }
    // Determine length of message
    len = strlen(message);
    // Build cow
    if (random) {
        // Select random cow
        int num_cows = 3;
        int rand_cow = rand() % num_cows;
        switch (rand_cow) {
            case 0:
                strcpy(cow[0], "        \\   ^__^");
                strcpy(cow[1], "         \\  (eye)\\_______");
                strcpy(cow[2], "            (__)\\       )\\/\\");
                strcpy(cow[3], "                ||----w |");
                strcpy(cow[4], "                ||     ||");
                break;
            case 1:
                strcpy(cow[0], "  ^__^");
               
            strcpy(cow[1], " (oo)\\_______");
            strcpy(cow[2], " (__)\       )\/\\");
            strcpy(cow[3], "     ||----w |");
            strcpy(cow[4], "     ||     ||");
            break;
        case 2:
            strcpy(cow[0], "  ^__^");
            strcpy(cow[1], " /    \\");
            strcpy(cow[2], "|      |");
            strcpy(cow[3], "|      |");
            strcpy(cow[4], " \\____/");
            break;
    }
} else if (strlen(custom_cow) > 0) {
    // Use custom cow
    FILE *f = fopen(custom_cow, "r");
    if (f == NULL) {
        printf("Error: unable to open custom cow file '%s'\n", custom_cow);
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < 5; i++) {
        if (fgets(cow[i], 100, f) == NULL) {
            printf("Error: custom cow file '%s' does not contain enough lines\n", custom_cow);
            exit(EXIT_FAILURE);
        }
        // Remove newline character at end of each line
        cow[i][strlen(cow[i])-1] = '\0';
    }
    fclose(f);
} else {
    // Use default cow
    strcpy(cow[0], "        \\   ^__^");
    strcpy(cow[1], "         \\  (eye)\\_______");
    strcpy(cow[2], "            (__)\\       )\\/\\");
    strcpy(cow[3], "                ||----w |");
    strcpy(cow[4], "                ||     ||");
}
// Add sound effect if specified
if (strcmp(sound, "moo") == 0) {
    strcat(message, " (");
    for (i = 0; i < 3; i++) {
        strcat(message, sound);
        if (i < 2) {
            strcat(message, " ");
        }
    }
    strcat(message, ")");
}
// Add font styling if specified
if (strcmp(font, "bold") == 0) {
    printf("\033[1m");
} else if (strcmp(font, "italic") == 0) {
    printf("\033[3m");
}
// Print cow's message bubble
printf(" ");
for (i = 0; i < len+2; i++) {
    printf("_");
}
printf("\n");
printf("< %s >\n", message);
printf(" ");
for (i = 0; i < len+2; i++) {
    printf("-");
}
printf("\n");
// Print cow
for (i = 0; i < height; i++) {
    printf("%s", cow[i]);
    for (j = strlen(cow[i]); j < width; j++) {
        printf(" ");
    }
    printf("|");
    if (i == 0) {
        printf(" ");
        for (j = 0; j < len; j++) {
            printf("_");
        }
        printf(" ");
    } else if (i == height-1) {
        printf(" ");
        for (j = 0; j < len; j++) {
            printf("-");
        }
        printf(" ");
    } else if (i == height/2) {
        printf("< ");
        printf("%s", message);
        printf(" >");
    }
    printf("\n");
}

  /*cowsay
-w <width>: specify the width of the cow's message bubble.
-h <height>: specify the height of the cow's message bubble.
-r: randomly select a cow from a list of available cows.
-p: use a custom cow specified by the user.
-s: add a sound effect to the cow's message (e.g. mooing, baaing).
-f <font>: use a custom font for the cow's message (e.g. bold, italic).
*/
