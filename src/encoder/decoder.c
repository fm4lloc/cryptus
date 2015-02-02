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
#include <stdlib.h>

#include "utils.h"
#include "hex.h"
#include "dec.h"
#include "base64.h"
#include "hash.h"

#include "common.h"

#include "../gui/ct-main-window.h"
#include "../gui/ui.h"

/*
 * encoder_url_uri ()
 *
 * Indices:
 * 	(0) Url(%XX)
 * 	(1) Hex(%XX)
 * 	(2) Unicode(%uUUUU)
 *
 */
void decode_url_uri (const char *text, const gint *idc,
		struct window_main_widgets *wm)
{
	const char *delim[] = {"%", "%", "%u00"}; /* type of delimiter */
	char *dest = NULL;

	/* allocate maximum length */
	dest = halloc (text, delim[idc[1]], HEX_DECODE);

	switch (idc[1])
	{
		case 0:
			/* faltando decoder */
			break;

		case 1: case 2:
			hex_to_ascii (dest, text, delim[idc[1]]);
			break;

		default:
			free (dest);
			return;
	}
	set_text_on_text_view (wm->textview2, dest);
	free (dest);
}
