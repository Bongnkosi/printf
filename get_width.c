#include "main.h"

/**
 * get_w - w
 * @format: Formatted string
 * @i: arguments
 * @list: list of arguments
 *
 * Return: w.
 */
int get_w(const char *format, int *i, va_list list)
{
	int act_i;
	int w = 0;

	for (act_i = *i + 1; format[act_i] != '\0'; act_i++)
	{
		if (int_find(format[act_i]))
		{
			w *= 10;
			w += format[act_i] - '0';
		}
		else if (format[act_i] == '*')
		{
			act_i++;
			w = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = act_i - 1;

	return (w);
}
