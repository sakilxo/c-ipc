#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 256

int main(void){
    int client_fd;

    struct sockaddr_in server_address;

    char buffer[BUFFER_SIZE];


    client_fd = socket(     // create tcp socket
        AF_INET,
        SOCK_STREAM,
        0
    );

    if(client_fd == -1){
        perror("socket");
        return 1;
    }


    memset(&server_address, 0, sizeof(server_address));     // config server address

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);


    if(inet_pton(       // convert ip address
        AF_INET,
        SERVER_IP,
        &server_address.sin_addr
    ) <= 0) {
        perror("inet_pton");
        close(client_fd);
        return 1;
    }


    if(connect(     // connect to server
        client_fd,
        (struct sockaddr *)&server_address,
        sizeof(server_address)
    ) == -1) {
        perror("connect");
        close(client_fd);
        return 1;
    }

    printf("connected to TCP server\n");


    const char *message = "hello from TCP client";      // send message

    write(
        client_fd,
        message,
        strlen(message) + 1
    );


    ssize_t bytes_read = read (     // receive message
        client_fd,
        buffer,
        sizeof(buffer) - 1
    );

    if (bytes_read > 0 ) {
        buffer[bytes_read] = '\0';

        printf("server: %s\n", buffer);
    }

    close(client_fd);

    return 0;
}