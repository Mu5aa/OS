#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
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
    return 0;
}
