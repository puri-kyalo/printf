#include "main.h"

/**
 * is_printable - write a function that evaluates if a char is printable
 * @c: Character to be evaluated
 * Return: 1 if c is printable, otherwise 0
 */
int is_printable(char c)
{
if (c >= 32 && c < 127) /* return 1 else 0 */
return (1);

return (0);
}

/**
 * append_hexa_code - write a function that append ascci in hexadecimal code to buffer
 * @buffer: the array of characters
 * @i: is the index at which to start appending.
 * @ascii_code: ASSCI CODE
 * Return: Always 3
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
char map_to[] = "0123456789ABCDEF";

if (ascii_code < 0)
ascii_code *= -1;
buffer[i++] = '\\';
buffer[i++] = 'x';

buffer[i++] = map_to[ascii_code / 16];
buffer[i] = map_to[ascii_code % 16];

return (3);
}

/**
 * is_digit - write a function that verifies if a char is a digit
 * @c: Character to be evaluated
 * Return: 1 if c is a digit, otherwise 0
 */
int is_digit(char c)
{
if (c >= '0' && c <= '9')
return (1);
return (0);
}

/**
 * convert_size_number - write a function that casts a number to the specified size
 * @num: is the number to be casted
 * @size: The number indicating the type to be casted
 * Return: Casted value of num
 */
long int convert_size_number(long int num, int size)
{
if (size == S_LONG)
return (num);
else if (size == S_SHORT)
return ((short)num);

return ((int)num);
}

/**
 * convert_size_unsgnd - function that casts a number to the specified size
 * @num: is the number to be casted
 * @size: the number indicating the type to be casted
 * Return: Casted value of num
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
if (size == S_LONG)
return (num);
else if (size == S_SHORT)
return ((unsigned short)num);

return ((unsigned int)num);
}
