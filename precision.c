#include "main.h"

/**
 * get_accu - precision
 * @format: string
 * @i: arguments
 * @list: list of arguments.
 *
 * Return: accu
 */
int get_accu(const char *format, int *i, va_list list)
{
	int act_i = *i + 1;
	int accu = -1;

	if (format[act_i] != '.')
		return (accu);

	accu = 0;

	for (act_i += 1; format[act_i] != '\0'; act_i++)
	{
		if (int_find(format[act_i]))
		{
			accu *= 10;
			accu += format[act_i] - '0';
		}
		else if (format[act_i] == '*')
		{
			act_i++;
			accu = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = act_i - 1;

	return (accu);
}
