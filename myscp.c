#include "myscp.h"

int main(int argc, char** argv) {
    // Check argument count
    if (argc != 4){
        fprintf(stderr, "usages:\nmyscp -s <source_file> <client_hostname>\nmyscp -c <server_hostname> <destination_path>\n");
        exit(EXIT_FAILURE);
    }

    // Flag indicates client or server mode
    char* mode = argv[1]; 

    if (strcmp(mode, "-s") == 0) {
        int fd = open(argv[2], O_RDONLY);
        char* client_hostname = argv[3];
        // Send the file from server to client
        if (transfer_file(fd, client_hostname, PORT, BUFFER_SIZE) == 1) {
            fprintf(stderr, "unable to transfer file\n");
            exit(EXIT_FAILURE);
        }
        close(fd);
        printf("Transfer complete\n");
    } else if (strcmp(mode, "-c") == 0) {
        char* server_hostname = argv[2];
        int fd = open(argv[3], O_WRONLY | O_APPEND);
        // Receive the file at client from server
        if (receive_file(fd, PORT, server_hostname, (int) BUFFER_SIZE) == 1) {
            fprintf(stderr, "unable to transfer file\n");
            exit(EXIT_FAILURE);
        }
        close(fd);
        printf("Transfer complete\n");
    } else {
        fprintf(stderr, "invalid mode (use either -s or -c)\n");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}