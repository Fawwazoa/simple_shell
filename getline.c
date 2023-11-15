#include "simple_shell.h"

#define BUFFER_SIZE 1024

ssize_t _getline(char **lineptr, size_t *n) {
    static char buffer[BUFFER_SIZE];
    static size_t buffer_index = 0;
    static size_t bytes_read = 0;
    size_t i ;

    if (*n == 0 || *lineptr == NULL) {
        *n = BUFFER_SIZE;
        *lineptr = (char *)malloc(*n);
        if (*lineptr == NULL) {
            return -1;  /*Memory allocation error*/
        }
    }

    i = 0;

    while (1) {
        if (buffer_index == bytes_read) {
            /* Buffer is empty, read more data*/
            bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
            if (bytes_read <= 0) {
                /* End of file or error*/
                return i == 0 ? bytes_read : i;
            }
            buffer_index = 0;
        }

        (*lineptr)[i++] = buffer[buffer_index++];

        if (buffer[buffer_index - 1] == '\n') {
            /*	End of line*/
            (*lineptr)[i] = '\0';
            return i;
        }

        if (i == *n - 1) {
            /*Resize lineptr if needed*/
            *n *= 2;
            *lineptr = (char *)realloc(*lineptr, *n);
            if (*lineptr == NULL) {
                return -1;  /*Memory allocation error*/
            }
        }
    }
}

