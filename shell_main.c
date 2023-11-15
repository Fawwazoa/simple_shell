#include "simple_shell.h"

/**
 * main - Entry point for the simple shell.
 *
 * Return: 0 on success.
 */


int main() {
    char input[100];
    char *args[10];  /*Assume a maximum of 10 arguments*/
    char *token;
    int i;
    pid_t pid;

    while (1) {
        printf("simple_shell$ ");
        fgets(input, sizeof(input), stdin);

        /* Tokenize the input*/
        token = strtok(input, " \n");
        i = 0;

        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " \n");
        }

        args[i] = NULL;  /* Null-terminate the argument list*/
        /* Fork and execute the command*/
        pid = fork();

        if (pid == 0) {
            /* Child process*/
            execvp(args[0], args);
            perror("simple_shell");
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            /* Parent process*/
            wait(NULL);  /* Wait for the child to complete*/
        } else {
            perror("simple_shell");
        }
    }

    return 0;
}

