#include "shell.h"
#include "string.h"

/**
 * main - main body of the shell
 * Return: 0
 */

int main(void) {
    char buffer[BUFFER_SIZE];
    ssize_t read_bytes;
    char *args[] = {buffer, NULL};

    while (1) {
        // Display the prompt
        write(STDOUT_FILENO, "$ ", 2);

        // Read user input
        read_bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE);
        if (read_bytes <= 0) {
            // End of file condition (Ctrl+D or error)
            write(STDOUT_FILENO, "\n", 1);
            break;
        }

        // Null-terminate the input
        buffer[read_bytes - 1] = '\0';

        // Fork a child process
        pid_t child_pid = fork();

        if (child_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (child_pid == 0) {
            // Child process
            execve(args[0], args, NULL);
            // If execve fails
            perror("execve");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            wait(NULL);
        }
    }

    return 0;
}

