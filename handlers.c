#include "main.h"

/**
 * w_handler - Prints a string
 * @c: char types.
 * @buff: Buffer array
 * @flg:  active flg.
 * @w: get w.
 * @accu: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars prints.
 */
int w_handler(char c, char buff[],
	int flg, int w, int accu, int size)
{
	int i = 0;
	char padd = ' ';

	UNUSED(accu);
	UNUSED(size);

	if (flg & F_ZERO)
		padd = '0';

	buff[i++] = c;
	buff[i] = '\0';

	if (w > 1)
	{
		buff[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < w - 1; i++)
			buff[BUFF_SIZE - i - 2] = padd;

		if (flg & F_MINUS)
			return (write(1, &buff[0], 1) +
					write(1, &buff[BUFF_SIZE - i - 1], w - 1));
		else
			return (write(1, &buff[BUFF_SIZE - i - 1], w - 1) +
					write(1, &buff[0], 1));
	}

	return (write(1, &buff[0], 1));
}


/**
 * n_handler - Prints a string
 * @is_negative: arguments
 * @ind: char types.
 * @buff: Buffer array
 * @flg:  active flg
 * @w: get w.
 * @accu: presision specifier
 * @size: Size specifier
 *
 * Return: Number of chars prints.
 */
int n_handler(int is_negative, int ind, char buff[],
	int flg, int w, int accu, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flg & F_ZERO) && !(flg & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flg & F_PLUS)
		extra_ch = '+';
	else if (flg & F_SPACE)
		extra_ch = ' ';

	return (num_handler(ind, buff, flg, w, accu,
		length, padd, extra_ch));
}

/**
 * num_handler - Write a number using a bufffer
 * @ind: Index
 * @buff: Buffer
 * @flg: Flags
 * @w: w
 * @prec: Precision specifier
 * @length: length
 * @padd: Pading char
 * @extra_c: Extra char
 *
 * Return: Number of prints chars.
 */
int num_handler(int ind, char buff[],
	int flg, int w, int prec,
	int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buff[ind] == '0' && w == 0)
		return (0); /* printf(".0d", 0)  no char is prints */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buff[ind] == '0')
		buff[ind] = padd = ' '; /* w is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buff[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (w > length)
	{
		for (i = 1; i < w - length + 1; i++)
			buff[i] = padd;
		buff[i] = '\0';
		if (flg & F_MINUS && padd == ' ')/* Asign extra char to left of buff */
		{
			if (extra_c)
				buff[--ind] = extra_c;
			return (write(1, &buff[ind], length) + write(1, &buff[1], i - 1));
		}
		else if (!(flg & F_MINUS) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buff[--ind] = extra_c;
			return (write(1, &buff[1], i - 1) + write(1, &buff[ind], length));
		}
		else if (!(flg & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buff[--padd_start] = extra_c;
			return (write(1, &buff[padd_start], i - padd_start) +
				write(1, &buff[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buff[--ind] = extra_c;
	return (write(1, &buff[ind], length));
}

/**
 * unsigned_handler - Writes an unsigned number
 * @is_negative: negative
 * @ind: Index
 * @buff: Array
 * @flg: Flags specifiers
 * @w: Width specifier
 * @accu: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */
int unsigned_handler(int is_negative, int ind,
	char buff[],
	int flg, int w, int accu, int size)
{
	/* The number is stored at the bufer's right and starts at position i */
	int length = BUFF_SIZE - ind - 1, i = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (accu == 0 && ind == BUFF_SIZE - 2 && buff[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is prints */

	if (accu > 0 && accu < length)
		padd = ' ';

	while (accu > length)
	{
		buff[--ind] = '0';
		length++;
	}

	if ((flg & F_ZERO) && !(flg & F_MINUS))
		padd = '0';

	if (w > length)
	{
		for (i = 0; i < w - length; i++)
			buff[i] = padd;

		buff[i] = '\0';

		if (flg & F_MINUS) /* Asign extra char to left of buff [buff>padd]*/
		{
			return (write(1, &buff[ind], length) + write(1, &buff[0], i));
		}
		else /* Asign extra char to left of padding [padd>buff]*/
		{
			return (write(1, &buff[0], i) + write(1, &buff[ind], length));
		}
	}

	return (write(1, &buff[ind], length));
}

/**
 * ptr_handler - Write a memory address
 * @buff: Arrays
 * @ind: Index
 * @length: Length
 * @w: width 
 * @flg: Flags specifier
 * @padd: padding
 * @extra_c: extra char
 * @padd_start: start index
 *
 * Return: Number of written chars.
 */
int ptr_handler(char buff[], int ind, int length,
	int w, int flg, char padd, char extra_c, int padd_start)
{
	int i;

	if (w > length)
	{
		for (i = 3; i < w - length + 3; i++)
			buff[i] = padd;
		buff[i] = '\0';
		if (flg & F_MINUS && padd == ' ')/* Asign extra char to left of buff */
		{
			buff[--ind] = 'x';
			buff[--ind] = '0';
			if (extra_c)
				buff[--ind] = extra_c;
			return (write(1, &buff[ind], length) + write(1, &buff[3], i - 3));
		}
		else if (!(flg & F_MINUS) && padd == ' ')/* extra char to left of buff */
		{
			buff[--ind] = 'x';
			buff[--ind] = '0';
			if (extra_c)
				buff[--ind] = extra_c;
			return (write(1, &buff[3], i - 3) + write(1, &buff[ind], length));
		}
		else if (!(flg & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buff[--padd_start] = extra_c;
			buff[1] = '0';
			buff[2] = 'x';
			return (write(1, &buff[padd_start], i - padd_start) +
				write(1, &buff[ind], length - (1 - padd_start) - 2));
		}
	}
	buff[--ind] = 'x';
	buff[--ind] = '0';
	if (extra_c)
		buff[--ind] = extra_c;
	return (write(1, &buff[ind], BUFF_SIZE - ind - 1));
}
