#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
/**
 * _print_a_char - Prints a char
 * @args: A list of variadic arguments
 *
 * Return: The length of the character
 */
int _print_a_char(va_list args)
{
	_putchar(va_arg(args, int));
	return (1);
}
/**
 * _print_a_string - Prints a string
 * @args: A list of variadic arguments
 *
 * Return: The length of the string
 */
int _print_a_string(va_list args)
{
	char *arg = va_arg(args, char *);
	int p = 0;

	if (arg != NULL)
	{
		while (arg[p])
		{
			_putchar(arg[p]);
			p++;
		}

		return (p);
	}

	_putchar('(');
	_putchar('n');
	_putchar('u');
	_putchar('l');
	_putchar('l');
	_putchar(')');
	return (6);
}
/**
 * _print_a_integer - Prints a integer
 * @args: A list of variadic arguments
 *
 * Return: The length of the string
 */
int _print_a_integer(va_list args)
{
	int counter = 1, m = 0;
	unsigned int j = 0;

	j = va_arg(args, int);
	m = j;
	if (m < 0)
	{
		_putchar('-');
		m = m * -1;
		j = m;
		counter += 1;
	}
	while (j > 9)
	{
		j = j / 10;
		counter++;
	}

	_recursion_integer(m);
	return (counter);
}
/**
 * _recursion_integer - Prints a integer
 * @a: integer to print
 *
 * Return: Nothing
 */
void _recursion_integer(int a)
{
	unsigned int q;

	q = a;
	if (q / 10)
		_recursion_integer(q / 10);
	_putchar(q % 10 + '0');
}
