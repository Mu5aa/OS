#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

#define RESET   "\x1B[0m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define WHITE   "\x1B[37m"

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
    
    //Storing user input
      char input[MAX_COMMAND_LENGTH];
      char *arguments[MAX_NUM_ARGUMENTS];
      char *commands1[MAX_NUM_ARGUMENTS];
      char *commands2[MAX_NUM_ARGUMENTS];
    
    while (1) {
        printf(RED"%s@%s\033[0m"BOLDGREEN":~$ \033[0m", hostName, login);
        fgets(input, MAX_COMMAND_LENGTH, stdin);
        input[strlen(input) - 1] = '\0';  // Remove newline character

        if(strcmp(input, "") == 0) {
          continue;
        }
        // Tokenize the command string by spaces
        char *token = strtok(input, " ");
        int i = 0;
        while(token != NULL && i < MAX_NUM_ARGUMENTS) {
          arguments[i] = token;
          token = strtok(NULL, " ");
          i++;
        }

        int x = 0;
        int check1 = 0;
        while(arguments[x] != NULL) {
          if(strcmp(arguments[x], "|") == 0) {
            check1 = 1;
            break;
          }
          x++;
        }

        if(check1) {
          int j = 0;
          int n = 0;
          while(strcmp(arguments[j], "|")) {
            commands1[n] = arguments[j];
            n++;
            j++;
          }

          int k = 0;
          int m = 0;
          int check = 0;
          while(arguments[k] != NULL) {
            if(strcmp(arguments[k], "|") == 0) {
              check = 1;
            } else if(check) {
              commands2[m] = arguments[k];
              m++;
            }
            k++;
          }
          commands1[n] = NULL;
          commands2[m] = NULL;
        }

        arguments[i] = NULL;  // Set the last argument to NULL for execvp
        
        
        //RM
        int result;
            if (argc < 2) {
                printf("Usage: rm <file>\n");
                return 1;
            }
            result = unlink(argv[1]);
            if (result == -1) {
                perror("Error");
                return 1;
            }
        
        
        //COWSAY
        
        if (argc < 2) {
                printf("Usage: cowsay <message>\n");
                return 1;
            }
            printf(" %s\n", "         \\   ^__^\n          \\  (oo)\\_______\n             (__)\\       )\\/\\\n                 ||----w |\n                 ||     ||\n");
        printf(" %s\n", argv[1]);
        
        
        
        //Clear
        char commandClear[100];

            while(1) {
                printf("$ ");
                fgets(commandClear, 100, stdin);
                commandClear[strcspn(commandClear, "\n")] = 0;

                if (strcmp(commandClear, "clear") == 0) {
                    system("clear");  // Executes the "clear" command in the shell
                    continue;
                }

                // Handle other commands here
            }
        
        
        
        //CAT
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

    
    
    
    
    
    
    
    
    
    
    
    printf("%sRED, %sGREEN%s\n", RED, GREEN, RESET);
    printf("%sThis text is %syellow%s\n", YELLOW, YELLOW, RESET);
    printf("%sThis text is %sblue%s\n", BLUE, BLUE, RESET);
    printf("%sThis text is %smagenta%s\n", MAGENTA, MAGENTA, RESET);
    printf("%sThis text is %scyan%s\n", CYAN, CYAN, RESET);
    printf("%sThis text is %swhite%s\n", WHITE, WHITE, RESET);
    
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
        printf( '' );
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
