#include "server.h"

server_info* create_server(int port, char* client_hostname, int buff_size) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t address_len = sizeof(address);
    int opt = 1;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("unable to create server socket");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("unable to set socket options");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*) &address, sizeof(address)) < 0) {
        perror("unable to bind socket to address and port");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 1) < 0) {
        perror("unable to listen for connection");
        exit(EXIT_FAILURE);
    }
    printf("Listening for connection\n");

    if ((new_socket = accept(server_fd, (struct sockaddr*) &address, &address_len)) < 0) {
        perror("unable to accept connection");
        exit(EXIT_FAILURE);
    }

    char hostname[NI_MAXHOST] = {};
    getnameinfo((struct sockaddr*)&address, address_len, hostname, sizeof(hostname), NULL, 0, 0);
    if (strcmp(hostname, client_hostname) != 0) {
        fprintf(stderr, "bad client, aborting\n");
        exit(EXIT_FAILURE);
    }
    printf("Connection accepted with %s\n", client_hostname);

    server_info* si = (server_info*) malloc(sizeof(server_info));
    si->server_socket = new_socket;
    si->address = address;
    si->buffer = (char*) malloc(buff_size);
    if (si->buffer == NULL) {
        perror("unable to allocate memory for buffer");
        exit(EXIT_FAILURE);
    }
    return si;
}

void destroy_server(server_info* si) {
    close(si->server_socket);
    free(si->buffer);
    free(si);
}

void send_data(server_info* si) {
    send(si->server_socket, si->buffer, strlen(si->buffer), 0);
}

int transfer_file(int fd, char* client_hostname, int port, int buff_size) {
    // Setup server socket
    server_info* server = create_server(port, client_hostname, buff_size);

    // Send data to client
    while (1) {
        ssize_t bytes_read = read(fd, server->buffer, buff_size);
        if (bytes_read == 0) break;
        send_data(server);
    }

    // Cleanup server
    destroy_server(server);

    return EXIT_SUCCESS;
}