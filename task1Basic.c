#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];
    char *args[BUFFER_SIZE / 2 + 1];
    int status;

    while (1) {
        printf("prompt$ ");
        fflush(stdout);

        // Read input from user
        if (!fgets(buffer, BUFFER_SIZE, stdin)) {
            break;
        }

        // Tokenize input
        int i = 0;
        args[i] = strtok(buffer, " \n");
        while (args[i] != NULL && i < BUFFER_SIZE / 2) {
            i++;
            args[i] = strtok(NULL, " \n");
        }
        args[i] = NULL;

        if (args[0] == NULL) {
            // Empty input, do nothing
            continue;
        }

        if (strcmp(args[0], "exit") == 0) {
            // Exit shell
            break;
        }

        if (strcmp(args[0], "cd") == 0) {
            // Change directory
            if (args[1] == NULL) {
                fprintf(stderr, "cd: expected argument\n");
            } else if (chdir(args[1]) != 0) {
                fprintf(stderr, "cd: %s: %s\n", args[1], strerror(errno));
            }
            continue;
        }

        // Execute command
        pid_t pid = fork();
        if (pid == -1) {
            fprintf(stderr, "fork: %s\n", strerror(errno));
        } else if (pid == 0) {
            // Child process
            execvp(args[0], args);
            fprintf(stderr, "%s: %s\n", args[0], strerror(errno));
            exit(1);
        } else {
            // Parent process
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}
