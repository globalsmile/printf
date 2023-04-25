#include "main.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
/**
 * print_pointer - Prints the value of a pointer variable
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_pointer(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int index = BUFF_SIZE - 2, length = 2, padd_start = 1;
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);
	if (addrs == NULL)
		return (write(1, "(nil)", 5));
	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);
	num_addrs = (unsigned long)addrs;
	while (num_addrs > 0)
	{
		buffer[index--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;
	index++;
	return (write_pointer(buffer, index, length,
	width, flags, padd, extra_c, padd_start));
}
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_non_printable(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
	int p = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
		return (write(1, "(null)", 6));
	while (str[p] != '\0')
	{
		if (is_printable(str[p]))
			buffer[p + offset] = str[p];
		else
			offset += append_hexa_code(str[p], buffer, p + offset);
		p++;
	}
	buffer[p + offset] = '\0';
	return (write(1, buffer, p + offset));
}
/**
* print_reverse - Prints reverse string.
* @types: Lista of arguments
* @buffer: Buffer array to handle print
* @flags: Calculates active flags
* @width: get width
* @precision: Precision specification
* @size: Size specifier
* Return: Numbers of chars printed
*/
int print_reverse(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
	char *str;
	int p, counter = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);
	str = va_arg(types, char *);
	if (str == NULL)
	{
		UNUSED(precision);
		str = "(Null)";
	}
	for (p = 0; str[p]; p++)
	;
	for (p = p - 1; p >= 0; p--)
	{
		char y = str[p];

		write(1, &y, 1);
		counter++;
	}
	return (counter);
}
/**
 * print_rot13string - Print a string in rot13.
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */
int print_rot13string(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
	char y;
	char *str;
	unsigned int p, q;
	int counter = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
		str = "(AHYY)";
	for (p = 0; str[p]; p++)
	{
		for (q = 0; in[q]; q++)
		{
			if (in[q] == str[p])
			{
				y = out[q];
				write(1, &y, 1);
				counter++;
				break;
			}
		}
		if (!in[q])
		{
			y = str[p];
			write(1, &y, 1);
			counter++;
		}
	}
	return (counter);
}
