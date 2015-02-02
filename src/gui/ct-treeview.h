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

#ifndef CT_TREEVIEW_H_
#define CT_TREEVIEW_H_

#include <gtk/gtk.h>

/* Categories */
enum
{
	URL_URI = 0,
	HTML_ENTITY,
	SPECIAL_ENCODING,
	STRAIGHT_ENCODING,
	IE_SPECIFIC,
	IP_SPECIFIC,
	HASH,
	OTHERS,
	SPECIAL
};

/* Returns a treeview to the main window. */
GtkWidget *create_tree_view ();

#endif /* CT_TREEVIEW_H_ */
