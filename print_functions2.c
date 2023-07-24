#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * print_pointer - function that prints the value of a pointer variable
 * @types: The list a of arguments
 * @buffer: The buffer array to handle print
 * @flags: this calculates active flags
 * @width: get width.
 * @precision: the precision specification
 * @size: the size specifier
 * Return: Number of characters printed.
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
char extra_c = 0, padd = ' ';
int ind = BUFF_SIZE - 2, length = 2, padd_start = 1;
unsigned long num_addrs;
char map_to[] = "0123456789abcdef";
void *addrs = va_arg(types, void *);

UNUSED(width);
UNUSED(size);

if (addrs == NULL)
return (write(1, "(nil)", 5));

buffer[BUFF_SIZE - 1] = '\0';
UNUSED(precision);

num_addrs = (unsigned long)addrs;
while (num_addrs > 0)
{
buffer[ind--] = map_to[num_addrs % 16];
num_addrs /= 16;
length++;
}

if ((flags & F_ZERO) && !(flags & F_MINUS))
padd = '0';
if (flags & F_PLUS)
extra_c = '+', length++;
else if (flags & F_SPACE)
extra_c = ' ', length++;

ind++;

/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
return (write_pointer(buffer, ind, length,
		width, flags, padd, extra_c, padd_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - function that prints ascii codes in hexa of non printable chars
 * @types: the lista of arguments
 * @buffer: the buffer array to handle print
 * @flags: this calculates active flags
 * @width: get width.
 * @precision: the precision specification
 * @size: the size specifier
 * Return: Number of characters printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
int x = 0, offset = 0;
char *str = va_arg(types, char *);

UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);

if (str == NULL)
return (write(1, "(null)", 6));

while (str[x] != '\0')
{
if (is_printable(str[x]))
buffer[x + offset] = str[x];
else
offset += append_hexa_code(str[x], buffer, x + offset);

x++;
}
buffer[x + offset] = '\0';
return (write(1, buffer, x + offset));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - function that prints reverse string.
 * @types: the lista of arguments
 * @buffer: the buffer array to handle print
 * @flags: this calculates active flags
 * @width: get width.
 * @precision: the precision specification
 * @size: the size specifier
 * Return: Numbers of characters printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
char *str;
int x, count = 0;

UNUSED(buffer);
UNUSED(flags);
UNUSED(width);
UNUSED(size);

str = va_arg(types, char *);
if (str == NULL)
{
UNUSED(precision);

str = ")Null(";
}
for (x = 0; str[x]; x++)
;
for (x = x - 1; x >= 0; x--)
{
char z = str[x];

write(1, &z, 1);
count++;
}
return (count);
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - function that print a string in rot13.
 * @types: the lista of arguments
 * @buffer: the buffer array to handle print
 * @flags: this calculates active flags
 * @width: get width.
 * @precision: the precision specification
 * @size: the size specifier
 * Return: Numbers of characters printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
char x;
char *str;
unsigned int a, b;
int count = 0;
char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

str = va_arg(types, char *);
UNUSED(buffer);
UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);

if (str == NULL)
str = "(AHYY)";
for (a = 0; str[a]; a++)
{
for (b = 0; in[b]; b++)
{
if (in[b] == str[a])
{
x = out[b];
write(1, &x, 1);
count++;
break;
}
}
if (!in[b])
{
x = str[a];
write(1, &x, 1);
count++;
}
}
return (count);
}
