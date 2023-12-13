#include "shell.h"
#include "string.h"

/**
 * main - main body of the shell
 * Return: 0
 */

int main(void) {
    char buffer[BUFFER_SIZE];
    ssize_t read_bytes;
    pid_t child_pid;
    char *args[64];
    int arg_count;
    char *token;

    while (1) {
        write(STDOUT_FILENO, "$ ", 2);

        read_bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE);
        if (read_bytes <= 0) {
            write(STDOUT_FILENO, "\n", 1);
            break;
        }
        args[0] = buffer;
        buffer[read_bytes - 1] = '\0';
        arg_count = 0;
        token = strtok(buffer, " ");

        args[arg_count++] = token;
        while ((token = strtok(NULL, " ")) != NULL) {
            args[arg_count++] = token;
        }
        args[arg_count] = NULL;

        child_pid = fork();

        if (child_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (child_pid == 0) {
            if (access(args[0], X_OK) == 0) {
                execve(args[0], args, NULL);
                exit(EXIT_FAILURE);
            } else {
                exit(EXIT_FAILURE);
            }
        } else {
            wait(NULL);
        }
    }

    return (0);
}

