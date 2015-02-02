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

#include <gtk/gtk.h>

#include "ct-main-window.h"
#include "ct-menubar.h"
#include "ct-scrolled-window.h"
#include "ct-treeview.h"

#include "callbacks.h"
#include "ui.h"

/* This function creates the main window of the Cryptus. */
void create_main_window (struct window_main_widgets *wm)
{
	GtkTextBuffer	*buffer;

	gtk_init (NULL, NULL);

	wm->window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (wm->window1), "Cryptus");
	gtk_window_set_position (GTK_WINDOW (wm->window1), GTK_WIN_POS_MOUSE);
	gtk_window_set_default_size (GTK_WINDOW (wm->window1), 600, 400);
	gtk_container_set_border_width (GTK_CONTAINER (wm->window1), 5);
	g_signal_connect (G_OBJECT (wm->window1), "destroy",
			G_CALLBACK (gtk_main_quit), NULL);

	wm->vbox1 = gtk_vbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER (wm->window1), wm->vbox1);

	wm->menubar1 = create_menubar (wm);
	gtk_box_pack_start (GTK_BOX (wm->vbox1), wm->menubar1, FALSE, TRUE, 1);

	wm->vpaned1 = gtk_vpaned_new ();
	gtk_paned_set_position (GTK_PANED (wm->vpaned1), 200);
	gtk_container_add (GTK_CONTAINER (wm->vbox1), wm->vpaned1);

	wm->hpaned1 = gtk_hpaned_new ();
	gtk_paned_set_position (GTK_PANED (wm->hpaned1), 200);
	gtk_container_add (GTK_CONTAINER (wm->vpaned1), wm->hpaned1);

	wm->treeview1 = create_tree_view ();
	wm->scrolled1 = create_scrolled_window_with_viewport (wm->treeview1);
	gtk_container_add (GTK_CONTAINER (wm->hpaned1), wm->scrolled1);

	wm->textview1 = gtk_text_view_new ();
	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (wm->textview1),
			GTK_WRAP_CHAR);

	wm->scrolled2 = create_scrolled_window_with_viewport (wm->textview1);
	gtk_container_add (GTK_CONTAINER (wm->vpaned1), wm->scrolled2);

	wm->textview2 = gtk_text_view_new ();
	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (wm->textview2),
			GTK_WRAP_CHAR );

	wm->scrolled3 = create_scrolled_window_with_viewport (wm->textview2);
	gtk_container_add (GTK_CONTAINER(wm->hpaned1), wm->scrolled3);

	wm->buttonbox1 = gtk_hbutton_box_new ();
	gtk_button_box_set_layout (GTK_BUTTON_BOX (wm->buttonbox1),
			GTK_BUTTONBOX_SPREAD);

	wm->button1 = gtk_button_new_with_label ("Encode");
	gtk_container_add (GTK_CONTAINER (wm->buttonbox1), wm->button1);
	gtk_signal_connect (GTK_OBJECT (wm->button1), "clicked",
			GTK_SIGNAL_FUNC (encode_cb), wm);

	wm->button2 = gtk_button_new_with_label ("Decode");
	gtk_container_add (GTK_CONTAINER (wm->buttonbox1), wm->button2);
	gtk_signal_connect (GTK_OBJECT (wm->button2), "clicked",
			GTK_SIGNAL_FUNC (decode_cb), wm);

	gtk_box_pack_start (GTK_BOX (wm->vbox1), wm->buttonbox1, FALSE, TRUE, 1);

	wm->statusbar1 = gtk_statusbar_new ();
	gtk_box_pack_end (GTK_BOX (wm->vbox1), wm->statusbar1, FALSE, TRUE, 1);

	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (wm->textview2));
	g_signal_connect_object (buffer, "changed",
			GTK_SIGNAL_FUNC (update_document_statistics),
			wm->statusbar1, 0);

	gtk_widget_show_all (wm->window1);
	gtk_main ();
}
