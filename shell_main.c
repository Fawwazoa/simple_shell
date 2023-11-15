#define _POSIX_C_SOURCE 200809L


#include "simple_shell.h"
extern char **environ;


/**
 * main - Entry point for the simple shell.
 * @ac: Number of command line arguments.
 * @av: Array of command line argument strings.
 *
 * Return: 0 on success.
 */

int main(int argc , char **argv) {
    char *input = NULL;
    size_t len = 0;
    ssize_t read;
    pid_t pid;
    char *token;
    int i;
    bool pipe= false;
    int status;
    char **env;


    while (1 && !pipe) {
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

        /* Tokenize the input*/
       token =  strtok(input, " \n");

         i = 0;

        while (token != NULL) {
            argv[i++] = token;
            token = strtok(NULL, " \n");
            
            if (i >= 10) {
                write_err("simple_shell: too many arguments\n");
                break;
        }

        argv[i] = NULL;  /* Null-terminate the argument list*/

        /* Handle built-in commands*/
        if (my_strcmp(argv[0], "exit") == 0) {
            free(input);
	    if (argc == 3)
                exit(atoi(argv[2]));   
	    else 
		    exit(0);

        } else if (my_strcmp(argv[0], "cd") == 0) {
            if (argv[1] != NULL) {
                if (chdir(argv[1]) == -1) {
                    perror("chdir");
                }
                continue;
            } else if (my_strcmp(argv[0],"cd") == -1) {
                write_err("simple_shell: cd: missing argument\n");
            }
            continue;  /* Skip the fork and wait*/
            }

        else if (my_strcmp(argv[0], "env") == 0) {
            /* Implement env built-in */
            env = environ;
            while (*env != NULL) {
                write_str(*env++);
                write_str("\n");
            }
            continue;  /* Skip the fork and wait */
        }
        /* Check if the command exists in PATH */
        if (access(argv[0], F_OK) == -1) {
            write_err("simple_shell: command not found\n");
            continue;  /* Display prompt again without forking */
        }

        pid = fork();

        if (pid == 0) {
            /* Child process*/
            execve(argv[0], argv, NULL);
            perror("Error in execve: ");
            _exit(EXIT_FAILURE);
        } else if (pid > 0) {
            /* Parent process*/
            waitpid(pid, &status, 0);  /* Wait for the child to complete*/
         }

         else {
            perror("fork");
        }
    }
    }
    /* Cleanup */
    free(input);

    return 0;
}

