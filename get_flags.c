#include "main.h"

/**
 * get_flg - active flg
 * @format: string
 * @i: parameter
 * Return: flg
 */
int get_flg(const char *format, int *i)
{
	int j, act_i;
	int flg = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (act_i = *i + 1; format[act_i] != '\0'; act_i++)
	{
		for (j = 0; FLAGS_CH[j] != '\0'; j++)
			if (format[act_i] == FLAGS_CH[j])
			{
				flg |= FLAGS_ARR[j];
				break;
			}

		if (FLAGS_CH[j] == 0)
			break;
	}

	*i = act_i - 1;

	return (flg);
}
