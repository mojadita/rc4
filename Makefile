# $Id: Makefile,v 1.1 2003/12/11 21:35:13 luis Exp $
# Author: Luis.Colorado@HispaLinux.ES
# Date: Thu Dec 11 22:25:41     2003

rc4_test_objs = rc4.o fprintbuf.o rc4_test.o
rc4_test: $(rc4_test_objs)
	$(CC) $(LDFLAGS) -o rc4_test $(rc4_test_objs)
rc4.o rc4_test.o: rc4.h

# $Id: Makefile,v 1.1 2003/12/11 21:35:13 luis Exp $
