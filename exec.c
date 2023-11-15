#include "simple_shell.h"

/**
 * exec_command - Execute the given command.
 * @args: The array of command arguments.
 *
 * Return: On success, returns the exit status of the command.
 *         On failure, returns -1.
 */
int exec_command(char *args[]) {
    pid_t pid;
    int status;

    pid = fork();

    if (pid == -1) {
        perror("fork");
        return -1;
    }

    if (pid == 0) {
        /* Child process */
        if (execve(args[0], args, NULL) == -1) {
            perror("Error in execve");
            _exit(EXIT_FAILURE);
        }
    } else {
        /* Parent process */
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            return -1;
        }

        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        } else {
            return -1;
        }
    }

    return -1;
}

