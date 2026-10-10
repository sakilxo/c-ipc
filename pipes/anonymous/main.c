// demonstrates parent <-> child communication using two pipes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h> 

#define BUFFER_SIZE 256

int main(void) {
    int parent_to_child[2];
    int child_to_parent[2];

    if (pipe(parent_to_child) == -1) {
        perror("pipe");
        return 1;
    }

    if (pipe(child_to_parent) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    }
    
    if (pid == 0) {     // child
        close(parent_to_child[1]);
        close(child_to_parent[0]);

        char message[BUFFER_SIZE];

        read(parent_to_child[0], message, sizeof(message));

        printf("child received: %s\n", message);

        const char *response = "hello from child";

        write(
            child_to_parent[1],
            response,
            strlen(response) +1
        );

        close(parent_to_child[0]);
        close(child_to_parent[1]);

        exit(0);

    } else {        // parent
        close(parent_to_child[0]);
        close(child_to_parent[1]);

        const char *message = "hello from parent";

        write(
            parent_to_child[1],
            message,
            strlen(message) +1
        );

        char response[BUFFER_SIZE];

        read(
            child_to_parent[0],
            response,
            sizeof(response)
        );

        printf("parent received: %s\n" , response);

        close(parent_to_child[1]);
        close(child_to_parent[0]);

        wait(NULL);

    }

    return 0;
}
