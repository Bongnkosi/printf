#include "main.h"

void _buffer(char buff[], int *buff_i);

/**
 * _printf - prints to stdout
 * @format: format.
 * Return: chars.
 */
int _printf(const char *format, ...)
{
	int i, prints = 0, prints_c = 0;
	int flg, w, accu, size, buff_i = 0;
	va_list list;
	char buff[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buff[buff_i++] = format[i];
			if (buff_i == BUFF_SIZE)
				_buffer(buff, &buff_i);
			/* write(1, &format[i], 1);*/
			prints_c++;
		}
		else
		{
			_buffer(buff, &buff_i);
			flg = get_flg(format, &i);
			w = get_w(format, &i, list);
			accu = get_accu(format, &i, list);
			size = get_size(format, &i);
			++i;
			prints = print_handler(format, &i, list, buff,
				flg, w, accu, size);
			if (prints == -1)
				return (-1);
			prints_c += prints;
		}
	}

	_buffer(buff, &buff_i);

	va_end(list);

	return (prints_c);
}

/**
 * _buffer - Prints the contents of the buff if it exist
 * @buff: Array of chars
 * @buff_i: Index at which to add next char, represents the length.
 */
void _buffer(char buff[], int *buff_i)
{
	if (*buff_i > 0)
		write(1, &buff[0], *buff_i);

	*buff_i = 0;
}
