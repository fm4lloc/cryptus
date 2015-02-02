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

#include "../encoder/encoder.h"
#include "../encoder/decoder.h"
#include "ct-treeview.h"
#include "ui.h"

/* Debug time  */
#define TIME_MSG (1)

#if TIME_MSG
	#include <sys/types.h>
	#include <time.h>
	#include "ui.h"
#endif

/* encode button */
void encode_cb (GtkWidget *widget, struct window_main_widgets *wm)
{
	gint depth;
	gint *idc;
	gchar *text;

	idc = get_tree_view_path_selected (wm->treeview1, &depth);
	if(!idc)
		return;

	text = get_text_from_text_view (wm->textview2);
	if (!text || !text[0])
	{
		g_free (idc);
		return;
	}

#if TIME_MSG
	clock_t start_time;
	clock_t final_time;

	start_time = clock ();
#endif

	switch (idc[0])
	{
		case URL_URI: 		encode_url_uri (text, idc, wm);		break;
		case HTML_ENTITY: 	encode_html_entity (text, idc, wm);	break;
		case SPECIAL_ENCODING:	encoded_special (text, idc, wm);	break;
		case STRAIGHT_ENCODING:	straigtht_encoding (text, idc, wm);	break;
		case IE_SPECIFIC:	ie_specific (text, idc, wm);		break;
		case IP_SPECIFIC: 											break;
		case HASH:		hash (text, idc, wm);			break;
		case OTHERS:												break;
		case SPECIAL:												break;
		default:
			break;
	}

#if TIME_MSG
	final_time = clock ();
	set_text_on_statusbar (wm->statusbar1, "Encoder time: %f milliseconds",
			((double) final_time - start_time) / CLOCKS_PER_SEC);
#endif

	g_free (idc);
	g_free (text);
}

/* decode button */
void decode_cb (GtkWidget *widget, struct window_main_widgets *wm)
{
	gint depth;
	gint *idc;
	gchar *text;

	idc = get_tree_view_path_selected (wm->treeview1, &depth);
	if(!idc)
		return;

	text = get_text_from_text_view (wm->textview1);
	if (!text || !text[0])
	{
		g_free (idc);
		return;
	}

#if TIME_MSG
	clock_t start_time;
	clock_t final_time;

	start_time = clock ();
#endif

	switch (idc[0])
	{
		case URL_URI: 		decode_url_uri (text, idc, wm);		break;
		case HTML_ENTITY: 	break;
		case SPECIAL_ENCODING:	break;
		case STRAIGHT_ENCODING:	break;
		case IE_SPECIFIC:	break;
		case IP_SPECIFIC: 	break;
		case HASH:		break;
		case OTHERS:		break;
		case SPECIAL:		break;
		default:
			break;
	}

#if TIME_MSG
	final_time = clock ();
	set_text_on_statusbar (wm->statusbar1, "Encoder time: %f milliseconds",
			((double) final_time - start_time) / CLOCKS_PER_SEC);
#endif
	g_free (idc);
	g_free (text);
}

static GtkResponseType check_if_overwriting_file (GtkWidget *window_parent,
		const gchar *filename)
{
  if (*filename && g_file_test (filename, G_FILE_TEST_EXISTS))
  {
	GtkWidget *dialog;
	gboolean resp;
	gchar *filename_in_utf8 = g_filename_to_utf8 (filename, -1,
						  NULL, NULL, NULL);

	const gchar hint[] =
			"Note that all information in the existing file "
			"will be lost permanently if you choose to overwrite it.";

	const gchar message_format_string[] =
			"File named '%s' already exists."
			"\nDo you want to overwrite it with the one you are saving?";

	dialog = gtk_message_dialog_new (GTK_WINDOW (window_parent),
								   GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
								   GTK_MESSAGE_WARNING,
								   GTK_BUTTONS_OK_CANCEL,
								   hint);

	gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_MOUSE);
	gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog),
			message_format_string, filename_in_utf8);

	g_free (filename_in_utf8);

	resp = gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);

	return resp;
  }

  return GTK_RESPONSE_CANCEL;
}

void open_cb (GtkAction *action, gpointer user_data)
{
	GtkWidget			*dialog;
	GtkResponseType		resp;
	gchar 				*filename;
	gchar 				*content;
	GtkTextBuffer 		*buffer;
	GError 				*error = NULL;
	struct window_main_widgets *wm;

	wm = (struct window_main_widgets *) user_data;

	dialog = gtk_file_chooser_dialog_new ("Select a file to open",
			 GTK_WINDOW(wm->window1),
			 GTK_FILE_CHOOSER_ACTION_OPEN,
			 GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
			 GTK_STOCK_OPEN, GTK_RESPONSE_OK,
			 NULL);

	gtk_window_set_modal (GTK_WINDOW(dialog), TRUE);
	gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_MOUSE);

	resp = gtk_dialog_run (GTK_DIALOG(dialog));
	if (resp == GTK_RESPONSE_OK)
	{
		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
		if(filename)
		{
			if (!g_file_get_contents (filename, &content, NULL, &error))
			{
				set_text_on_statusbar (wm->statusbar1, error->message);
				g_clear_error (&error);
			}
			else
			{
				buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (wm->textview2));
				gtk_text_buffer_set_text (buffer, content, -1);
				gtk_window_set_title (GTK_WINDOW (wm->window1), filename);
				g_free (content);
			}
			g_free (filename);
		}
	}
	gtk_widget_destroy(dialog);
}

void save_as_cb (GtkAction *action, gpointer user_data)
{
	GtkWidget 		*dialog;
	GtkResponseType	resp;
	gchar 			*filename	= NULL;
	gchar			*text		= NULL;
	GError			*error		= NULL;
	struct window_main_widgets *wm;

	wm = (struct window_main_widgets *) user_data;

	dialog = gtk_file_chooser_dialog_new ("Save File As ...",
			GTK_WINDOW(wm->window1),
			GTK_FILE_CHOOSER_ACTION_SAVE,
			GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
			GTK_STOCK_SAVE, GTK_RESPONSE_OK,
			NULL);

	gtk_window_set_modal (GTK_WINDOW(dialog), TRUE);
	gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_MOUSE);

	resp = gtk_dialog_run (GTK_DIALOG (dialog));
	if (resp == GTK_RESPONSE_OK)
	{
		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
		resp = check_if_overwriting_file (dialog, filename);
		if (resp == GTK_RESPONSE_OK)
		{
			text = get_text_from_text_view (wm->textview1);
			if (!g_file_set_contents (filename, text, -1, &error))
			{
				set_text_on_statusbar (wm->statusbar1, error->message);
				g_clear_error (&error);
			}
			g_free (text);
		}
		g_free (filename);
	}
	gtk_widget_destroy (dialog);
}

void about_cb (GtkAction *action, gpointer user_data)
{
	struct window_main_widgets *wm = (struct window_main_widgets *) user_data;
	GdkPixbuf *logo = pixbuf_new_from_file("img/logo.png");

	const gchar *authors[] = {
		"Fernando Magalhães (Fm4lloc) <fm4lloc@gmail.com>",
		NULL
	};

	const gchar license[] =
			"Copyright (C) 2014  Fernando Magalhães (Fm4lloc) <fm4lloc@gmail.com>\n"
			"\n"
			"This program is free software: you can redistribute it and/or modify\n"
			"it under the terms of the GNU General Public License as published by\n"
			"the Free Software Foundation, either version 3 of the License, or\n"
			"(at your option) any later version.\n"
			"\n"
			"This program is distributed in the hope that it will be useful,\n"
			"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
			"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
			"GNU General Public License for more details.\n"
			"\n"
			"You should have received a copy of the GNU General Public License\n"
			"along with this program.  If not, see <http://www.gnu.org/licenses/>.";

	const gchar copyright[] = "Copyright \xc2\xa9 2014\nFernando Magalhães (Fm4lloc)";

	gtk_show_about_dialog (GTK_WINDOW 		(wm->window1),
	                       "authors",		authors,
	                       "comments",		"A simple encoder in C",
	                       "copyright",		copyright,
	                       "license",		license,
	                       "logo",			logo,
	                       "program-name",	"Cryptus",
	                       "title",			"About Cryptus",
	                       "version",		"1.0.0",
	                       "website",		"http://fm4lloc.wordpress.com/cryptus",
	                       "website-label",	"Cryptus Website",
	                       "wrap-license",	FALSE,
	                       "modal",			TRUE,
	                       NULL);

	g_object_unref (logo), logo = NULL;
}
