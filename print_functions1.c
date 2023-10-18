#include "main.h"

/**
 * _unsigned - Prints an unsigned number
 * @types: arguments
 * @buff: Buffer arra
 * @flg:  active flag
 * @w: get w
 * @accu: Precision specification
 * @size: Size specifier
 * Return: chars.
 */
int _unsigned(va_list types, char buff[],
	int flg, int w, int accu, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = cast_unsigned(num, size);

	if (num == 0)
		buff[i--] = '0';

	buff[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buff[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (unsigned_handler(0, i, buff, flg, w, accu, size));
}

/**
 * _octal - Prints an unsigned number in octal notation
 * @types: arguments
 * @buff: Buffer array
 * @flg: active flg
 * @w: get w
 * @accu: Precision specification
 * @size: Size specifier
 * Return: chars
 */
int _octal(va_list types, char buff[],
	int flg, int w, int accu, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(w);

	num = cast_unsigned(num, size);

	if (num == 0)
		buff[i--] = '0';

	buff[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buff[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flg & F_HASH && init_num != 0)
		buff[i--] = '0';

	i++;

	return (unsigned_handler(0, i, buff, flg, w, accu, size));
}

/**
 * _hexadec - Prints an unsigned number in hexadecimal notation
 * @types: arguments
 * @buff: Buffer array
 * @flg:  active flg
 * @w: get w
 * @accu: Precision specification
 * @size: Size specifier
 * Return: chars
 */
int _hexadec(va_list types, char buff[],
	int flg, int w, int accu, int size)
{
	return (_hex(types, "0123456789abcdef", buff,
		flg, 'x', w, accu, size));
}

/**
 * hex_upper - Prints an unsigned number in upper hexadecimal notation
 * @types: arguments
 * @buff: Buffer array
 * @flg:  active flg
 * @w: get w
 * @accu: Precision specification
 * @size: Size specifier
 * Return: chars
 */
int hex_upper(va_list types, char buff[],
	int flg, int w, int accu, int size)
{
	return (_hex(types, "0123456789ABCDEF", buff,
		flg, 'X', w, accu, size));
}

/**
 * _hex - Prints a hexadecimal number in lower or upper
 * @types: arguments
 * @map_to: Array
 * @buff: Buffer array
 * @flg:  active flg
 * @flag_ch: active flg
 * @w: get w
 * @accu: Precision specification
 * @size: Size specification
 * Return: Number of chars prints
 */
int _hex(va_list types, char map_to[], char buff[],
	int flg, char flag_ch, int w, int accu, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(w);

	num = cast_unsigned(num, size);

	if (num == 0)
		buff[i--] = '0';

	buff[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buff[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flg & F_HASH && init_num != 0)
	{
		buff[i--] = flag_ch;
		buff[i--] = '0';
	}

	i++;

	return (unsigned_handler(0, i, buff, flg, w, accu, size));
}
