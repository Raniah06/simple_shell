#include "shell.h"
#include "string.h"

int main(void) {
    char buffer[BUFFER_SIZE];
    ssize_t read_bytes;
    char *args[2];
    pid_t child_pid;

    while (1) {
        write(STDOUT_FILENO, "$ ", 2);

        read_bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE);
        if (read_bytes <= 0) {
            write(STDOUT_FILENO, "\n", 1);
            break;
        }
        buffer[read_bytes - 1] = '\0';

        args[0] = buffer;
        args[1] = NULL;

        child_pid = fork();

        if (child_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (child_pid == 0) {
            execve(args[0], args, NULL);
            perror("execve");
            exit(EXIT_FAILURE);
        } else {
            wait(NULL);
        }
    }

    return 0;
}

