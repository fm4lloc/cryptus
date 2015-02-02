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

#include <stdarg.h>
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

/* This should be freed using g_object_unref() */
GdkPixbuf *pixbuf_new_from_file (const gchar *filename)
{
	GdkPixbuf	*pixbuf;
	GError		*error = NULL;

	pixbuf = gdk_pixbuf_new_from_file (filename, &error);
	if (!pixbuf)
	{
		g_warning ("Can't creates a new pixbuf from a file - %s\n", error->message);
		g_clear_error (&error);
		return NULL;
	}

	return pixbuf;
}

void set_text_on_statusbar (GtkWidget *statusbar, const gchar *format, ...)
{
	va_list ap;
	gchar str[256];

	va_start (ap, format);
	vsnprintf (str, sizeof (str), format, ap);
	va_end (ap);

	/* clear any previous message, underflow is allowed */
	gtk_statusbar_pop (GTK_STATUSBAR (statusbar), 0);
	gtk_statusbar_push (GTK_STATUSBAR (statusbar), 0, str);
}

/* Updates the status bar document statistics */
void update_document_statistics (GtkTextBuffer *buffer, GtkWidget *statusbar)
{
	gint row;
	gint col;
	gint count;
	GtkTextIter iter;

	count = gtk_text_buffer_get_char_count (buffer);

	gtk_text_buffer_get_iter_at_mark (buffer, &iter,
			gtk_text_buffer_get_insert (buffer));

	row = gtk_text_iter_get_line (&iter);
	col = gtk_text_iter_get_line_offset (&iter);

	set_text_on_statusbar (statusbar, "Cursor at row %d column %d - %d chars in document",
			row, col, count);
}

/* This value should be freed using g_free */
gchar *get_text_from_text_view (GtkWidget *textview)
{
	GtkTextBuffer *buffer;
	GtkTextIter start;
	GtkTextIter end;

	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (textview));

	gtk_text_buffer_get_start_iter (buffer, &start);
	gtk_text_buffer_get_end_iter (buffer, &end);

	return gtk_text_buffer_get_text (buffer, &start, &end, FALSE);
}

void set_text_on_text_view (GtkWidget *textview, const gchar *text)
{
	GtkTextBuffer *buffer;

	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (textview));
	gtk_text_buffer_set_text (buffer, text ? text : "", -1);
}

/*
 * Insert text at the end of the buffer..
 * Is not the best option to use in large loops.
 */
inline void insert_text_on_text_view (GtkWidget *textview, const gchar *text)
{
	GtkTextBuffer *buffer;
	GtkTextIter end;

	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textview));
	gtk_text_buffer_get_end_iter (buffer, &end);

	gtk_text_buffer_insert (buffer, &end, text ? text : "", -1);
}

/*
 * Returns the current indices of path selected in tree view.
 * The value returned should be freed using g_free
 *
 * @treeview: A GtkWidget of tree view.
 * @depth: Number of elements returned in the integer array;
 *
 */
gint *get_tree_view_path_selected (GtkWidget *treeview, gint *depth)
{
	GtkTreeIter iter;
	GtkTreeModel *model;
	GtkTreeSelection *selection;

	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (treeview));

	if (gtk_tree_selection_get_selected (GTK_TREE_SELECTION (selection),
			&model, &iter))
	{
		GtkTreePath *path = gtk_tree_model_get_path (model, &iter);
		gint *temp = gtk_tree_path_get_indices_with_depth (path, depth);
		gint *indices = (gint *) g_memdup (temp, sizeof (gint) * (*depth));

		gtk_tree_path_free (path);

		return indices;
	}

	return NULL;
}
