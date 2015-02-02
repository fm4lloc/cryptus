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

#ifndef UI_H_
#define UI_H_

#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gtk/gtk.h>

/* This should be freed using g_object_unref() */
GdkPixbuf *pixbuf_new_from_file (const gchar *filename);

void set_text_on_statusbar (GtkWidget  *statusbar, const gchar *format, ...);
/* updates the status bar document statistics */
void update_document_statistics (GtkTextBuffer *buffer, GtkWidget *statusbar);

/* This value should be freed using g_free */
gchar *get_text_from_text_view (GtkWidget *textview);
/* Delete whole buffer, then insert */
void set_text_on_text_view (GtkWidget *textview, const gchar *text);
/* Insert into the buffer */
inline void insert_text_on_text_view (GtkWidget *textview, const gchar *text);

/* This value should be freed using g_free */
gint *get_tree_view_path_selected (GtkWidget *treeview, gint *depth);

#endif /* UI_H_ */
