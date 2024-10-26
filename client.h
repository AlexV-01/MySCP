#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

typedef struct client_info {
    int client_socket;
    struct sockaddr_in address;
    char* buffer;
} client_info;

/* Creates a client socket with a given buffer size, and listens for connection.
Returns `client_info` struct pointer or NULL on failure. */
client_info* establish_connection(int port, char* server_hostname, int buff_size);

/* Cleanup for client. */
void destroy_client(client_info* si);

/* Receives data from server. Returns data. */
char* receive_data(client_info* ci, int buff_size);

/* Receives the file. Returns 0 on success and 1 on failure. */
int receive_file(int fd, int port, char* server_hostname, int buff_size);

#endif