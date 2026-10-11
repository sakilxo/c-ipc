// writer.c ----------> /tmp/c_ipc_fifo ----------> reader.c
//            write()                     read()


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#define FIFO_PATH "/tmp/c_ipc_fifo"
#define BUFFER_SIZE 256


int main(void) {
    char message[BUFFER_SIZE];

    if (mkfifo(FIFO_PATH, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        return 1;
    }

    printf("writer: waiting for reader \n");

    int fd = open(FIFO_PATH, O_WRONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    printf("writer connected \n");
    printf("type 'exit' to quit \n");

    while (1) {
        printf("you: ");
        fflush(stdout);

        if (fgets(message, sizrof(message), stdin) == NULL) {
            break;
        }

        message[strcspn(message, "\n")] = '\0';

        if (strcmp(message, "exit") == 0) {
            break;
        }

        if (write(fd, message, strlen(message) +1) == -1) {
            perror("write");
            break;
        }
    }

    close(fd);

    unlink(FIFO_PATH);

    return 0;
    
}