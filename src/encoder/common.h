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

#ifndef COMMON_H_
#define COMMON_H_

/* memory code */
typedef enum
{
	HEX_ENCODE = 0,
	HEX_DECODE,
	DEC_ENCODE,
	DEC_DECODE,
	BASE64_ENCODE,
	BASE64_DECODE,
	HASH_MD5,
	HASH_SHA256,
	HASH_RIPEMD160
} hcode;

void *mallocx (size_t bytes);
void *xcalloc (size_t nmemb, size_t size);
char *halloc  (const char *text, const char *delim, hcode code);

#endif /* COMMON_H_ */
