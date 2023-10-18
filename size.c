#include "main.h"

/**
 * get_size - Calculates the size to cast the argument
 * @format: Formatted string
 * @i: arguments
 *
 * Return: size.
 */
int get_size(const char *format, int *i)
{
	int act_i = *i + 1;
	int size = 0;

	if (format[act_i] == 'l')
		size = S_LONG;
	else if (format[act_i] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = act_i - 1;
	else
		*i = act_i;

	return (size);
}
