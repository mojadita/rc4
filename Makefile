# $Id: Makefile,v 1.3 2003/12/22 23:53:21 luis Exp $
# Author: Luis.Colorado@HispaLinux.ES
# Date: Thu Dec 11 22:25:41     2003

name	?= rc4 

prefix	?= $(HOME)
libdir	?= $(prefix)/lib
incdir	?= $(prefix)/include

VMAJOR	?= 1
VMINOR	?= 0
VRSION	?= $(VMAJOR).$(VMINOR)

RMFLAGS ?= -f
IFLAGS	?= #-o `id -u` -g `id -g`
RM		?= /bin/rm $(RMFLAGS)
LINK	?= ln -sf
INSTALL	?= /usr/bin/install $(IFLAGS)
IMOD	?= -m 0644
XMOD	?= -m 0711
DMOD	?= -m 0755

rc4_a				?= lib$(name).a
rc4_so				?= lib$(name).so
rc4_soname			?= $(rc4_so).$(VMAJOR)
rc4_fullname		?= $(rc4_soname).$(VMINOR)
rc4_a_objs			?= rc4.o
rc4_fullname_objs	?= rc4.do
rc4_includes		?= rc4.h
toclean				+= $(rc4_a) $(rc4_so) $(rc4_soname)
toclean				+= $(rc4_fullname)
toclean				+= $(rc4_a_objs) $(rc4_fullname_objs)

targets = $(rc4_a) $(rc4_so)

all: $(targets)
clean:
	$(RM) $(toclean)
test: rc4 rc4_test rc4_test2
install: $(targets)
	$(INSTALL) $(DMOD) -d $(libdir)
	$(INSTALL) $(DMOD) -d $(incdir)
	$(INSTALL) $(FMOD) $(rc4_a) $(libdir)
	$(INSTALL) $(FMOD) $(rc4_includes) $(incdir)
	$(LINK) $(rc4_fullname) $(libdir)/$(rc4_soname)
	$(LINK) $(rc4_soname) $(libdir)/$(rc4_so)
deinstall:
	-$(RM) $(libdir)/$(rc4_fullname)
	-$(RM) $(libdir)/$(rc4_a)
	-$(RM) $(libdir)/$(rc4_soname)
	-$(RM) $(libdir)/$(rc4_so)
	-@for i in $(rc4_includes);\
	do\
		echo $(RM) $(incdir)/$$i;\
		$(RM) $(incdir)/$$i;\
	done
depend: .depend

.SUFFIXES: .c .o .do .so .a
.PHONY: all clean test install deinstall depend

$(rc4_a): $(rc4_a_objs)
	$(AR) $(ARFLAGS) $@ $?

$(rc4_so): $(rc4_soname)
	$(LINK) $? $@
$(rc4_soname): $(rc4_fullname)
	$(LINK) $? $@

$(rc4_fullname): $(rc4_fullname_objs)
	$(CC) $(LDFLAGS) -shared -o $@ $(rc4_fullname_objs) -Wl,-soname=$(rc4_soname)

$(rc4_fullname_objs): $*.c
	$(CC) $(CFLAGS) -c -fPIC -o $@ $?

rc4_objs = rc4_main.o rc4.o fprintbuf.o gkfs.o b64.o
toclean	+= $(rc4_objs)
rc4: $(rc4_objs)
	$(CC) $(LDFLAGS) -o $@ $(rc4_objs)

rc4_test_objs = rc4.o fprintbuf.o rc4_test.o
toclean += $(rc4_test_objs)
rc4_test: $(rc4_test_objs)
	$(CC) $(LDFLAGS) -o $@ $(rc4_test_objs)

rc4_test2_objs = rc4_test2.o rc4.o fprintbuf.o
toclean += $(rc4_test2_objs)
rc4_test2: $(rc4_test2_objs)
	$(CC) $(LDFLAGS) -o $@ $(rc4_test2_objs)

.depend: Makefile *.c
	mkdep *.c

# $Id: Makefile,v 1.3 2003/12/22 23:53:21 luis Exp $
