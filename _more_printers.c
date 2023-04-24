#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
/**
 * _print_int_binary - Prints a int converted to binary
 * @args: A list of variadic arguments
 *
 * Return: The number of printed digits
 */
int _print_int_binary(va_list args)
{
	unsigned int x = 0;
	int p = 0, new = 0;

	new = va_arg(args, int);
	x = new;
	if (new < 0)
	{
		_putchar('1');
		new = new * -1;
		x = new;
		p += 1;
	}
	while (x > 0)
	{
		x = x / 2;
		p++;
	}
	_recursion_int_binary(new);
	return (p);
}
/**
 * _recursion_int_binary - Prints a binary
 * @a: integer to print
 *
 */
void _recursion_int_binary(int a)
{
	unsigned int q;

	q = a;
	if (q / 2)
		_recursion_int_binary(q / 2);
	_putchar(q % 2 + '0');
}
