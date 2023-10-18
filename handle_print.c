#include "main.h"
/**
 * print_handler - Prints an argument based on its type
 * @fmt: Formatted string
 * @list: List of arguments
 * @ind: ind
 * @buff: Buffer array
 * @flg: active flg
 * @w: get w.
 * @accu: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int print_handler(const char *fmt, int *ind, va_list list, char buff[],
	int flg, int w, int accu, int size)
{
	int i, unknow_len = 0, prints_c = -1;
	fmt_t fmt_types[] = {
		{'c', print_c}, {'s', print_s}, {'%', _percentage},
		{'i', print_i}, {'d', print_i}, {'b', _binary},
		{'u', _unsigned}, {'o', _octal}, {'x', _hexadec},
		{'X', hex_upper}, {'p', _pointer}, {'S', _unprintable},
		{'r', _reverse}, {'R', _string}, {'\0', NULL}
	};
	for (i = 0; fmt_types[i].fmt != '\0'; i++)
		if (fmt[*ind] == fmt_types[i].fmt)
			return (fmt_types[i].fn(list, buff, flg, w, accu, size));

	if (fmt_types[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (w)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &fmt[*ind], 1);
		return (unknow_len);
	}
	return (prints_c);
}
