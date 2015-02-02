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
#include <stdint.h> /* uint8_t */

/* low-level */

/*
 * @param[in] d  A hexadecimal digit. Any non-hex digit returns a NULL char
 */
inline const char hex_to_char (uint8_t d)
{
	static const char map[] = "0123456789ABCDEF"
	                         "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	                         "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	                         "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	                         "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	                         "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	                         "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	                         "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	                         "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	                         "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	                         "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	                         "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	                         "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	                         "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	                         "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	                         "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
	return map[d];
}

inline int char_to_hex (int c)
{
	return ((c >= 'a') && (c <= 'f')) ? c - 'a' + 10 :
	       ((c >= '0') && (c <= '9')) ? c - '0' :
	       ((c >= 'A') && (c <= 'F')) ? c - 'A' + 10 : -1;
}

/*
 * len_ascii2hex ()
 * This function returns the required maximum length for encoding
 *
 * @len: length of the source.
 * @delim_len: length of the delimiter.
 */
size_t len_ascii_to_hex (int len, int delim_len)
{
    return (len * (2 + delim_len)) + 1;
}

/*
 * len_hex2ascii ()
 * This function returns the required maximum length for decoding
 *
 * @len: length of the source.
 * @delim_len: length of the delimiter.
 */
size_t len_hex_to_ascii (int len, int delim_len)
{
    return (len / (2 + delim_len)) + 1;
}

/*
void ascii_2_hex (char *dest, const char *src, const char *delim)
{
	int i;
	int j = 0;
	int len = delim ? strlen (delim) : 0;

	// Step through converting the source string
	for (i = 0; *(src + i) != '\0'; i++)
	{
		memcpy (dest + i * 2 + j, delim, len);
		j += len;
		*(dest + i * 2 + j)     = hex_to_char (*(src + i) >> 4 & 0xf);
		*(dest + i * 2 + 1 + j) = hex_to_char (*(src + i)      & 0xf);
	}
	*(dest + i * 2 + j) = '\0';
}
*/

/* Convert ASCII string to hexadecimal */
void ascii_to_hex (char *dest, const char *src, const char *delim)
{
	int i;
	int j = 0;
	int len = delim ? strlen (delim) : 0;

	/* Step through converting the source string */
	for (i = 0; src[i] != '\0'; i++)
	{
		memcpy (dest + i * 2 + j, delim, len);
		j += len;
		dest[i * 2 + j]     = hex_to_char (src[i] >> 4 & 0xf);
		dest[i * 2 + 1 + j] = hex_to_char (src[i]      & 0xf);
	}
	dest[i * 2 + j] = '\0';
}

/* Convert hexadecimal string to ASCII */
void hex_to_ascii (char *dest, const char *src, const char *delim)
{
	int i;
	int j = 0;
	int len = delim ? strlen (delim) : 0;

	dest[0] = '\0';
	/* Step through conversing the source hex digit pairs */
	for (i = 0; src[i * 2 + j] != '\0' && src[i * 2 + 1 + j] != '\0'; i++)
	{
		//fprintf (stderr, ">>: '%c'\n", src[i - j]);
		//fprintf (stderr, ">>: '%c'\n", src+i-j);

		if ((memcmp (src+i-j, delim, (size_t) len)) == 0)
		{
			fprintf (stderr, "%.*s\n", len, src+i-j);
			j += len;
			dest[i] = ((char_to_hex (src[i * 2 + j])     & 0xf) << 4)
					  |(char_to_hex (src[i * 2 + j + 1]) & 0xf);
		}

	}
	dest[i] = '\0';
}
