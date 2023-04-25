#include "main.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
/**
 * get_size - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @p: List of arguments to be printed.
 *
 * Return: Precision.
 */
int get_size(const char *format, int *p)
{
	int curr_p = *p + 1;
	int size = 0;

	if (format[curr_p] == 'l')
		size = S_LONG;
	else if (format[curr_p] == 'h')
		size = S_SHORT;

	if (size == 0)
		*p = curr_p - 1;
	else
		*p = curr_p;

	return (size);
}
