#include "main.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * print_char - Prints a char
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_char(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
	char q = va_arg(types, int);

	return (handle_write_char(q, buffer, flags, width, precision, size));
}
/**
 * print_string - Prints a string
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_string(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
	int length = 0, p;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = " ";
	}
	while (str[length] != '\0')
		length++;
	if (precision >= 0 && precision < length)
		length = precision;
	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (p = width - length; p > 0; p--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (p = width - length; p > 0; p--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}
	return (write(1, str, length));
}
/**
 * print_percent - Prints a percent sign
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_percent(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}
/**
 * print_int - Print int
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_int(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
	int p = BUFF_SIZE - 2;
	int is_negative = 0;
	long int q = va_arg(types, long int);
	unsigned long int num;

	q = convert_size_number(q, size);
	if (q == 0)
	buffer[p--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)q;
	if (q < 0)
	{
		num = (unsigned long int)((-1) * q);
		is_negative = 1;
	}
	while (num > 0)
	{
		buffer[p--] = (num % 10) + '0';
		num /= 10;
	}
	p++;
	return (write_number(is_negative, p, buffer, flags, width, precision, size));
}
/**
 * print_binary - Prints an unsigned number
 * @types: Lists of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of char printed.
 */
int print_binary(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
	unsigned int p, q, r, sum;
	unsigned int a[32];
	int counter;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	p = va_arg(types, unsigned int);
	q = 2147483648; /* (2 ^ 31) */
	a[0] = p / q;
	for (r = 1; r < 32; r++)
	{
		q /= 2;
		a[r] = (p / q) % 2;
	}
	for (r = 0, sum = 0, counter = 0; r < 32; r++)
	{
		sum += a[r];
		if (sum || r == 31)
		{
			char z = '0' + a[r];

			write(1, &z, 1);
			counter++;
		}
	}
	return (counter);
}
