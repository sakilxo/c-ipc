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

    
}