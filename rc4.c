/* $Id: rc4.c,v 1.2 2003/12/11 21:35:13 luis Exp $
 * Author: Luis Colorado <Luis.Colorado@HispaLinux.ES>
 * Date: Thu Dec 11 09:12:46 MET 2003
 *
 * Disclaimer:
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#define IN_RC4_C

/* Standard include files */
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "rc4.h"

/* constants */

/* types */

/* prototypes */

/* variables */
static char RC4_C_RCSId[]="\n$Id: rc4.c,v 1.2 2003/12/11 21:35:13 luis Exp $\n";

/* functions */
static void rc4advance(RC4STATUS *s, RC4BYTE *key)
{
    RC4BYTE c;

    s->i++;
    s->i %= RC4MOD;

    s->j += s->S[s->i];
    if(key)
        s->j += key[s->i];
    s->j %= RC4MOD;

    /* SWAP S[i] <--> S[j] */
    if (s->i != s->j) {
        RC4BYTE c;

        c = s->S[s->i];
        s->S[s->i] = s->S[s->j];
        s->S[s->j] = c;
    } /* if */

#if DEBUG
    fprintbuf(stdout, RC4MOD, s->S,
        "STATUS: i = 0x%02x; j = 0x%02x; K = 0x%02x",
        s->i, s->j, s->S[(s->S[s->i] + s->S[s->j])%RC4MOD]);
#endif

} /* rc4advance */

void rc4init(RC4STATUS *s, RC4BYTE *key)
{
    int i;

    /* initialize fields */
    s->i = s->j = 0;
    for (i = 0; i < RC4MOD; i++)
        s->S[i] = i;

    /* scramble with the key */
    for (i = 0; i < RC4MOD; i++)
        rc4advance(s, key);

} /* rc4init */

RC4BYTE rc4next(RC4STATUS *s)
{
    rc4advance(s, NULL);
    return s->S[(s->S[s->i] + s->S[s->j]) % RC4MOD];
} /* rc4next */

void rc4cipher(RC4STATUS *s, RC4BYTE *b, size_t n)
{
    for (;n;b++,n--)
        *b ^= rc4next(s);
} /* rc4cipher */

/* $Id: rc4.c,v 1.2 2003/12/11 21:35:13 luis Exp $ */
