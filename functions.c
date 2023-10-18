#include "main.h"

/* CHAR */

/**
 * print_c - Prints a char
 * @types: arguments
 * @buff: buffer array
 * @flg:  active flg
 * @w: width
 * @accu: precision specification
 * @size: size specifier
 * Return: chars
 */
int print_c(va_list types, char buff[],
	int flg, int w, int accu, int size)
{
	char c = va_arg(types, int);

	return (w_handler(c, buff, flg, w, accu, size));
}
/* STRING */
/**
 * print_s - prints a string
 * @types: arguments
 * @buff: buffer array
 * @flg:  active flg
 * @w: get width
 * @accu: precision specification
 * @size: size specifier
 * Return: chars
 */
int print_s(va_list types, char buff[],
	int flg, int w, int accu, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buff);
	UNUSED(flg);
	UNUSED(w);
	UNUSED(accu);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (accu >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (accu >= 0 && accu < length)
		length = accu;

	if (w > length)
	{
		if (flg & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = w - length; i > 0; i--)
				write(1, " ", 1);
			return (w);
		}
		else
		{
			for (i = w - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (w);
		}
	}

	return (write(1, str, length));
}
/* PERCENTAGE */
/**
 * _percentage - Prints a percent sign
 * @types: arguments
 * @buff: buffer array
 * @flg:  active flg
 * @w: get width
 * @accu: precision specification
 * @size: size specifier
 * Return: chars
 */
int _percentage(va_list types, char buff[],
	int flg, int w, int accu, int size)
{
	UNUSED(types);
	UNUSED(buff);
	UNUSED(flg);
	UNUSED(w);
	UNUSED(accu);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/* INTEGER */
/**
 * print_i - prints int
 * @types: arguments
 * @buff: buffer array
 * @flg:  active flg
 * @w: get width.
 * @accu: precision specification
 * @size: size specifier
 * Return: chars
 */
int print_i(va_list types, char buff[],
	int flg, int w, int accu, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = cast_int(n, size);

	if (n == 0)
		buff[i--] = '0';

	buff[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buff[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (n_handler(is_negative, i, buff, flg, w, accu, size));
}

/* PRINT BINARY */
/**
 * _binary - prints an unsigned number
 * @types: arguments
 * @buff: buffer array
 * @flg:  active flg
 * @w: get width.
 * @accu: precision specification
 * @size: size specifier
 * Return: chars.
 */
int _binary(va_list types, char buff[],
	int flg, int w, int accu, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buff);
	UNUSED(flg);
	UNUSED(w);
	UNUSED(accu);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648;
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
