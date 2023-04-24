#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "main.h"

/**
 * _printf - function my printf
 * @format: string whit format to print
 *
 * Return: number of chars that print
 */
int _printf(const char *format, ...)
{
	va_list argt;
	int length = 0;

	if (format == NULL)
		return (-1);

	va_start(argt, format);

	length = _print_format(format, argt);
	va_end(argt);
	return (length);
}
