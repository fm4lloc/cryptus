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

#include "utils.h"

/* converts char to wchar_t. */
wchar_t *char_to_wchar (const char* text)
{
	size_t size;
	int requiredSize;
	wchar_t* pwc;

	requiredSize = mbstowcs (NULL, text, 0);
	fprintf (stderr, "char_to_wchar(): required size: %ld\n", (requiredSize + 1) * sizeof( wchar_t ));

	pwc = (wchar_t *) malloc((requiredSize + 1) * sizeof( wchar_t ));
	if (!pwc)
	{
		fprintf (stderr, "Memory allocation failure.\n");
		return NULL;
	}

	size = mbstowcs (pwc, text, requiredSize + 1);
	if (size == (size_t) (-1))
	{
	   fprintf(stderr, "Couldn't convert string--invalid multibyte character.\n");
	   return NULL;
	}

    return pwc;
}

/* converts char to wchar_t. */
char *wchar_to_char (const wchar_t* text)
{
	size_t size;
	int requiredSize;
	char *pc;

	requiredSize = wcstombs (NULL, text, 0);
	fprintf (stderr, "wchar_to_char(): required size: %ld\n", (requiredSize + 1) * sizeof( char ));

	pc = (char *) malloc ((requiredSize + 1) * sizeof( char ));
	if (!pc)
	{
		fprintf (stderr, "Memory allocation failure.\n");
		return NULL;
	}

	size = wcstombs ( pc, text, requiredSize + 1);
	if (size == (size_t) (-1))
	{
	   fprintf (stderr, "Couldn't convert string--invalid multibyte character.\n");
	   return NULL;
	}

    return pc;
}
