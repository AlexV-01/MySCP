#include "client.h"

client_info* establish_connection(int port, int buff_size) {
    int status, client_fd, new_socket;
    struct sockaddr_in serv_address;
    int opt = 1;
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("unable to create client socket");
        exit(EXIT_FAILURE);
    }

    serv_address.sin_family = AF_INET;
    serv_address.sin_port = htons(port);

    if (bind(client_fd, (struct sockaddr*) &serv_address, sizeof(serv_address)) < 0) {
        perror("unable to bind socket to address and port");
        exit(EXIT_FAILURE);
    }


    if ((status = connect(client_fd, (struct sockaddr*) &serv_address, sizeof(serv_address))) < 0) {
        perror("unable to connect to server");
        exit(EXIT_FAILURE);
    }

    client_info* ci = (client_info*) malloc(sizeof(client_info));
    ci->client_socket = new_socket;
    ci->address = serv_address;
    ci->buffer = (char*) malloc(buff_size);
    if (ci->buffer == NULL) {
        perror("unable to allocate memory for buffer");
        exit(EXIT_FAILURE);
    }
    return ci;
}

void destroy_client(client_info* ci) {
    close(ci->client_socket);
    free(ci->buffer);
    free(ci);
}

char* receive_data(client_info* ci, int buff_size) {
    ssize_t bytes_read = read(ci->client_socket, ci->buffer, buff_size - 1);
    if (bytes_read == -1) return NULL;
    return ci->buffer;
}