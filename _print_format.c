#include <stdlib.h>
#include "main.h"
/**
 * _print_format - Prints a format
 * @format: The format to prints
 * @args: A list of variadic arguments
 *
 * Return: The length of the format
 */
int _print_format(const char *format, va_list args)
{
	int counter = 0;
	int p = 0;

	while (format && format[p])
	{
		if (format[p] == '%')
		{
			if (format[p + 1] == '\0')
				return (-1);

			p++;

			while (format[p] == ' ')
				p++;

			if (format[p] == '%')
				counter += _putchar(format[p]);

			if (_validate_char(format[p]) == 0)
			{
				counter = _print_invalid_spec(format[p - 1], format[p], counter);
			}
			else
			{
				counter += _print_spec(format[p], args);
			}
		}
		else
		{
			counter += _putchar(format[p]);
		}

		p++;
	}

	return (counter);
}
/**
 * _print_spec - Prints a valid specifier
 * @format: The specifier to prints
 * @args: A list of variadic arguments
 *
 * Return: The length of the specifier
 */
int _print_spec(char format, va_list args)
{
	int p  = 0, length = 0;
	spc_dt _types[] = {
		{"c", _print_a_char},
		{"s", _print_a_string},
		{"d", _print_a_integer},
		{"i", _print_a_integer},
		{"b", _print_int_binary},
		{NULL, NULL}
	};

	while (_types[p].specifier)
	{
		if (*_types[p].specifier == format)
			length = _types[p].f(args);

		p++;
	}

	return (length);
}
/**
 * _print_invalid_spec - Prints a invalid specifier
 * @prev_format: The previous specifier of actual specifier
 * @format: The specifier to prints
 * @count: The current count before prints invalid specifiers
 *
 * Return: The current count after prints invalid specifiers
 */
int _print_invalid_spec(char prev_format, char format, int count)
{
	count += _putchar('%');

	if (prev_format == ' ')
	{
		count += _putchar(' ');
		count += _putchar(format);
	}
	else
	{
		count += _putchar(format);
	}

	return (count);
}
/**
 * _validate_char - validate the type
 * @_type: character to be comparate
 *
 * Return: 1 if char is equal to a type
 */
int _validate_char(char _type)
{
	char _types[] = {'c', 's', 'd', 'i', 'b', '%'};
	int p = 0;

	while (_types[p])
	{
		if (_types[p] == _type)
			return (1);
		p++;
	}
	return (0);
}
