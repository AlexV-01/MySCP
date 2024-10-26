#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

typedef struct client_info {
    int client_socket;
    struct sockaddr_in address;
    char* buffer;
} client_info;

/* Creates a client socket with a given buffer size, and listens for connection.
Returns `client_info` struct pointer or NULL on failure. */
client_info* establish_connection(int port, int buff_size);

/* Receives data from client. Returns data. */
char* receive_data(client_info* ci, int buff_size);

#endif