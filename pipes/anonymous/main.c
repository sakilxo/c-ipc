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
}