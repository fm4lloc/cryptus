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

#ifndef ENCODER_H_
#define ENCODER_H_

#include <string.h>
#include <stdint.h>

#include "../gui/ct-main-window.h"

void encode_url_uri (const gchar *text, const gint *idc,
		struct window_main_widgets *wm);

void encode_html_entity (const char *text, const gint *idc,
		struct window_main_widgets *wm);

void encoded_special (const char *text, const gint *idc,
		struct window_main_widgets *wm);

void straigtht_encoding (const char *text, const gint *idc,
		struct window_main_widgets *wm);

void ie_specific (const char *text, const gint *idc,
		struct window_main_widgets *wm);

void hash (const char *text, const gint *idc,
		struct window_main_widgets *wm);

#endif /* ENCODER_H_ */
