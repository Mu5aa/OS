#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    int status;
    char *args[] = {"ls", "-l", NULL};
    pid = fork();
    if (pid < 0) {
        perror("Error");
        return 1;
    } else if (pid == 0) {
        // child process
        printf("Child process running...\n");
        execvp(args[0], args);
        perror("Error");
        exit(1);
    } else {
        // parent process
        printf("Parent process waiting...\n");
        wait(&status);
        if (WIFEXITED(status)) {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child process terminated by signal %d\n", WTERMSIG(status));
        } else if (WIFSTOPPED(status)) {
            printf("Child process stopped by signal %d\n", WSTOPSIG(status));
        }
    }
    return 0;
}
/*This program forks a child process and runs the ls -l command using execvp(). The parent process then waits for the child process to complete 
using wait(). If the child process exits normally, the parent process prints the exit status. If the child process is terminated by a signal, 
the parent process prints the signal number. If the child process is stopped by a signal, the parent process prints the signal number.*/
