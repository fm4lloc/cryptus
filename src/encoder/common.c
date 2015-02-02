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
#include <stdlib.h>
#include <string.h>

#include "hex.h"
#include "dec.h"
#include "base64.h"
#include "hash.h"
#include "common.h"

#define DEBUG (1)

#include <stdio.h>
#include <stdlib.h>

void *mallocx (size_t bytes)
{
	void *ptr = malloc (bytes);
	if (!ptr)
	{
		fprintf (stderr,"mallocx : out memory!\n");
		return NULL;
	}
	return ptr;
}

void *xcalloc (size_t nmemb, size_t size)
{
	void *ptr = calloc (nmemb, size);
	if (!ptr)
	{
		fprintf (stderr,"xcalloc : out memory!\n");
		return NULL;
	}
	return ptr;
}

/* Cryptus easy allocation */
char *halloc (const char *text, const char *delim, hcode code)
{
	void *p;								/* pointer to the allocate memory */
	size_t l = 0;							/* length to allocate */
	size_t lt = text  ? strlen (text)  : 0;	/* length text 		  */
	size_t ld = delim ? strlen (delim) : 0; /* length delimiter   */

	switch (code)
	{
		case HEX_ENCODE: 	 l = len_ascii_to_hex (lt, ld);	break;
		case HEX_DECODE: 	 l = len_hex_to_ascii (lt, ld);	break;
		case DEC_ENCODE: 	 l = len_ascii_to_dec (lt, ld);	break;
		case DEC_DECODE: 	 l = len_dec_to_ascii (lt, ld);	break;
		case BASE64_ENCODE:  l = Base64encode_len (lt);		break;
		case BASE64_DECODE:  l = Base64decode_len (text);	break;
		case HASH_MD5: 		 l = len_hash_md5 ();			break;
		case HASH_SHA256: 	 l = len_hash_sha256 ();		break;
		case HASH_RIPEMD160: l = len_hash_ripemd160 ();		break;
		default:
			break;
	}

#if DEBUG
		fprintf (stderr, "[+] Allocate: %ld\n", (l * sizeof(char)));
#endif

	p = (char *) malloc (sizeof (char) * l);
	if (!p)
	{
		fprintf (stderr, "Out of memory!\n");
		return NULL;
	}
	return p;
}
