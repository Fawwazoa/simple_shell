#include "simple_shell.h"

/**
 * get_command_path - Get the full path of a command.
 * @command: The command to find in PATH.
 *
 * Return: The full path of the command, or NULL if not found.
 */
char *get_command_path(const char *command) {
    char *path_env = getenv("PATH");
    char *token, *path, *full_path;

    if (path_env == NULL || command == NULL)
        return NULL;

    token = strtok(path_env, ":");
    while (token != NULL) {
        path = token;
        token = strtok(NULL, ":");

        /* Build the full path */
        full_path = malloc(strlen(path) + strlen(command) + 2);  /* for and null terminator*/
        if (full_path == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        strcpy(full_path, path);
        strcat(full_path, "/");
        strcat(full_path, command);

        /* Check if the command exists */
        if (access(full_path, F_OK) == 0) {
            return full_path;
        }

        free(full_path);  /* Free the allocated memory for full_path*/
    }

    return NULL;  /* Command not found in PATH*/
}

