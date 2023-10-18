#include "main.h"

/**
 * _printable - Evaluates if a char is printable
 * @c: Char to be evaluated.
 *
 * Return: 1 if c is printable, 0 otherwise
 */
int _printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hex - Append ascci in hexadecimal code to buff
 * @buff: Array
 * @i: Index
 * @ascii_code: ASSCI CODE.
 * Return: Always 3
 */
int append_hex(char ascii_code, char buff[], int i)
{
	char map_to[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	buff[i++] = '\\';
	buff[i++] = 'x';

	buff[i++] = map_to[ascii_code / 16];
	buff[i] = map_to[ascii_code % 16];

	return (3);
}

/**
 * int_find - Verifies if a char is a digit
 * @c: Char to be evaluated
 *
 * Return: 1 if c is a digit, 0 otherwise
 */
int int_find(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * cast_int - Casts a number to the specified size
 * @num: Number to be casted
 * @size: type to be casted
 *
 * Return: Casted value of num
 */
long int cast_int(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * cast_unsigned - Casts a number to the specified size
 * @num: Number to be casted
 * @size: type to be casted
 *
 * Return: Casted value of num
 */
long int cast_unsigned(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
