#include "main.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
/**
 * handle_write_char - Prints a string
 * @d: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char d, char buffer[],
int flags, int width, int precision, int size)
{
	int p = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	buffer[p++] = d;
	buffer[p] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (p = 0; p < width - 1; p++)
			buffer[BUFF_SIZE - p - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - p - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - p - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}
/**
 * write_number - Prints a string
 * @is_negative: Lista of arguments
 * @index: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int index, char buffer[],
int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - index - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(index, buffer, flags, width, precision,
		length, padd, extra_ch));
}
/**
 * write_num - Write a number using a bufffer
 * @index: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @prec: Precision specifier
 * @length: Number length
 * @padd: Pading char
 * @extra_c: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int index, char buffer[],
int flags, int width, int prec,
int length, char padd, char extra_c)
{
	int p, padd_start = 1;

	if (prec == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0' && width == 0)
		return (0);
	if (prec == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		buffer[index] = padd = ' ';
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--index] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (p = 1; p < width - length + 1; p++)
			buffer[p] = padd;
		buffer[p] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			if (extra_c)
				buffer[--index] = extra_c;
			return (write(1, &buffer[index], length) + write(1, &buffer[1], p - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if (extra_c)
				buffer[--index] = extra_c;
			return (write(1, &buffer[1], p - 1) + write(1, &buffer[index], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], p - padd_start) +
				write(1, &buffer[index], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--index] = extra_c;
	return (write(1, &buffer[index], length));
}
/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @index: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int index, char buffer[],
int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - index - 1, p = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		return (0);
	if (precision > 0 && precision < length)
		padd = ' ';
	while (precision > length)
	{
		buffer[--index] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > length)
	{
		for (p = 0; p < width - length; p++)
			buffer[p] = padd;

		buffer[p] = '\0';

		if (flags & F_MINUS)
		{
			return (write(1, &buffer[index], length) + write(1, &buffer[0], p));
		}
		else
		{
			return (write(1, &buffer[0], p) + write(1, &buffer[index], length));
		}
	}
	return (write(1, &buffer[index], length));
}
/**
 * write_pointer - Write a memory address
 * @buffer: Arrays of chars
 * @index: Index at which the number starts in the buffer
 * @length: Length of number
 * @width: Width specifier
 * @flags: Flags specifier
 * @padd: Char representing the padding
 * @extra_c: Char representing extra char
 * @padd_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int index, int length,
int width, int flags, char padd, char extra_c, int padd_start)
{
	int p;

	if (width > length)
	{
		for (p = 3; p < width - length + 3; p++)
			buffer[p] = padd;
		buffer[p] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extra_c)
				buffer[--index] = extra_c;
			return (write(1, &buffer[index], length) + write(1, &buffer[3], p - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extra_c)
				buffer[--index] = extra_c;
			return (write(1, &buffer[3], p - 3) + write(1, &buffer[index], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], p - padd_start) +
				write(1, &buffer[index], length - (1 - padd_start) - 2));
		}
	}
	buffer[--index] = 'x';
	buffer[--index] = '0';
	if (extra_c)
		buffer[--index] = extra_c;
	return (write(1, &buffer[index], BUFF_SIZE - index - 1));
}
