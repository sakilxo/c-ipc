// client <-------------------> server
//            send()/recv()

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/c_ipc_socket"
#define BUFFER_SIZE 256

int main(void) {
    int server_fd;
    int client_fd;

    struct sockaddr_un address;

    char buffer[BUFFER_SIZE];


    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);    // create socket

    if (server_fd == -1) {
        perror("socket");
        return 1;
    }


    unlink(SOCKET_PATH);   // remove old socket file

    memset(&address, 0, sizeof(address));

    address.sun_family = AF_UNIX;

    strncpy(
        address.sun_path,
        SOCKET_PATH,
        sizeof(address.sun_path) -1
    );


    if (bind(           // bind socket to filesys path
        server_fd,
        (struct sockaddr *)&address,
        sizeof(address)
    ) == -1) {
        perror("bind");
        close(server_fd);
        return 1;
    }


    if (listen(server_fd, 5) == -1) {   // listen for clients
        perror("listen");
        close(server_fd);
        unlink(SOCKET_PATH);
        return 1;
    }

    printf("server: waiting for client. \n");


    client_fd = accept(     // accept connection
        server_fd,
        NULL,
        NULL
    );

    if (client_fd == -1) {
        perror("accept");
        close(server_fd);
        unlink(SOCKET_PATH);
        return 1;
    }

    printf("server: client connected. \n");


    ssize_t bytes_read = read(      // receive a message
        client_fd,
        buffer,
        sizeof(buffer) -1
    );

    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';

        printf("client: %s\n", buffer);
    }


    const char *response = "hello from server";     // send response

    write(
        client_fd,
        response,
        strlen(response) +1
    );

    close(client_fd);
    close(server_fd);

    unlink(SOCKET_PATH);

    return 0;

}