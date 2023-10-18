#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/*FLAGS*/
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/*SIZES*/
#define S_LONG 2
#define S_SHORT 1

/**
 * struct fmt - Struct
 *
 * @fmt: format
 * @fn: function
 */
struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct fmt fmt_t - Struct
 *
 * @fmt: format
 * @fm_t: function
 */
typedef struct fmt fmt_t;

int _printf(const char *format, ...);
int print_handler(const char *fmt, int *i,
va_list list, char buff[], int flg, int w, int accu, int size);

/*FUNCTIONS*/

/* print chars and strings */
int print_c(va_list types, char buff[],
	int flg, int w, int accu, int size);
int print_s(va_list types, char buff[],
	int flg, int w, int accu, int size);
int _percentage(va_list types, char buff[],
	int flg, int w, int accu, int size);

/* print numbers */
int print_i(va_list types, char buff[],
	int flg, int w, int accu, int size);
int _binary(va_list types, char buff[],
	int flg, int w, int accu, int size);
int _unsigned(va_list types, char buff[],
	int flg, int w, int accu, int size);
int _octal(va_list types, char buff[],
	int flg, int w, int accu, int size);
int _hexadec(va_list types, char buff[],
	int flg, int w, int accu, int size);
int hex_upper(va_list types, char buff[],
	int flg, int w, int accu, int size);

int _hex(va_list types, char map_to[],
char buff[], int flg, char flag_ch, int w, int accu, int size);

/* print non printable characters */
int _unprintable(va_list types, char buff[],
	int flg, int w, int accu, int size);

/* print memory address */
int _pointer(va_list types, char buff[],
	int flg, int w, int accu, int size);

/* handle other specifiers */
int get_flg(const char *format, int *i);
int get_w(const char *format, int *i, va_list list);
int get_accu(const char *format, int *i, va_list list);
int get_size(const char *format, int *i);

/*print string in reverse*/
int _reverse(va_list types, char buff[],
	int flg, int w, int accu, int size);

/*print a string in rot 13*/
int _string(va_list types, char buff[],
	int flg, int w, int accu, int size);

/* write */
int w_handler(char c, char buff[],
	int flg, int w, int accu, int size);
int n_handler(int is_positive, int ind, char buff[],
	int flg, int w, int accu, int size);
int num_handler(int ind, char bff[], int flg, int w, int accu,
	int length, char padd, char extra_c);
int ptr_handler(char buff[], int ind, int length,
	int w, int flg, char padd, char extra_c, int padd_start);

int unsigned_handler(int is_negative, int ind,
char buff[],
	int flg, int w, int accu, int size);

/* UTILS */
int _printable(char);
int append_hex(char, char[], int);
int int_find(char);

long int cast_int(long int num, int size);
long int cast_unsigned(unsigned long int num, int size);

#endif
