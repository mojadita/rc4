# $Id: Makefile,v 1.3 2003/12/22 23:53:21 luis Exp $
# Author: Luis.Colorado@HispaLinux.ES
# Date: Thu Dec 11 22:25:41     2003

all: rc4 rc4_test

rc4_objs = rc4_main.o rc4.o fprintbuf.o gkfs.o b64.o
rc4: $(rc4_objs)
	$(CC) $(LDFLAGS) -o rc4 $(rc4_objs)

rc4_test_objs = rc4.o fprintbuf.o rc4_test.o
rc4_test: $(rc4_test_objs)
	$(CC) $(LDFLAGS) -o rc4_test $(rc4_test_objs)

rc4.o rc4_test.o: rc4.h

# $Id: Makefile,v 1.3 2003/12/22 23:53:21 luis Exp $
