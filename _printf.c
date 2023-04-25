#include "main.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void _putchar(char buffer[], int *buff_ind);
/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int p, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);
	va_start(list, format);
	for (p = 0; format && format[p] != '\0'; p++)
	{
		if (format[p] != '%')
		{
			buffer[buff_ind++] = format[p];
			if (buff_ind == BUFF_SIZE)
				_putchar(buffer, &buff_ind);
			printed_chars++;
		}
		else
		{
			_putchar(buffer, &buff_ind);
			flags = get_flags(format, &p);
			width = get_width(format, &p, list);
			precision = get_precision(format, &p, list);
			size = get_size(format, &p);
			++p;
			printed = handle_print(format, &p, list, buffer,
					flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}
	_putchar(buffer, &buff_ind);
	va_end(list);
	return (printed_chars);
}
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
