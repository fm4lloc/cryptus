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

#ifndef CT_MAIN_WINDOW_H_
#define CT_MAIN_WINDOW_H_

#include <gtk/gtk.h>

/**
 * Structure for the widgets in the main window.
 */
struct window_main_widgets
{
	GtkWidget	*window1;
	GtkWidget	*vbox1;
	GtkWidget	*menubar1;
	GtkWidget	*vpaned1;
	GtkWidget	*hpaned1;
	GtkWidge	*scrolled1;
	GtkWidget	*scrolled2;
	GtkWidget	*scrolled3;
	GtkWidget	*treeview1;
	GtkWidget	*textview1;
	GtkWidget	*textview2;
	GtkWidget	*buttonbox1;
	GtkWidget	*button1;
	GtkWidget	*button2;
	GtkWidget	*statusbar1;
};

/**
 * create_main_window()
 * 
 * This function creates and configures
 * the components of the main program interface.
 *
 * @struct window_main_widgets *wmain: Pointer to
 * the structure that holds the components of the
 * main interface.
 *
 */
void create_main_window (struct window_main_widgets *wmain);

#endif /* CT_MAIN_WINDOW_H_ */
