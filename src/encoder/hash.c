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

#include <openssl/md5.h>
#include <openssl/sha.h>
#include <openssl/ripemd.h>

unsigned short int len_hash_md5 ()
{
	return MD5_DIGEST_LENGTH * 2 + 1;
}

unsigned short int len_hash_sha256 ()
{
	return SHA256_DIGEST_LENGTH * 2 + 1;
}

unsigned short int len_hash_ripemd160 ()
{
	return RIPEMD160_DIGEST_LENGTH * 2 + 1;
}

static void human_readable (char *dest, const unsigned char *md, const int length)
{
	int i;

    for (i = 0; i < length; i++)
    	sprintf (dest + i*2, "%02x", (unsigned int) md[i]);
}

void hash_md5 (char *dest, const char *data)
{
	MD5_CTX c;
	unsigned char md[MD5_DIGEST_LENGTH];

    MD5_Init   (&c);
	MD5_Update (&c, data, strlen (data));
    MD5_Final  (md, &c);

    human_readable (dest, md, MD5_DIGEST_LENGTH);
}

void hash_sha256 (char *dest, const char *data)
{
	SHA256_CTX c;
	unsigned char md[SHA256_DIGEST_LENGTH];

    SHA256_Init   (&c);
    SHA256_Update (&c, data, strlen (data));
    SHA256_Final  (md, &c);

    human_readable (dest, md, SHA256_DIGEST_LENGTH);
}

void hash_ripemd160 (char *dest, const char *data)
{
	RIPEMD160_CTX c;
	unsigned char md[RIPEMD160_DIGEST_LENGTH];

	RIPEMD160_Init   (&c);
	RIPEMD160_Update (&c, data, strlen (data));
	RIPEMD160_Final  (md, &c);

	human_readable (dest, md, RIPEMD160_DIGEST_LENGTH);
}
