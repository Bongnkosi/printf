#include "main.h"

/**
 * _pointer - Prints the value of a pointer variable
 * @types: arguments
 * @buff: Buffer array
 * @flg:  active flg
 * @w: get w
 * @accu: Precision specification
 * @size: Size specifier
 * Return: chars
 */
int _pointer(va_list types, char buff[],
	int flg, int w, int accu, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(w);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buff[BUFF_SIZE - 1] = '\0';
	UNUSED(accu);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buff[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flg & F_ZERO) && !(flg & F_MINUS))
		padd = '0';
	if (flg & F_PLUS)
		extra_c = '+', length++;
	else if (flg & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	/*return*/
	return (ptr_handler(buff, ind, length,
		w, flg, padd, extra_c, padd_start));
}

/**
 * _unprintable - Prints ascii codes in hexa of non printable chars
 * @types: arguments
 * @buff: Buffer array
 * @flg: active flg
 * @w: get w
 * @accu: Precision specification
 * @size: Size specifier
 * Return: chars
 */
int _unprintable(va_list types, char buff[],
	int flg, int w, int accu, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flg);
	UNUSED(w);
	UNUSED(accu);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (_printable(str[i]))
			buff[i + offset] = str[i];
		else
			offset += append_hex(str[i], buff, i + offset);

		i++;
	}

	buff[i + offset] = '\0';

	return (write(1, buff, i + offset));
}

/**
 * _reverse - Prints reverse string.
 * @types: arguments
 * @buff: Buffer array
 * @flg:  active flg
 * @w: get w
 * @accu: Precision specification
 * @size: Size specifier
 * Return: chars
 */

int _reverse(va_list types, char buff[],
	int flg, int w, int accu, int size)
{
	char *str;
	int i, count = 0;

	UNUSED(buff);
	UNUSED(flg);
	UNUSED(w);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(accu);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/**
 * _string - Print a string in rot13.
 * @types: arguments
 * @buff: Buffer array
 * @flg:  active flg
 * @w: get w
 * @accu: Precision specification
 * @size: Size specifier
 * Return: chars
 */
int _string(va_list types, char buff[],
	int flg, int w, int accu, int size)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buff);
	UNUSED(flg);
	UNUSED(w);
	UNUSED(accu);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
