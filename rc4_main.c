/* $Id: rc4_main.c,v 1.1 2003/12/11 11:04:15 luis Exp $
 * Author: Luis Colorado <Luis.Colorado@HispaLinux.ES>
 * Date: Thu Dec 11 11:52:13 MET 2003
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

#define IN_RC4_MAIN_C

/* Standard include files */
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

/* constants */

/* types */

/* prototypes */

/* variables */
static char RC4_MAIN_C_RCSId[]="\n$Id: rc4_main.c,v 1.1 2003/12/11 11:04:15 luis Exp $\n";

char default_pw[256] = "";

/* functions */
void do_usage(void)
{
} /* do_usage */

/* main program */
int main (int argc, char **argv)
{

	extern int optind;
	extern char *optarg;
	int opt;

	while ((opt = getopt(argc, argv, "h")) != EOF) {
		switch(opt) {
		case 'p':
			strncpy(default_pw, sizeof default_pw, optarg);
		case 'h':
		  do_usage(); exit(EXIT_SUCCESS);
		default:
		  do_usage(); exit(EXIT_FAILURE);
		}
	} /* while */
} /* main */

/* $Id: rc4_main.c,v 1.1 2003/12/11 11:04:15 luis Exp $ */
