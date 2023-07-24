#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - write a function that prints a string
 * @c: is the character types
 * @buffer: is the buffer array to handle print
 * @flags: calculates active flags
 * @width: the get width
 * @precision: The precision specifier
 * @size: is the size specifier
 * Return: Number of chars printed
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{
int x = 0;
char padd = ' ';
UNUSED(precision);
UNUSED(size);

if (flags & F_ZERO)
padd = '0';

buffer[x++] = c;
buffer[x] = '\0';

if (width > 1)
{
buffer[BUFF_SIZE - 1] = '\0';
for (x = 0; x < width - 1; x++)
buffer[BUFF_SIZE - x - 2] = padd;

if (flags & F_MINUS)
return (write(1, &buffer[0], 1) + write(1, &buffer[BUFF_SIZE - x - 1], width - 1));
else
return (write(1, &buffer[BUFF_SIZE - x - 1], width - 1) + write(1, &buffer[0], 1));
}
return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - function that prints a string
 * @is_negative: the lista of arguments
 * @ind: The character types
 * @buffer: The buffer array to handle print
 * @flags: This calculates active flags
 * @width: is the get width
 * @precision: is the precision specifier
 * @size: the size specifier.
 * Return: Number of chars printed
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
int length = BUFF_SIZE - ind - 1;
char padd = ' ', extra_ch = 0;

UNUSED(size);
if ((flags & F_ZERO) && !(flags & F_MINUS))
padd = '0';
if (is_negative)
extra_ch = '-';
else if (flags & F_PLUS)
extra_ch = '+';
else if (flags & F_SPACE)
extra_ch = ' ';

return (write_num(ind, buffer, flags, width, precision, length, padd, extra_ch));
}

/**
 * write_num - function that writes a number using a bufffer
 * @ind: is the index at which the number starts on the buffer
 * @buffer: The buffer
 * @flags: is the flags
 * @width: the width
 * @prec: is the precision specifier
 * @length: The number length
 * @padd: is the pading character
 * @extra_c: Extra character
 * Return: Number of printed characters.
 */
int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
int x, padd_start = 1;
if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
return (0);
if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
buffer[ind] = padd = ' ';
if (prec > 0 && prec < length)
padd = ' ';
while (prec > length)
buffer[--ind] = '0', length++;
if (extra_c != 0)
length++;
if (width > length)
{
for (x = 1; x < width - length + 1; x++)
buffer[x] = padd;
buffer[x] = '\0';
if (flags & F_MINUS && padd == ' ')
{
if (extra_c)
buffer[--ind] = extra_c;
return (write(1, &buffer[ind], length) + write(1, &buffer[1], x - 1));
}
else if (!(flags & F_MINUS) && padd == ' ')
{
if (extra_c)
buffer[--ind] = extra_c;
return (write(1, &buffer[1], x - 1) + write(1, &buffer[ind], length));
}
else if (!(flags & F_MINUS) && padd == '0')
{
if (extra_c)
buffer[--padd_start] = extra_c;
return (write(1, &buffer[padd_start], x - padd_start) + write(1, &buffer[ind], length - (1 - padd_start)));
}
}
if (extra_c)
buffer[--ind] = extra_c;
return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - function that writes an unsigned number
 * @is_negative: is The number indicating if the num is negative
 * @ind: is the index at which the number starts in the buffer
 * @buffer: The array of characters
 * @flags: The flags specifiers
 * @width: Width specifier.
 * @precision: is the precision specifier
 * @size: The size specifier
 * Return: Number of written characters.
 */
int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
int length = BUFF_SIZE - ind - 1, x = 0;
char padd = ' ';

UNUSED(is_negative);
UNUSED(size);

if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
return (0);
if (precision > 0 && precision < length)
padd = ' ';

while (precision > length)
{
buffer[--ind] = '0';
length++;
}

if ((flags & F_ZERO) && !(flags & F_MINUS))
padd = '0';

if (width > length)
{
for (x = 0; x < width - length; x++)
buffer[x] = padd;

buffer[x] = '\0';
if (flags & F_MINUS)
{
return (write(1, &buffer[ind], length) + write(1, &buffer[0], x));
}
else
{
return (write(1, &buffer[0], x) + write(1, &buffer[ind], length));
}
}
return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - function that write a memory address
 * @buffer: Arrays of characters
 * @ind: is the index at which the number starts in the buffer
 * @length: the length of number
 * @width: is the width specifier
 * @flags: The flags specifier
 * @padd: The character representing the padding
 * @extra_c: Character representing extra character.
 * @padd_start: is the index at which padding should start
 * Return: Number of written characters
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
int a;
if (width > length)
{
for (a = 3; a < width - length + 3; a++)
buffer[a] = padd;
buffer[a] = '\0';
if (flags & F_MINUS && padd == ' ')
{
buffer[--ind] = 'x';
buffer[--ind] = '0';
if (extra_c)
buffer[--ind] = extra_c;
return (write(1, &buffer[ind], length) + write(1, &buffer[3], a - 3));
}
else if (!(flags & F_MINUS) && padd == ' ')
{
buffer[--ind] = 'x';
buffer[--ind] = '0';
if (extra_c)
buffer[--ind] = extra_c;
return (write(1, &buffer[3], a - 3) + write(1, &buffer[ind], length));
}
else if (!(flags & F_MINUS) && padd == '0')
{
if (extra_c)
buffer[--padd_start] = extra_c;
buffer[1] = '0';
buffer[2] = 'x';
return (write(1, &buffer[padd_start], a - padd_start) +
write(1, &buffer[ind], length - (1 - padd_start) - 2));
}
}
buffer[--ind] = 'x';
buffer[--ind] = '0';
if (extra_c)
buffer[--ind] = extra_c;
return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
