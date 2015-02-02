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

#include "ct-treeview.h"
#include "ct-scrolled-window.h"

#include <glib-object.h> /* G_TYPE_STRING */

enum
{
	ITEM = 0,
	COLUMNS
};

enum
{
	ITEM_CATEGORY = 0,
	ITEM_CHILD
};

typedef struct
{
	gint item_type;
	gchar *item;
} GroceryItem;

const GroceryItem list[] =
{
	{ ITEM_CATEGORY, 	"URL/URI" 					}, /* 0   */
		{ ITEM_CHILD, 		"Url(%XX)" 				}, /* 0:0 */
		{ ITEM_CHILD, 		"Hex(%XX)" 				}, /* 0:1 */
		{ ITEM_CHILD, 		"Unicode(%uUUUU)" 		}, /* 0:2 */

	{ ITEM_CATEGORY, 	"HTML-ENTITY" 				}, /* 1   */
		{ ITEM_CHILD, 		"Named(&lt)" 			}, /* 1:0 */
		{ ITEM_CHILD, 		"Decimal(&#DD)" 		}, /* 1:1 */
		{ ITEM_CHILD, 		"Hex(&#xXX)" 			}, /* 1:2 */
		{ ITEM_CHILD, 		"Hex long(&#x00XX)" 	}, /* 1:3 */

	{ ITEM_CATEGORY, 	"SPECIAL ENCODING" 			}, /* 2   */
		{ ITEM_CHILD, 		"JavaScript escaped"	}, /* 2:0 */
		{ ITEM_CHILD, 		"XML escaped" 			}, /* 2:1 */

	{ ITEM_CATEGORY, 	"Straight Encoding" 		}, /* 3	  */
		{ ITEM_CHILD, 		"Decimal(DD)" 			}, /* 3:0 */
		{ ITEM_CHILD, 		"Hex(XX)" 				}, /* 3:1 */

	{ ITEM_CATEGORY, 	"IE Specific"				}, /* 4   */
		{ ITEM_CHILD, 		"(\\xXX)" 				}, /* 4:0 */
		{ ITEM_CHILD, 		"(\\x0XX)" 				}, /* 4:1 */
		{ ITEM_CHILD, 		"(\\x00XX)" 			}, /* 4:2 */
		{ ITEM_CHILD, 		"(\\x000XX)" 			}, /* 4:3 */
		{ ITEM_CHILD, 		"(\\x0000XX)" 			}, /* 4:4 */
		{ ITEM_CHILD, 		"(\\x00000XX)" 			}, /* 4:5 */
		{ ITEM_CHILD, 		"(\\uUUUU)" 			}, /* 4:6 */

	{ ITEM_CATEGORY, 	"IP Specific"				}, /* 5   */
		{ ITEM_CHILD, 		"Hex Address (IPv4)" 	}, /* 5:0 */
		{ ITEM_CHILD, 		"(Octal (IPv4)" 		}, /* 5:1 */
		{ ITEM_CHILD, 		"Dword Address (IPv4)" 	}, /* 5:2 */

	{ ITEM_CATEGORY, 	"Hash"	}, 					   /* 6   */
		{ ITEM_CHILD, 		"Base64" 				}, /* 6:0 */
		{ ITEM_CHILD, 		"MD5" 					}, /* 6:1 */
		{ ITEM_CHILD, 		"SHA-256" 				}, /* 6:2 */
		{ ITEM_CHILD, 		"RIPEMD160" 			}, /* 6:3 */

	{ ITEM_CATEGORY, 	"Others"					}, /* 7   */
		{ ITEM_CHILD, 		"Split (delimiter)" 	}, /* 7:0 */
		{ ITEM_CHILD, 		"Split (Space)" 		}, /* 7:1 */
		{ ITEM_CHILD, 		"Reverse string" 		}, /* 7:2 */
		{ ITEM_CHILD, 		"Join" 					}, /* 7:3 */
		{ ITEM_CHILD, 		"International Morse" 	}, /* 7:4 */
		{ ITEM_CHILD, 		"13375p34k - Simple" 	}, /* 7:5 */
		{ ITEM_CHILD, 		"13375p34k - Advanced" 	}, /* 7:6 */
		{ ITEM_CHILD, 		"Binary" 				}, /* 7:7 */
		{ ITEM_CHILD, 		"BCD (int)" 			}, /* 7:8 */
		{ ITEM_CHILD, 		"Replace" 				}, /* 7:9 */
		{ ITEM_CHILD, 		"Up Case" 				}, /* 7:10*/
		{ ITEM_CHILD, 		"Low Case" 				}, /* 7:11*/
		{ ITEM_CHILD, 		"String length" 		}, /* 7:12*/

	{ ITEM_CATEGORY, 		"Special"				}, /* 8   */
		{ ITEM_CHILD, 		"Password generator"	}, /* 8:0 */

	{ ITEM_CATEGORY,		NULL 					}, /* NULL */
};

static void setup_tree_view (GtkWidget *treeview)
{
	GtkCellRenderer 	*renderer;
	GtkTreeViewColumn	*column;

	/* Create a new GtkCellRendererText, add it to the tree view column and
	 * append the column to the tree view. */
	renderer = gtk_cell_renderer_text_new ();

	column = gtk_tree_view_column_new_with_attributes
			("encoder options", renderer,
			 "text", ITEM,
			 NULL);

	gtk_tree_view_append_column (GTK_TREE_VIEW (treeview), column);
}

/* Create a tree view to the main window. */
GtkWidget *create_tree_view ()
{
	GtkWidget *treeview;
	GtkTreeStore *store;
	GtkTreeIter iter;
	GtkTreeIter child;
	guint i = 0;

	treeview = gtk_tree_view_new ();
	setup_tree_view (treeview);

	store = gtk_tree_store_new (COLUMNS, 		/* Total number of columns */
								G_TYPE_STRING);	/* options */

	while (list[i].item != NULL)
	{
		/* If the item type is a category, count the quantity of all of the items
		 * in the category that are going to be bought. */
		if (list[i].item_type == ITEM_CATEGORY)
		{
			/* Add the category as a new root element. */
			gtk_tree_store_append (store, &iter, NULL);
			gtk_tree_store_set (store, &iter, ITEM, list[i].item, -1);
		}
		/* Otherwise, add the item as a child of the category. */
		else
		{
			gtk_tree_store_append (store, &child, &iter);
			gtk_tree_store_set (store, &child, ITEM, list[i].item, -1);
		}
		i++;
	}

	gtk_tree_view_set_model (GTK_TREE_VIEW (treeview), GTK_TREE_MODEL (store));
	gtk_tree_view_expand_all (GTK_TREE_VIEW (treeview));
	g_object_unref (store);

	return treeview;
}
