// writer.c ----------> /tmp/c_ipc_fifo ----------> reader.c
//            write()                     read()

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_PATH "/tmp/c_ipc_fifo"
#define BUFFER_SIZE 256

int main (void) {
    char message[BUFFER_SIZE];

    printf("reader: waiting for writer. \n");

    int fd = open(FIFO_PATH, O_RDONLY);

    if (fd == -1 ){
        perror("open");
        return 1;
    }
    printf("reader: connected \n\n");

    while(1) {
        ssize_t bytes_read = read(
            fd,
            message,
            sizeof(message)
        );

        if (bytes_read == 0) {
            printf("writer disconnected \n");
            break;
        }

        if (bytes_read == -1) {
            perror("read");
            break;
        }

        printf("received: %s\n" , message);

        if (strcmp(message, "exit") == 0)
            break;
    }

    close(fd);

    return 0;

}