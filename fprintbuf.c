/* $RCSfile: fprintbuf.c,v $ -- muestra un buffer de datos en hexadecimal y ASCII.
 * Autor: Luis Colorado.
 * Fecha: 7.10.92.
 * Version: $Revision: 1.1 $ ($Date: 2003/12/11 11:04:15 $)
 */
#include <sys/types.h>
#include <ctype.h>
#include <stdio.h>
#include <stdarg.h>

static char *id = "$Id: fprintbuf.c,v 1.1 2003/12/11 11:04:15 luis Exp $\n";

#define 	TAM_REG		16

int fprintbuf (FILE *f,	/* fichero de salida */
	int t,			/* tamano del buffer */
	unsigned char *b,	/* puntero al buffer */
    int A, int B,
	char *fmt, ...)		/* rotulo de cabecera */
{
	int off, i;
	unsigned char c;
	va_list lista;
	size_t escritos = 0;
    char *color = "", *reset = "";

	if (fmt)
		escritos += fprintf (f, "DESPLAZ. : ");
	va_start (lista, fmt);
	escritos += vfprintf (f, fmt, lista);
	va_end (lista);
	escritos += fprintf (f, "\n");
	off = 0;
	while (t > 0) {
		escritos += fprintf (f, "%08x : ", off);
		for (i = 0; i < TAM_REG; i++) {
            if (off == A) {
                if (off == B) {
                    color = "\033[33m";
                } else {
                    color = "\033[31m";
                }
            } else if (off == B) {
                color = "\033[32m";
            }
            if (off == A || off == B)
                reset = "\033[0m";
			if (t > 0)
				escritos += fprintf (f, "%s%02x%s ", color, *b & 0xff, reset);
			else escritos += fprintf (f, "   ");
			off++;
			t--;
			b++;
            color = reset = "";
		}
		escritos += fprintf (f, ": ");
		t += TAM_REG;
		b -= TAM_REG;
		off -= TAM_REG;
		for (i = 0; i < TAM_REG; i++) {
            if (off == A) {
                if (off == B) {
                    color = "\033[33m";
                } else {
                    color = "\033[31m";
                }
            } else if (off == B) {
                color = "\033[32m";
            }
            if (off == A || off == B)
                reset = "\033[0m";
			c = *b++;
			if (t > 0)
				if (isprint (c))
					escritos += fprintf (f, "%s%c%s", color, c, reset);
				else	escritos += fprintf (f, ".");
			else break;
			off++;
			t--;
            color = reset = "";
		}
		escritos += fprintf (f, "\n");
	}
	escritos += fprintf (f, "%08x\n", off);
	return escritos;
}

/* fin de $RCSfile: fprintbuf.c,v $ */
