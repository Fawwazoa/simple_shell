#define _POSIX_C_SOURCE 200809L

#include "simple_shell.h"
extern char **environ;

int main(void) {  /* Modified the function signature*/
    char *input = NULL;
    size_t len = 0;
    ssize_t read;
    pid_t pid;
    char *token;
    int i;
    char *args[11];
    bool pipe = false ; 
    int status;
   
    char *command_path;

    while (1) {
   	  if (isatty(STDERR_FILENO) == 0)
            pipe = true;

        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            /* The command was successful */
            write_str(":) ");
        } else {
            /* The command failed */
            write_str(":( ");
        }

        read = _getline(&input, &len);

        if (read == -1) {
            perror("getline");
            exit(EXIT_FAILURE);
        }

        /* Tokenize the input */
        token = strtok(input, " \n");

        i = 0;

        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " \n");

            if (i >= 10) {
                write_err("simple_shell: too many arguments\n");
                break;
            }
        }

        args[i] = NULL;  /* Null-terminate the argument list */

        /* Check if the command exists in PATH */
        command_path = get_command_path(args[0]);
        if (command_path == NULL) {
            write_err("simple_shell: command not found\n");
            free(input);
            continue;  /* Display prompt again without forking */
        }

        pid = fork();

        if (pid == 0) {
            /* Child process */
            execve(command_path, args, environ);
            perror("Error in execve: ");
            _exit(EXIT_FAILURE);
        } else if (pid > 0) {
            /* Parent process */
            waitpid(pid, &status, 0);  /* Wait for the child to complete */
        } else {
            perror("fork");
        }

        free(command_path); /* Free the allocated memory for command_path*/
    }

    /* Cleanup */
    free(input);

    return 0;
}

