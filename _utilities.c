#include "main.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
/**
 * is_printable - Evaluates if a char is printable
 * @d: Char to be evaluated.
 *
 * Return: 1 if d is printable, 0 otherwise
 */
int is_printable(char d)
{
	if (d >= 32 && d < 127)
		return (1);

	return (0);
}
/**
 * append_hexa_code - Append ascci in hexadecimal code to buffer
 * @buffer: Array of chars.
 * @p: Index at which to start appending.
 * @ascii_code: ASSCI CODE.
 * Return: Always 3
 */
int append_hexa_code(char ascii_code, char buffer[], int p)
{
	char map_to[] = "0123456789ABCDEF";

	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[p++] = '\\';
	buffer[p++] = 'x';

	buffer[p++] = map_to[ascii_code / 16];
	buffer[p] = map_to[ascii_code % 16];

	return (3);
}
/**
 * is_digit - Verifies if a char is a digit
 * @d: Char to be evaluated
 *
 * Return: 1 if d is a digit, 0 otherwise
 */
int is_digit(char d)
{
	if (d >= '0' && d <= '9')
		return (1);

	return (0);
}
/**
 * convert_size_number - Casts a number to the specified size
 * @num: Number to be casted.
 * @sizes: Number indicating the type to be casted.
 *
 * Return: Casted value of num
 */
long int convert_size_number(long int num, int sizes)
{
	if (sizes == S_LONG)
		return (num);
	else if (sizes == S_SHORT)
		return ((short)num);

	return ((int)num);
}
/**
 * convert_size_unsgnd - Casts a number to the specified size
 * @num: Number to be casted
 * @sizes: Number indicating the type to be casted
 *
 * Return: Casted value of num
 */
long int convert_size_unsgnd(unsigned long int num, int sizes)
{
	if (sizes == S_LONG)
		return (num);
	else if (sizes == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
