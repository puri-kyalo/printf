#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char - function that prints a character
 * @types: is the list a of arguments
 * @buffer: is the buffer array to handle print
 * @flags:  this calculates active flags
 * @width: the width
 * @precision: the precision specification
 * @size: is the size specifier
 * Return: Number of chars printed.
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
char b = va_arg(types, int);
return (handle_write_char(b, buffer, flags, width, precision, size));
}
/************************* PRINT A STRING *************************/
/**
 * print_string - function that prints a string
 * @types: The list a of arguments
 * @buffer: The buffer array to handle print
 * @flags: This calculates active flags
 * @width: get width
 * @precision: the precision specification
 * @size: this is size specifier
 * Return: Number of chars printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
int length = 0, x;
char *str = va_arg(types, char *);

UNUSED(buffer);
UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);
if (str == NULL)
{
str = "(null)";
if (precision >= 6)
str = "      ";
}
while (str[length] != '\0')
length++;

if (precision >= 0 && precision < length)
length = precision;

if (width > length)
{
if (flags & F_MINUS)
{
write(1, &str[0], length);
for (x = width - length; x > 0; x--)
write(1, " ", 1);
return (width);
}
else
{
for (x = width - length; x > 0; x--)
write(1, " ", 1);
write(1, &str[0], length);
return (width);
}
}

return (write(1, str, length));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - function that prints a percent sign
 * @types: The lista of arguments
 * @buffer: is the buffer array to handle print
 * @flags:  this calculates active flags
 * @width: get widt.
 * @precision: the precision specification
 * @size: is the size specifier
 * Return: Number of characters printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
UNUSED(types);
UNUSED(buffer);
UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);
return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * print_int - function that print integer
 * @types: the lista of arguments
 * @buffer: the buffer array to handle print
 * @flags: this calculates active flags
 * @width: get width
 * @precision: the precision specification
 * @size: is the size specifier
 * Return: Number of chars printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
int x = BUFF_SIZE - 2;
int is_negative = 0;
long int a = va_arg(types, long int);
unsigned long int num;

a = convert_size_number(a, size);

if (a == 0)
buffer[x--] = '0';

buffer[BUFF_SIZE - 1] = '\0';
num = (unsigned long int)a;

if (a < 0)
{
num = (unsigned long int)((-1) * a);
is_negative = 1;
}
while (num > 0)
{
buffer[x--] = (num % 10) + '0';
num /= 10;
}

x++;

return (write_number(is_negative, x, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Prints an unsigned number
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of char printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
unsigned int a, m, x, sum;
unsigned int b[32];
int count;
UNUSED(buffer);
UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);

a = va_arg(types, unsigned int);
m = 2147483648;
b[0] = a / m;
for (x = 1; x < 32; x++)
{
m /= 2;
b[x] = (a / m) % 2;
}
for (x = 0, sum = 0, count = 0; x < 32; x++)
{
sum += b[x];
if (sum || x == 31)
{
char z = '0' + b[x];

write(1, &z, 1);
count++;
}
}
return (count);
}
