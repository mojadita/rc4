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
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "rc4.h"
#include "fprintbuf.h"

#define F(s) "%s:%d:%s: " s, __FILE__, __LINE__, __func__

RC4STATUS *new_rc4status(size_t mod)
{
    RC4STATUS *res = malloc(sizeof(RC4STATUS));

    assert(res != NULL);
    res->s = malloc(mod*sizeof(RC4));
    assert(res->s != NULL);
    res->mod = mod;

    return res;
}

/* functions */
static void rc4advance(RC4STATUS *s, RC4 *key, size_t keysize)
{
    RC4 c;

#define I       (s->i)
#define J       (s->j)
#define N       (s->mod)
#define S(x)    (s->s[(x)])
#define C       S((S(I) + S(J)) % N)
#define K(x)    key[(x) % keysize]

#if DEBUG
    fprintbuf(stdout, N, s->s, I, J,
              F("ENTER: I = %d; J = %d; S(I) = %d; S(J) = %d"),
              I, J, S(I), S(J));
#endif

    I = (I+1) % N;
#ifdef DEBUG
    printf(F("I <= I + 1 = %d; S(I) = %d\n"), I, S(I));
#endif
    if (key && keysize) {
#ifdef DEBUG
        printf(F("K(I) = %d\n"), K(I));
#endif
        J = (J + S(I) + K(I)) % N;
#ifdef DEBUG
        printf(F("J <= J + S(I) + K(I) = %d; S(J) = %d\n"), J, S(J));
#endif
    } else {
        J = (J + S(I)) % N;
#ifdef DEBUG
        printf(F("J <= J + S(I) = %d; S(J) = %d\n"), J, S(J));
#endif
    }

    /* SWAP S(I) <--> S(J) */
    if (I != J) {
        RC4 c;

        c = S(I);
        S(I) = S(J);
        S(J) = c;
#ifdef DEBUG
        printf(F("SWAP: S(I) <= %d; S(J) <= %d\n"), S(I), S(J));
#endif
    } /* if */

#ifdef DEBUG
    fprintf(stdout, F("EXIT:  I = %d; J = %d; C = S(S(I) + S(J)) = %d\n"), I, J, C);
#endif

} /* rc4advance */

void rc4init(RC4STATUS *s, RC4 *key, size_t keysize)
{
    int i;

    /* initialize fields */
    I = J = 0;
    for (i = 0; i < N; i++)
        S(i) = i;

    /* scramble with the key */
    for (i = 0; i < N; i++)
        rc4advance(s, key, keysize);

} /* rc4init */

RC4 rc4next(RC4STATUS *s)
{
    rc4advance(s, NULL, 0);
    return C;
} /* rc4next */

void rc4cipher(RC4STATUS *s, RC4 *b, size_t n)
{
    for (;n;b++,n--) *b = (*b + rc4next(s)) % N;
} /* rc4cipher */

void rc4uncipher(RC4STATUS *s, RC4 *b, size_t n)
{
    for (;n;b++,n--) *b = (*b + N - rc4next(s))% N;
}

/* $Id: rc4.c,v 1.2 2003/12/11 21:35:13 luis Exp $ */
