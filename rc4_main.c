/* $Id: rc4_main.c,v 1.3 2003/12/22 21:53:23 luis Exp $
 * Author: Luis Colorado <Luis.Colorado@HispaLinux.ES>
 * Date: Wed Dec 17 00:23:34 MET 2003
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
#include <string.h>
#include <malloc.h>
#include <pwd.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "rc4.h"
#include "b64.h"
#include "gkfs.h"

/* constants */
#define C_FLAG	0x01
#define A_FLAG	0x02
#define V_FLAG	0x04
#define H_FLAG	0x08
#define OP_CIPHER 1
#define OP_DECIPHER	2

/* types */

/* prototypes */

/* variables */
static char RC4_MAIN_C_RCSId[]="\n$Id: rc4_main.c,v 1.3 2003/12/22 21:53:23 luis Exp $\n";

const char ext[] = ".rc4";

struct {
	int flags;
	RC4BYTE *key;
} cfg = {
	C_FLAG | A_FLAG,
};

/* functions */
void do_usage(void)
{
	printf(
"Usage: aes [ options ... ] [ file ... ]\n"
"Options:\n"
"  -a Ascii output (in case of encipherment) or input (in case of decipherment)\n"
"     (base64 coded output/input)\n"
"  -b BINARY output (in case of encipherment) or input (in case of decipherment)\n"
"  -c\n"
"     Use this option to cipher. Default option.\n"
"  -d\n"
"     Use this option to decipher.\n"
"  -v\n"
"     Be verbose. Show info about what rc4 is doing.\n"
"  -p password\n"
"     User password coded in hex\n"
"  -h\n"
"     Help. This help screen.\n"
	);
} /* do_usage */

void procesar(char *nomfich)
{
	FILE *in;

	if (cfg.flags & V_FLAG) {
		fprintf(stderr, "rc4:"__FILE__"(%d): procesando %s\n",
			__LINE__, nomfich ? nomfich : "<stdin>");
	} /* if */
	if (nomfich) {
		in = fopen(nomfich, "r");
		if (!in) {
			fprintf(stderr, "rc4:"__FILE__"(%d): fopen: %s: %s(%d)\n",
				__LINE__, nomfich, sys_errlist[errno], errno);
			return;
		} /* if */
	} else {
		in = stdin;
	} /* if */

	if (cfg.flags & C_FLAG) {
		RC4STATUS rc4st;
		b64_st b64st;
		int c;

		rc4init(&rc4st, cfg.key);
		if (cfg.flags & A_FLAG) b64_init(&b64st);

		/* leemos caracteres, ciframos y codificamos b64 opcionalmente */
		while ((c = fgetc(in)) != EOF) {
			c ^= rc4next(&rc4st);
			if (cfg.flags & A_FLAG) {
				char cin = c;
				char cout[4];
				int n;
				n = b64_code(&b64st, &cin, 1, cout);
				printf("%0.*s", n, cout);
			} else {
				fputc(c, stdout);
			} /* if */
		} /* while */
		if (cfg.flags & A_FLAG) {
			char cout[4];
			int n;
			n = b64_code_end(&b64st, cout);
			printf("%0.*s", n, cout);
		} /* if */
	} else { /* decode */
		RC4STATUS rc4st;
		b64_st b64st;
		int c;

		rc4init(&rc4st, cfg.key);
		if (cfg.flags & A_FLAG) b64_init(&b64st);

		/* leemos caracteres, descodificamos b64 opcionalmente y desciframos */
		while ((c = fgetc(in)) != EOF) {
			if (cfg.flags & A_FLAG) {
				char cin = c;
				char cout[1];
				int n;
				n = b64_decode(&b64st, &cin, 1, cout);
				if (n < 1) continue;
				c = cout[0];
			} /* if */
			c ^= rc4next(&rc4st);
			fputc(c, stdout);
		} /* while */
		if (cfg.flags & A_FLAG) {
			char cout[1];
			int n;
			n = b64_decode_end(&b64st, cout);
			if (n) {
				c = cout[0];
				c ^= rc4next(&rc4st);
				fputc(c, stdout);
			} /* if */
		} /* if */
	} /* if */
	fclose(in);
} /* procesar */

/* main program */
int main (int argc, char **argv)
{

	extern int optind;
	extern char *optarg;
	int opt;
	char theKey [256];

	while ((opt = getopt(argc, argv, "abcp:dhv")) != EOF) {
		switch(opt) {
		case 'a': cfg.flags |= A_FLAG; break;
		case 'b': cfg.flags &= ~A_FLAG; break;
		case 'c': cfg.flags |= C_FLAG; break;
		case 'd': cfg.flags &= ~C_FLAG; break;
		case 'p': cfg.key = optarg; break;
		case 'v': cfg.flags |= V_FLAG; break;
		case 'h': default: cfg.flags |= H_FLAG; break;
		} /* switch */
	} /* while */
	/* testeo de errores en los datos */
	if (cfg.flags & H_FLAG)
	{
		do_usage();
		exit(EXIT_FAILURE);
	} /* if */

	/* proceso de la clave */
	if (!cfg.key) {
		char aux[1024];
		FILE *f = fopen("/dev/tty", "ra");
		fprintf(f,"Clave: ");
		fgets(aux, sizeof aux, f);
		cfg.key = strdup(aux);
		fclose(f);
	} /* if */

	cfg.key = getkeyfromstr(cfg.key);

	/* proceso de ficheros/stdin. */
	argc -= optind; argv += optind;
	if (argc) {
		while (argc) {
			procesar(argv[0]);
			argc--; argv++;
		} /* while */
	} else {
		procesar(NULL); /* stdin */
	} /* if */
	exit(EXIT_SUCCESS);
} /* main */

/* $Id: rc4_main.c,v 1.3 2003/12/22 21:53:23 luis Exp $ */
