#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * print_unsigned - function that prints an unsigned number
 * @types: The list a of arguments
 * @buffer: Is the buffer array to handle print
 * @flags: this calculates active flags
 * @width: get width.
 * @precision: the precision specification
 * @size: The size specifier
 * Return: Number of chars printed
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
int x = BUFF_SIZE - 2;
unsigned long int num = va_arg(types, unsigned long int);

num = convert_size_unsgnd(num, size);

if (num == 0)
buffer[x--] = '0';
buffer[BUFF_SIZE - 1] = '\0';
while (num > 0)
{
buffer[x--] = (num % 10) + '0';
num /= 10;
}
x++;

return (write_unsgnd(0, x, buffer, flags, width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * print_octal - function that prints an unsigned number in octal notation
 * @types: The lista of arguments
 * @buffer: the buffer array to handle print
 * @flags: this calculates active flags
 * @width: get width.
 * @precision: is the precision specification
 * @size: is the size specifier
 * Return: Number of characters printed
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

int x = BUFF_SIZE - 2;
unsigned long int num = va_arg(types, unsigned long int);
unsigned long int init_num = num;

UNUSED(width);

num = convert_size_unsgnd(num, size);

if (num == 0)
buffer[x--] = '0';

buffer[BUFF_SIZE - 1] = '\0';
while (num > 0)
{
buffer[x--] = (num % 8) + '0';
num /= 8;
}

if (flags & F_HASH && init_num != 0)
buffer[x--] = '0';
x++;

return (write_unsgnd(0, x, buffer, flags, width, precision, size));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadecimal - function that prints an unsigned number in hexadecimal notation
 * @types: is the lista of arguments
 * @buffer: is the buffer array to handle print
 * @flags: this calculates active flags
 * @width: get width.
 * @precision: the precision specification
 * @size: is the size specifier
 * Return: Number of characters printed
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
return (print_hexa(types, "0123456789abcdef", buffer, flags, 'x', width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hexa_upper - function that prints an unsigned number in upper hexadecimal notation
 * @types: is the lista of arguments
 * @buffer: the buffer array to handle print
 * @flags: this calculates active flags
 * @width: get width.
 * @precision: the precision specification
 * @size: is the size specifier
 * Return: Number of charaters printed
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
return (print_hexa(types, "0123456789ABCDEF", buffer, flags, 'X', width, precision, size));
}

/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
 * print_hexa - function that prints a hexadecimal number in lower or upper
 * @types: is the lista of arguments
 * @map_to: the array of values to map the number to
 * @buffer: the buffer array to handle print
 * @flags: this calculates active flags
 * @flag_ch: this calculates active flags
 * @width: get width.
 * @precision: The precision specification
 * @size: the size specifier
 * @size: te size specification
 * Return: Number of characters printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
int x = BUFF_SIZE - 2;
unsigned long int num = va_arg(types, unsigned long int);
unsigned long int init_num = num;

UNUSED(width);

num = convert_size_unsgnd(num, size);

if (num == 0)
buffer[x--] = '0';

buffer[BUFF_SIZE - 1] = '\0';
while (num > 0)
{
buffer[x--] = map_to[num % 16];
num /= 16;
}
if (flags & F_HASH && init_num != 0)
{
buffer[x--] = flag_ch;
buffer[x--] = '0';
}
x++;
return (write_unsgnd(0, x, buffer, flags, width, precision, size));
}
