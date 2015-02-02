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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"
#include "hex.h"
#include "dec.h"
#include "base64.h"
#include "hash.h"

#include "common.h"

#include "../gui/ct-main-window.h"
#include "../gui/ui.h"

/* Converts plaintext to URL Encoded text */
static void url_uri (char *dest, const char *text)
{
	const char *p = text;
	char *pd = dest;

	for(; *p != '\0'; p++)
	{
		if(*p == 0x20)
			*pd++ = '+';
		/*
		 * unreserved characters
		 * ---------------------------------------------------
		 * A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
		 * a b c d e f g h i j k l m n o p q r s t u v w x y z
		 * 0 1 2 3 4 5 6 7 8 9
		 * - _ . ~
		 * ---------------------------------------------------
		 */
		else if (! ((*p >= 0x41  && *p <= 0x5A) ||
					(*p >= 0x61  && *p <= 0x7A) ||
					(*p >= 0x30  && *p <= 0x39) ||
					(*p == 0x2D  || *p == 0x2E  || *p == 0x5F  || *p == 0x7E)))
		{
			*pd++ = '%';
			*pd++ =  hex_to_char(*p >> 4 & 0xf);
			*pd++ =  hex_to_char(*p      & 0xf);
		}
		else
			*pd++ = *p;
	}
	*pd = '\0';
}

/*
 * encoder_url_uri ()
 *
 * Indices:
 * 	(0) Url(%XX)
 * 	(1) Hex(%XX)
 * 	(2) Unicode(%uUUUU)
 *
 */
void encode_url_uri (const char *text, const gint *idc,
		struct window_main_widgets *wm)
{
	const char *delim[] = {"%", "%", "%u00"}; /* type of delimiter */
	char *dest = NULL;

	/* allocate maximum length */
	dest = halloc (text, delim[idc[1]], HEX_ENCODE);

	switch (idc[1])
	{
		case 0:
			url_uri (dest, text);
			break;

		case 1: case 2:
			ascii_to_hex (dest, text, delim[idc[1]]);
			break;

		default:
			free (dest);
			return;
	}
	set_text_on_text_view (wm->textview1, dest);
	free (dest);
}

static void replace (const char *text, const wchar_t *raw_src,
		const char *repl_src[], struct window_main_widgets *wm)
{
	int i;
	int len;
	wchar_t *p;
	wchar_t *buf;
	gchar ch[MB_CUR_MAX + 1];

	/* convert char to wchar_t */
	buf = char_to_wchar (text);
	p = buf;

	/* clean text view */
	set_text_on_text_view (wm->textview1, NULL);

	for (; *p != '\0'; p++)
	{
		for (i = 0; i < wcslen (raw_src); i++)
		{
			if (*p == raw_src[i])
			{
				insert_text_on_text_view (wm->textview1, repl_src[i]);
				i = 0;
				break;
			}
		}
		if (i)
		{
			len = wctomb (ch, *p);
			ch[len] = '\0';

			insert_text_on_text_view (wm->textview1, ch);
		}
	}
	free (buf);
}

/*
 * encode_html_entity ()
 *
 * Indices:
 * 	(0) Named(&lt)
 * 	(1) Decimal(&#DD)
 * 	(2) Hex(&#\xXX)
 * 	(3) Hex long(&#x00XX)
 *
 */
void encode_html_entity (const char *text, const gint *idc,
		struct window_main_widgets *wm)
{

	if(idc[1] == 0)
	{
		const wchar_t plain[] = L" !\"#$%'()*-./:;<=>?@[\\]_`{|}~ ¡¤¢£¥¦§¨©ª«¬­®¯°±²³´µ¶·¸"
					"¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîï"
					"ðñòóôõö÷øùúûüýþÿŒœŠšŸˆ   –—‘’‚“”„†‡…‰‹›€™+,&";

		const char *html[] =
		{
			"&sp","&excl","&quot","&num","&dollar","&percnt","&apos","&lpar","&rpar","&ast",
			"&hyphen","&period","&sol","&colon","&semi","&lt","&equals","&gt","&quest",
			"&commat","&lsqb","&bsol","&rsqb","&lowbar","&grave","&lcub","&verbar","&rcub",
			"&tilde","&nbsp","&iexcl","&curren","&cent","&pound","&yen","&brvbar","&sect","&uml",
			"&copy","&ordf","&laquo","&not","&shy","&reg","&macr","&deg","&plusmn","&sup2","&sup3",
			"&acute","&micro","&para","&middot","&cedil","&sup1","&ordm","&raquo","&frac14","&frac12",
			"&frac34","&iquest","&Agrave","&Aacute","&Acirc","&Atilde","&Auml","&Aring","&AElig","&Ccedil",
			"&Egrave","&Eacute","&Ecirc","&Euml","&Igrave","&Iacute","&Icirc","&Iuml","&ETH",
			"&Ntilde","&Ograve","&Oacute","&Ocirc","&Otilde","&Ouml","&times","&Oslash","&Ugrave",
			"&Uacute","&Ucirc","&Uuml","&Yacute","&THORN","&szlig","&agrave","&aacute","&acirc",
			"&atilde","&auml","&aring","&aelig","&ccedil","&egrave","&eacute","&ecirc","&euml",
			"&igrave","&iacute","&icirc","&iuml","&eth","&ntilde","&ograve","&oacute","&ocirc",
			"&otilde","&ouml","&divide","&oslash","&ugrave","&uacute","&ucirc","&uuml","&yacute",
			"&thorn","&yuml","&OElig","&oelig","&Scaron","&scaron","&Yuml","&circ",
			"&ensp","&emsp","&thinsp","&ndash","&mdash","&lsquo","&rsquo","&sbquo","&ldquo",
			"&rdquo","&bdquo","&dagger","&Dagger","&hellip","&permil","&lsaquo","&rsaquo",
			"&euro","&trade","&plus","&comma","&amp"
		};

		replace (text, plain, html, wm);
		return;
	}

	char *dest = NULL;
	const char *delim[] = {NULL, "&#", "&#x", "&#x00"}; /* type of delimiter */

	switch (idc[1])
	{
		case 1:
			dest = halloc (text, delim[idc[1]], DEC_ENCODE);
			ascii_to_dec (dest, text, delim[idc[1]]);
			break;

		case 2: case 3:
			dest = halloc (text, delim[idc[1]], HEX_ENCODE);
			ascii_to_hex (dest, text, delim[idc[1]]);
			break;

		default:
			return;
	}

	set_text_on_text_view (wm->textview1, dest);
	free (dest);
}

/*
 * encoded_special ()
 *
 * Indices:
 * 	(0) JavaScript escaped
 * 	(1) XML escaped
 *
 */
void encoded_special (const char *text, const gint *idc,
		struct window_main_widgets *wm)
{
	if (idc[1] == 0)
	{
		const wchar_t plain[]	 = L"\\'\"\t\n";
		const char *escaped[] 	 = {"\\\\", "\\'", "\\\"", "\\t", "\\n"};

		replace (text, plain, escaped, wm);
	}
	else if (idc[1] == 1)
	{
		const wchar_t plain[]	 = L"&<>'\"";
		const char *escaped[] = {"&amp;", "&lt;", "&gt;", "&apos;", "&quot;"};

		replace (text, plain, escaped, wm);
	}
}

/*
 * straigtht_encoding ()
 *
 * Indices:
 * 	(0) Decimal(DD)
 * 	(1) Hex(XX)
 *
 */
void straigtht_encoding (const char *text, const gint *idc,
		struct window_main_widgets *wm)
{
	char *dest = NULL;

	hcode hc[] = {DEC_ENCODE, HEX_ENCODE};
	dest = halloc (text, " ", hc[idc[1]]);

	switch (idc[1])
	{
		case 0:
			ascii_to_dec (dest, text, " ");
			break;

		case 1:
			ascii_to_hex (dest, text, " ");
			break;

		default:
			free (dest);
			return;
	}

	set_text_on_text_view (wm->textview1, dest);
	free (dest);
}

/*
 * ie_specific ()
 *
 * Indices:
 *  (0) (\\xXX)
 * 	(1) (\\x0XX)
 * 	(2) (\\x00XX)
 * 	(3) (\\x000XX)
 * 	(4) (\\x0000XX)
 * 	(5) (\\x00000XX)
 * 	(6) (\\uUUUU)
 *
 */
void ie_specific (const char *text, const gint *idc,
		struct window_main_widgets *wm)
{
	char *dest = NULL;
	const char *delim[] =
	{		"\\x",
			"\\x0",
			"\\x00",
			"\\x000",
			"\\x0000",
			"\\x00000",
			"\\u00"
	};

	dest = halloc (text,  delim[idc[1]], HEX_ENCODE);
	ascii_to_hex (dest, text, delim[idc[1]]);

	set_text_on_text_view (wm->textview1, dest);
	free (dest);
}

/*
 * hash ()
 *
 * Indices:
 *  (0) Base64
 * 	(1) MD5
 * 	(2) SHA-256
 * 	(3) RIPEMD160
 *
 */
void hash (const char *text, const gint *idc,
		struct window_main_widgets *wm)
{
	char *dest = NULL;
	hcode hc[] = {BASE64_ENCODE, HASH_MD5, HASH_SHA256, HASH_RIPEMD160};

	dest = halloc (text, NULL, hc[idc[1]]);
	dest[0] = '\0';

	switch (idc[1])
	{
		case 0:
			Base64encode (dest, text, strlen (text));
			break;

		case 1:
			hash_md5 (dest, text);
			break;

		case 2:
			hash_sha256 (dest, text);
			break;

		case 3:
			hash_ripemd160 (dest, text);
			break;

		default:
			free (dest);
			return;
	}

	set_text_on_text_view (wm->textview1, dest);
	free (dest);
}
