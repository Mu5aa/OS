#include <unistd.h>

int main() {
    while(1) {
        fork();
    }
    return 0;
}



/*A forkbomb is a type of denial-of-service attack that can be executed through a command in a shell. The forkbomb command is a short program that
repeatedly spawns new processes, each of which in turn spawns new processes, until the system becomes unresponsive and crashes or needs to be restarted.
The basic idea behind a forkbomb is to use the fork() system call in a loop to create new child processes. The child processes then repeat the loop,
spawning more child processes, and so on, until a large number of processes have been created, consuming all available system resources such as memory,
CPU, and process table entries. This results in a system crash or freeze.*/
