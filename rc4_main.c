/* $Id: rc4_main.c,v 1.2 2003/12/11 21:35:13 luis Exp $
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
#include "rc4.h"

/* constants */
#define OPT_ASCII	0x01

/* types */

/* prototypes */

/* variables */
static char RC4_MAIN_C_RCSId[]="\n$Id: rc4_main.c,v 1.2 2003/12/11 21:35:13 luis Exp $\n";

char default_pw[256] = "";
struct config {
	int flags;
	RC4BYTE *clave;
	RC4STATUS estado;
} cfg = {
	OPT_ASCII,
	NULL, /* clave de 40 bits (cinco bytes) por defecto */
};

/* functions */
void do_usage(void)
{
	fprintf(stderr, "Uso: rc4 [ opciones ... ]\n");
	fprintf(stderr, "rc4 es un filtro que cifra/descifra la entrada estandar, produciendo la salida\n");
	fprintf(stderr, "cifrada o descifrada correspondiente por la salida estandar.\n");
	fprintf(stderr, " -p password\n");
	fprintf(stderr, "    Permite especificar la clave de cifrado. En caso de que no se especifique\n");
	fprintf(stderr, "	clave de cifrado, el programa solicita una a través de la función\n");
	fprintf(stderr, "	getpass(3).\n");
	fprintf(stderr, " -a\n");
	fprintf(stderr, " 	Provoca que la parte cifrada se codifique/descodifique en formato base64.\n");
	fprintf(stderr, " -A\n");
	fprintf(stderr, "    Opuesta a la anterior opción. La parte cifrada se interpreta como datos\n");
	fprintf(stderr, "	binarios.\n");
} /* do_usage */

/* main program */
int main (int argc, char **argv)
{

	extern int optind;
	extern char *optarg;
	int opt;

	while ((opt = getopt(argc, argv, "hp:aA")) != EOF) {
		switch(opt) {
		case 'p':
			strncpy(default_pw, sizeof default_pw, optarg); break;
		case 'a': cfg.flags |= OPT_ASCII; break;
		case 'A': cfg.flags &= ~OPT_ASCII; break;
		case 'h':
		  do_usage(); exit(EXIT_SUCCESS);
		default:
		  do_usage(); exit(EXIT_FAILURE);
		} /* switch */
	} /* while */
} /* main */

/* $Id: rc4_main.c,v 1.2 2003/12/11 21:35:13 luis Exp $ */
