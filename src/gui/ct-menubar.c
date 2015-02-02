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

#include "ct-menubar.h"
#include "callbacks.h"

//#include <gio/gio.h>
//#include <glib/gi18n.h>

static const GtkActionEntry entries[] =
{
	{ "FileMenu", NULL, "_File" }		/* name, stock id, label */
	{ "PreferencesMenu", NULL, "_Preferences" },
	{ "HelpMenu", NULL, "_Help" },

	{ "Open", GTK_STOCK_OPEN,		/* name, stock id */
			"_Open", "<control>O",	/* label, accelerator */
			"Open a file",		/* tooltip */
	G_CALLBACK (open_cb) },			/* callback */
	{ "SaveAs", GTK_STOCK_SAVE,
			"Save _As...", NULL,
			"Save to a file",
			G_CALLBACK (save_as_cb) },
	{ "Quit", GTK_STOCK_QUIT,
			"_Quit", "<control>Q",
			"Quit",
			G_CALLBACK (gtk_main_quit) },
	{ "About", GTK_STOCK_ABOUT,
			"_About", "F1",
			"About",
			G_CALLBACK (about_cb) },
};

static const gchar *ui_info =
"<ui>"
"  <menubar name='MainMenu'>"
"    <menu action='FileMenu'>"
"      <menuitem action='Open'/>"
"      <menuitem action='SaveAs'/>"
"      <separator/>"
"      <menuitem action='Quit'/>"
"    </menu>"
"    <menu action='PreferencesMenu'/>"
"    <menu action='HelpMenu'>"
"      <menuitem action='About'/>"
"    </menu>"
"  </menubar>"
"</ui>";

GtkWidget *create_menubar (struct window_main_widgets *wm)
{
	GtkUIManager	*merge;
	GtkActionGroup	*action_group;
	GError 			*error = NULL;
	gint 			n_entries = G_N_ELEMENTS (entries);

	action_group = gtk_action_group_new ("CryptusActions");
	//gtk_action_group_set_translation_domain (action_group, GETTEXT_PACKAGE);
	gtk_action_group_add_actions (action_group, entries, n_entries, wm);

	merge = gtk_ui_manager_new ();

	g_object_set_data_full (G_OBJECT (wm->window1), "ui-manager", merge,
			g_object_unref);
	gtk_ui_manager_insert_action_group (merge, action_group, 0);
	gtk_window_add_accel_group (GTK_WINDOW (wm->window1),
			gtk_ui_manager_get_accel_group (merge));

	/* load menu description from resources */
	if (!gtk_ui_manager_add_ui_from_string (merge, ui_info, -1, &error))
	{
		g_critical ("%s\n", error->message);
		g_clear_error (&error);
		return NULL;
	}

    return gtk_ui_manager_get_widget (merge, "/MainMenu");
}
