#include "simple_shell.h"

void write_str(const char *str) {
    write(STDOUT_FILENO, str, strlen(str));
}

void write_err(const char *str) {
    write(STDERR_FILENO, str, strlen(str));
}

int my_strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

int is_delimiter(char c) {
    /*Define your delimiter characters, e.g., space and newline*/
    return (c == ' ' || c == '\n');
}

void tokenize(char *input, char *tokens[MAX_TOKENS]) {
    int i = 0;
    int token_start = 0;
    int in_token = 0;

    while (input[i] != '\0') {
        if (is_delimiter(input[i])) {
            if (in_token) {
                input[i] = '\0';  /*Null-terminate the token*/
                tokens[token_start] = &input[token_start];
                in_token = 0;
            }
        } else {
            if (!in_token) {
                token_start = i;
                in_token = 1;
            }
        }

        i++;
    }

    /*Null-terminate the last token if needed*/
    if (in_token) {
        tokens[token_start] = &input[token_start];
    }

    tokens[i] = NULL;  /*Null-terminate the token array*/
}
