#include "client.h"

client_info* establish_connection(int port, char* server_hostname, int buff_size) {
    int status, client_fd;
    struct sockaddr_in serv_address;
    struct hostent* h;
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("unable to create client socket");
        exit(EXIT_FAILURE);
    }

    if ((h = gethostbyname(server_hostname)) == NULL) {
        fprintf(stderr, "invalid hostname\n");
        exit(EXIT_FAILURE);
    }

    serv_address.sin_family = AF_INET;
    memcpy((char *) &serv_address.sin_addr.s_addr, h->h_addr_list[0], h->h_length); 
    serv_address.sin_port = htons(port);

    if ((status = connect(client_fd, (struct sockaddr*) &serv_address, sizeof(serv_address))) < 0) {
        perror("unable to connect to server");
        exit(EXIT_FAILURE);
    }

    client_info* ci = (client_info*) malloc(sizeof(client_info));
    ci->client_socket = client_fd;
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

int receive_file(int fd, int port, char* server_hostname, int buff_size) {
    // Setup client socket
    client_info* client = establish_connection(port, server_hostname, buff_size);

    // Receive data from server
    while (1) {
        receive_data(client, buff_size);
        ssize_t bytes_written = write(fd, client->buffer, buff_size);
        if (bytes_written == 0) break;
    }

    // Cleanup client
    destroy_client(client);

    return EXIT_SUCCESS;
}