#include <stdio.h>
#include "main.h"

/**
 * _putchar - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void _putchar(char buffer[], int *buff_ind)
{
        if (*buff_ind > 0)
                write(1, &buffer[0], *buff_ind);
        *buff_ind = 0;
}
