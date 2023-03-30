#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: cowsay <message>\n");
        return 1;
    }
    printf(" %s\n", "         \\   ^__^\n          \\  (oo)\\_______\n             (__)\\       )\\/\\\n                 ||----w |\n                 ||     ||\n");
    printf(" %s\n", argv[1]);
    return 0;
}
