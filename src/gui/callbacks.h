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

#ifndef CALLBACKS_H_
#define CALLBACKS_H_

#include "ct-main-window.h"

/* buttons clicked */
void encode_cb (GtkWidget *widget, struct window_main_widgets *wm);
void decode_cb (GtkWidget *widget, struct window_main_widgets *wm);

/* main menu */
void open_cb (GtkAction *action, gpointer user_data);
void save_as_cb (GtkAction *action, gpointer user_data);
void about_cb (GtkAction *action, gpointer user_data);

#endif /* CALLBACKS_H_ */
