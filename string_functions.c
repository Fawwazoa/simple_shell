#ifndef SHELL_H
#define SHELL_H


#include <stdio.h>
#include <string.h>

/*
 * strlength - retutns the length of a string
 *
 * @s - the string  
 *
 * Return: integer length of the string
 */
 

int strlength(char *s)
{
    int i = 0 ;

    while (s[i] != '\0')
    i++;

    return (i);
}


#endif
