/* $Id: rc4.h,v 1.1 2003/12/11 11:04:15 luis Exp $
 * Author: Luis Colorado <Luis.Colorado@HispaLinux.ES>
 * Date: Thu Dec 11 09:11:05 MET 2003
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

/* Do not include anything BEFORE the line below, as it would not be
 * protected against double inclusion from other files
 */
#ifndef RC4_H
#define RC4_H

static char RC4_H_RCSId[] = "\n$Id: rc4.h,v 1.1 2003/12/11 11:04:15 luis Exp $\n";

/* constants */
#define RC4MOD	256

/* types */
typedef unsigned char RC4BYTE;

typedef struct RC4STATUS {
	RC4BYTE i;
	RC4BYTE j;
	RC4BYTE S[RC4MOD];
} RC4STATUS;

/* prototypes */

#endif /* RC4_H */
/* Do not include anything AFTER the line above, as it would not be
 * protected against double inclusion from other files.
 */

/* $Id: rc4.h,v 1.1 2003/12/11 11:04:15 luis Exp $ */
