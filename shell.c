#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <sys/statvfs.h>
#include <sys/wait.h>

#define RED "\033[0;31m"                               //colors defined
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define RESET "\033[0m"

#define args 10
#define BUFFER_SIZE 100

int main(){
    char input[BUFFER_SIZE];                           //finput
    char *arguments[args];
    char *FirstCommand[args];
    char *SecondCommand[args];
    char hostname[BUFFER_SIZE];               //hostname storing
    char *login = getlogin();                                //gettin the login username
    gethostname(hostname, BUFFER_SIZE); //getting the hostname

    while (1){
    printf(BLUE"%s@%s\033[0m"GREEN":~$ \033[0m", hostname, login);
    fgets(input, BUFFER_SIZE, stdin);
    input[strlen(input) - 1] = '\0';

    if(strcmp(input, "") == 0) {
      continue;
    }

    //tokens
    char *token = strtok(input, " ");
    int i = 0;
    while(token != NULL && i < args) {
      arguments[i] = token;
      token = strtok(NULL, " ");
      i++;
    }
    arguments[i]=NULL; //last element always has to be null for execvp()

    int a = 0;
    int confrim1= 0;
    while(arguments[a] != NULL) {
      if(strcmp(arguments[a], "|") == 0) {      //This line will set confrim1 if we have the | line
        confrim1= 1;
        break;
      }
      a++;
    }

    if(confrim1) {  //if confirm1 is 1 we will have pipng
    
      int b = 0;                               
      int c = 0;
      while(strcmp(arguments[b], "|")) {
        FirstCommand[c] = arguments[b];
        b++;
        c++;
      }

      int d = 0;
      int e = 0;
      int confirm2= 0;
      while(arguments[d] != NULL) {
        if(strcmp(arguments[d], "|") == 0) {           //same as cofirm1
          confirm2 = 1;
        } else if(confirm2) {
          SecondCommand[e] = arguments[d];           //this is storing arguments after |
          e++;
        }
        d++;
      }
        FirstCommand[c] = NULL;                      //last element has to be null because of execvp()
        SecondCommand[e] = NULL;
    }
    if(strcmp(arguments[0], "exit") == 0) {
        printf(YELLOW"Dovidjenja prijatno\033[0m\n");
        break;
    }
    else if(strcmp(arguments[0], "name") == 0) {
        printf("Shell Name: "GREEN"Šelić \033[0m\n");
        continue;
    }
    else if(strcmp(arguments[0], "cowsay")==0){
      printf(" %s\n", arguments[1]);
      printf ("_______________\n");
      printf("----------------\n");
      printf ("       \\      ^__^\n");
      printf("         \\     (oo)\\_______\n");
      printf("               (__)\\        )\\/\\\n");
      printf("                   ||-----w  |\n");
      printf("                   ||       ||\n");
    }else if(strcmp(arguments[0], "cd") == 0) {
        if(arguments[1] != NULL) {
            if(chdir(arguments[1]) == -1) {
                perror("cd");
            }
        }
        else {
            chdir(getenv("HOME"));
        }
        continue;
    }
    else if(strcmp(arguments[0], "rm") == 0) {
        if(arguments[1] == NULL) {
            fprintf(stderr, "Usage: rm FILE\n");
            continue;
        }
        if(unlink(arguments[1]) == -1) {
            perror("rm");
        }
        continue;
    }


    else if(confrim1) {
        int pipefd[2];
        pid_t pid1, pid2;          //pid_t is used for storing process id

    pipe(pipefd);           //array pipefd is used for piping, file decriptors for reading and writing will be stored here

    pid1 = fork();

    
    if (pid1 == 0) {           //this is child one
          
        close(pipefd[0]);       //close reading end of pipe

        dup2(pipefd[1], STDOUT_FILENO);        //child process writing into writing end of pipe, instead of standard output

        execvp(FirstCommand[0], FirstCommand);      //execute the first command/program
      }
      else {                                        // parent process, to make child two
        pid2 = fork();

        if (pid2 == 0) {                            //chid process 2
        
        close(pipefd[1]);

        dup2(pipefd[0], STDIN_FILENO);        //child process reading from reading end of pipe, instead od standard input

        execvp(SecondCommand[0], SecondCommand);   //execute the second command/program

        }
        else {                                    // parent process
            close(pipefd[0]);                    //Close both ends of the pipe
            close(pipefd[1]);

            waitpid(pid1, NULL, 0);               // Wait for both child processes to finish
            waitpid(pid2, NULL, 0);
          }
      }
    }
    else{                                    //This is the case if we don't have piping
        pid_t pid = fork();
        if (pid==0){                   //child process
            execvp(arguments[0], arguments);
            perror("Command not found\n");
            exit(1);
        }
        else if (pid>0){
            waitpid(pid, NULL, 0);
        }
    }
}
}
