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

}