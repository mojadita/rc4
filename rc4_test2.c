/* rc4_test2 -- pseudo generador de números aleatorios.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: domingo, 21 de agosto de 2016, 14:43:43 EEST
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include "rc4.h"
#define NCOL    72
#define DEV_RANDOM      "/dev/random"
#define F(x) "%s:%d:%s: " x, __FILE__, __LINE__, __func__
static RC4 cad[] = {
         32,  33,  34,  35,  36,  37,  38,  39,
         40,  41,  42,  43,  44,  45,  46,  47,
         48,  49,  50,  51,  52,  53,  54,  55,
         56,  57,  58,  59,  60,  61,  62,  63,
         64,  65,  66,  67,  68,  69,  70,  71,
         72,  73,  74,  75,  76,  77,  78,  79,
         80,  81,  82,  83,  84,  85,  86,  87,
         88,  89,  90,  91,  92,  93,  94,  95,
         96,  97,  98,  99, 100, 101, 102, 103,
        104, 105, 106, 107, 108, 109, 110, 111,
        112, 113, 114, 115, 116, 117, 118, 119,
        120, 121, 122, 123, 124, 125, 126,
        0
    };
int main(int argc, char **argv)
{
    RC4STATUS *sta, *stb;
    RC4 *key = NULL;
    size_t keylen;
    int opt, i = 0;
    static RC4 *tab = cad;
    size_t mod;

    while ((opt = getopt(argc, argv, "k:t:")) != EOF) {
        switch (opt) {
        case 'k': key = (RC4 *)optarg; break;
        case 't': tab = optarg; break;
        }
    }
    mod = strlen(tab);

    sta = new_rc4status(mod);
    if (key) {
        rc4init(sta, key, keylen = strlen((char*)key));
    } else {
        RC4 keybuffer[RC4MOD];
        int i, fd = open(DEV_RANDOM, O_RDONLY);
        if (fd == -1) {
            fprintf(stderr, F("open: %s: %s(errno=%d)\n"),
                    DEV_RANDOM, strerror(errno), errno);
            exit(1);
        }
        keylen = read(fd, keybuffer, sizeof keybuffer);
        if (keylen > mod) keylen = mod;
        for (i = 0; i < keylen; i++) keybuffer[i] = keybuffer[i] % mod;
        rc4init(sta, keybuffer, keylen);
    }

    for(;;) {
        putchar(tab[rc4next(sta)]);
        if (++i == NCOL) {
            puts("");
            i = 0;
        }
    } /* for */

} /* main */
