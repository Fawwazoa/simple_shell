#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H


#define MAX_TOKENS 10



#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>
#include <stdbool.h>




/* Function prototypes */
void write_str(const char *str);
void write_err(const char *str);
int my_strcmp(const char *s1, const char *s2);
ssize_t _getline(char **lineptr, size_t *n);
int is_delimiter(char c);
void tokenize(char *input, char *tokens[MAX_TOKENS]);
char *get_command_path(const char *command);
int exec_command(char *args[]);

#endif /* SIMPLE_SHELL_H */
