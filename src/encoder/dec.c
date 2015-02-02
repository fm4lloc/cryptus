/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 * Author: Fernando Magalhães (Fm4lloc) <fm4lloc@gmail.com>
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>

/*
 * len_ascii_to_dec ()
 * This function returns the required maximum length for encoding.
 *
 * @len: length of the source.
 * @delim_len: length of the delimiter.
 */
size_t len_ascii_to_dec (size_t len, size_t delim_len)
{
	return (len * (3 + delim_len)) + 1;
}

/*
 * len_dec_to_ascii ()
 * This function returns the required maximum length for decoding.
 *
 * @len: length of the source.
 * @delim_len: length of the delimiter.
 */
size_t len_dec_to_ascii (int len, int delim_len)
{
	return (len / (3 + delim_len)) + 1;
}

/* ascii_code_to_str ()
 * Converts ASCII code (0 to 255) to string.
 *
 * @c: the ASCII code (0 to 255)
 *
 * @v: saves the ASCII code converted to string.
 * the maximum size is: 4 * sizeof(char):
 *
 * Explanation of the maximum size:
 * --------------------------------
 * size = strlen("255") + 1;
 *
 * @l: saves the length of the decimal code.
 *
 * Notes:
 * ======
 * This function is adapted from code
 * written by bhuwansahni.
 *
 * Started with:
 * ------------
 * http://stackoverflow.com/questions/9655202/
 *      how-to-convert-integer-to-string-in-c
 *
 */
static void inline ascii_code_to_str (uint8_t c, char v[], int *vl)
{
	char *p = v;
	uint8_t shifter = c;
	static char const digit[] = "0123456789";

	*vl = 0; /* decimal length string */
	do
	{	/* Move to where representation ends */
		++*vl;
		++p;
		shifter /= 10;
	} while (shifter);
	*p = '\0';
	
	do
	{	/* Move back, inserting digits as u go */
		*--p = *digit + c % 10;
		c /= 10;
	} while (c);
}

void ascii_to_dec (char *dest, const char *src, const char *delim)
{
	int vl;
	char value[4];
	char *p = dest;
	int dll = delim ? strlen (delim) : 0;

	for (; *src != '\0'; src++)
	{
		memcpy (p, delim, dll);
		p += dll;

		ascii_code_to_str (*src & 0xff, value, &vl);
		memcpy (p, value, vl + 1);
		p += vl;
	}
}
