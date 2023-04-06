#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    bool force = false;
    bool recursive = false;
    bool verbose = false;
    int opt;
    int status;
    while ((opt = getopt(argc, argv, "frv")) != -1) {
        switch (opt) {
            case 'f':
                force = true;
                break;
            case 'r':
                recursive = true;
                break;
            case 'v':
                verbose = true;
                break;
            default:
                printf("Usage: rm [-f] [-r] [-v] [file]\n");
                exit(EXIT_FAILURE);
        }
    }
    if (optind >= argc) {
        printf("Usage: rm [-f] [-r] [-v] [file]\n");
        exit(EXIT_FAILURE);
    }
    if (force) {
        status = unlink(argv[optind]);
    } else if (recursive) {
        status = rmdir(argv[optind]);
    } else {
        printf("Are you sure you want to delete %s? (y/n): ", argv[optind]);
        char c = getchar();
        if (c == 'y' || c == 'Y') {
            status = unlink(argv[optind]);
        } else {
            printf("Deletion canceled.\n");
            exit(EXIT_SUCCESS);
        }
    }
    if (status != 0) {
        perror("Error deleting file");
        exit(EXIT_FAILURE);
    }
    if (verbose) {
        printf("%s deleted successfully.\n", argv[optind]);
    }
    exit(EXIT_SUCCESS);
}


/*rm:
-f: Force deletion of file without prompting for confirmation
-r: Recursively delete a directory and all its contents
-v: Verbosely display the name of each file as it is deleted*/

