#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 256

int main(void) {
    int server_fd;
    int client_fd;

    struct sockaddr_in address;

    char buffer[BUFFER_SIZE];


    server_fd = socket(     // create tcp socket
        AF_INET,
        SOCK_STREAM,
        0
    );

    if (server_fd == -1) {
        perror("socket");
        return 1;
    }


    memset(&address, 0, sizeof(address));      // config server address

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);


    if (bind(           // bind socket to port
        server_fd,
        (struct sockaddr *)&address,
        sizeof(address)
    ) == -1) {
        perror("bind");
        close(server_fd);
        return 1;
    }


    if(listen(server_fd, 5) == -1) {        // listen for connections
        perror("listen");
        close(server_fd);
        return 1;
    }

    printf("TCP server listening on port %d", PORT);


    client_fd = accept(     // accept client
        server_fd,
        NULL,
        NULL
    );
    
    if(client_fd == -1) {
        perror("accept");
        close(server_fd);
        return 1;
    }

    printf("client connected. \n");


    ssize_t bytes_read = read(      // receive data
        client_fd,
        buffer,
        sizeof(buffer) -1
    );

    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        printf("client: %s\n", buffer);
    }


    const char *response = "hello from TCP server";     // send response

    write(
        client_fd,
        response,
        strlen(response) + 1
    );

    close(client_fd);
    close(server_fd);

    return 0;
}