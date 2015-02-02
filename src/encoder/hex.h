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

#ifndef HEX_H_
#define HEX_H_

#include <stddef.h> /* size_t */
#include <stdint.h>

inline const char hex_to_char (uint8_t d);
inline int char_to_hex (int c);

size_t len_ascii_to_hex (int len, int delim_len);
size_t len_hex_to_ascii (int len, int delim_len);

void ascii_to_hex (char *dest, const char *src, const char *delim);
void hex_to_ascii (char *dest, const char *src, const char *delim);

#endif /* HEX_H_ */
