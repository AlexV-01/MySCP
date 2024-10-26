#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

typedef struct server_info {
    int server_socket;
    struct sockaddr_in address;
    char* buffer;
} server_info;

/* Creates a server socket with a given buffer size, and listens for connection.
Returns `server_info` struct pointer or NULL on failure. */
server_info* create_server(int port, int buff_size);

/* Cleanup for server. */
void destroy_server(server_info* si);

/* Sends data to client. */
void send_data(server_info* si);

/* Transfers the file. Returns 0 on success and 1 on failure. */
int transfer_file(int fd, int port, int buff_size);

#endif