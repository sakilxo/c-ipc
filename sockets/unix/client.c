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


int main(void){
    int client_fd;

    struct sockaddr_un address;

    char buffer[BUFFER_SIZE];


    client_fd = socket(     // create socket
        AF_UNIX,
        SOCK_STREAM,
        0
    );

    if(client_fd == -1){
        perror("socket");
        return 1;
    }

    memset(&address, 0, sizeof(address));

    address.sun_family = AF_UNIX;

    strncpy(
        address.sun_path,
        SOCKET_PATH,
        sizeof(address.sun_path) -1
    );


    if(connect(     // connect to server
        client_fd,
        (struct sockaddr*) &address,
        sizeof(address)
    ) == -1) {
        perror("connect");
        close(client_fd);
        return 1;
    }

    printf("client: connected to server.");


    const char *message = "hello from client.";     // send message

    write(
        client_fd,
        message,
        strlen(message) +1
    );


    ssize_t bytes_read = read(      // receive response
        client_fd,
        buffer,
        sizeof(buffer) -1
    );

    if(bytes_read > 0){
        buffer[bytes_read] = '\0';

        printf("server: %s\n", buffer);
    }

    close(client_fd);
    return 0;

}
