/* $Id: gkfs.c,v 1.1 2003/12/22 21:53:23 luis Exp $
 * Author: Luis Colorado <Luis.Colorado@HispaLinux.ES>
 * Date: Wed Dec 17 23:10:01 MET 2003
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

#define IN_GKFS_C

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
#include "gkfs.h"

/* constants */

/* types */

/* prototypes */

/* variables */
static char GKFS_C_RCSId[]="\n$Id: gkfs.c,v 1.1 2003/12/22 21:53:23 luis Exp $\n";

/* functions */

RC4BYTE *getkeyfromstr(char *s)
{
	int n, i;
	static RC4BYTE b[RC4MOD];

	for (n = 0; *s; s++) {
		if (isxdigit(*s)) {
			if (!(n & 1)) {
				b[n>>1] = 0;
			} /* if */
			switch(*s) {
			case '0': b[n>>1] |= (n & 1) ? 0x00 : 0x00; break;
			case '1': b[n>>1] |= (n & 1) ? 0x01 : 0x10; break;
			case '2': b[n>>1] |= (n & 1) ? 0x02 : 0x20; break;
			case '3': b[n>>1] |= (n & 1) ? 0x03 : 0x30; break;
			case '4': b[n>>1] |= (n & 1) ? 0x04 : 0x40; break;
			case '5': b[n>>1] |= (n & 1) ? 0x05 : 0x50; break;
			case '6': b[n>>1] |= (n & 1) ? 0x06 : 0x60; break;
			case '7': b[n>>1] |= (n & 1) ? 0x07 : 0x70; break;
			case '8': b[n>>1] |= (n & 1) ? 0x08 : 0x80; break;
			case '9': b[n>>1] |= (n & 1) ? 0x09 : 0x90; break;
			case 'A':
			case 'a': b[n>>1] |= (n & 1) ? 0x0a : 0xa0; break;
			case 'B':
			case 'b': b[n>>1] |= (n & 1) ? 0x0b : 0xb0; break;
			case 'C':
			case 'c': b[n>>1] |= (n & 1) ? 0x0c : 0xc0; break;
			case 'D':
			case 'd': b[n>>1] |= (n & 1) ? 0x0d : 0xd0; break;
			case 'E':
			case 'e': b[n>>1] |= (n & 1) ? 0x0e : 0xe0; break;
			case 'F':
			case 'f': b[n>>1] |= (n & 1) ? 0x0f : 0xf0; break;
			}
			n++;
		} /* if */
		if (((n+1)>>1) >= RC4MOD)
			break;
	} /* for */
	n++;
	n >>= 1;
	for (i = n; i < RC4MOD; i++) {
		b[i] = b[i-n];
	}
#if DEBUG
	fprintbuf(stderr, RC4MOD, b, "");
#endif
	return b;
} /* getkeyfromstr */

/* $Id: gkfs.c,v 1.1 2003/12/22 21:53:23 luis Exp $ */
