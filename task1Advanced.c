#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

void execute_command(char **args) {
    pid_t pid = fork();
    if (pid == -1) {
        printf("Error: Unable to fork process.\n");
    } else if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            printf("Error: Invalid command.\n");
        }
        exit(EXIT_FAILURE);
    } else {
        int status;
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

int main() {
    char input_buffer[BUFFER_SIZE];
    char *args[BUFFER_SIZE / 2 + 1];
    
    
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0) {
        
    } else {
        perror("gethostname");
        return 1;
    }
    
    char *username = getlogin();
    if (username != NULL) {
    
    } else {
        perror("getlogin");
        return 1;
    }

    while (1) {
        printf(hostname);
        putchar('@');
        printf(username);
        fflush(stdout);

        // Read input from user
        fgets(input_buffer, BUFFER_SIZE, stdin);

        // Parse input into command and arguments
        int i = 0;
        args[i] = strtok(input_buffer, " \n");
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " \n");
        }
        args[i] = NULL;

        // Execute command
        if (args[0] != NULL) {
            if (strcmp(args[0], "exit") == 0) {
                exit(EXIT_SUCCESS);
            } else if (strcmp(args[0], "cd") == 0) {
                if (args[1] != NULL) {
                    if (chdir(args[1]) != 0) {
                        printf("Error: Unable to change directory.\n");
                    }
                } else {
                    printf("Error: Expected argument to \"cd\".\n");
                }
            } else {
                execute_command(args);
            }
        }
    }

    return EXIT_SUCCESS;
}
