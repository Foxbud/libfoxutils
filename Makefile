SHELL = /bin/sh
.SUFFIXES:
.SUFFIXES: .c .h .o .so



# Build directories.
prjdir = $(realpath $(CURDIR))
srcdir = $(prjdir)/src
incdir = $(prjdir)/include
pubincdir = $(incdir)/foxutils
builddir = $(prjdir)/build
docdir = $(prjdir)/docs

# Installation directories.
prefix = /usr/local
exec_prefix = $(prefix)
libdir = $(exec_prefix)/lib
includedir = $(prefix)/include

# Library names.
dlibnamev0 = libfoxutils.so
dlibnamev1 = $(dlibnamev0).1
dlibnamev3 = $(dlibnamev1).0.0dev
slibname = $(subst .so,.a,$(dlibnamev0))

# Build files.
src = $(wildcard $(srcdir)/*.c) $(wildcard $(srcdir)/foxutils/*.c)
pubinc = $(wildcard $(pubincdir)/*.h)
inc = $(pubinc) $(wildcard $(incdir)/*.h)
obj = $(src:.c=.o)
dlib = $(builddir)/$(dlibnamev3)
slib = $(builddir)/$(slibname)

# Program and flag defaults.
CFLAGS = -Wall -Wextra -O3
ALL_CFLAGS = -I$(incdir) $(CFLAGS)
ALL_LDFLAGS = $(LDFLAGS)
ARFLAGS = -crs
ALL_ARFLAGS = $(ARFLAGS)
DOC = doxygen
INSTALL = install



.PHONY: lib
lib: dlib slib

$(dlib): $(obj)
	mkdir -p $(builddir)
	$(LD) -shared -soname=$(dlibnamev1) $(ALL_LDFLAGS) -o $@ $(obj)

$(slib): $(obj)
	mkdir -p $(builddir)
	$(AR) $(ALL_ARFLAGS) $@ $(obj)

%.o: %.c
	$(CC) -c $(ALL_CFLAGS) -o $@ $<

$(docdir): $(pubinc)
	$(DOC) $(DOCFLAGS)

.PHONY: all
all: lib docs

.PHONY: dlib
dlib: $(dlib)

.PHONY: slib
slib: $(slib)

.PHONY: docs
docs: $(docdir)

.PHONY: clean
clean:
	rm -rf $(obj) $(builddir) $(docdir)

.PHONY: install
install: lib $(pubinc)
	$(NORMAL_INSTALL)
	$(INSTALL) -Dt $(DESTDIR)$(libdir) $(dlib)
	$(INSTALL) -Dt $(DESTDIR)$(libdir) -m 644 $(slib)
	$(INSTALL) -Dt $(DESTDIR)$(includedir)/foxutils -m 644 $(pubinc)
	$(POST_INSTALL)
	ln -srf $(DESTDIR)$(libdir)/$(dlibnamev3) $(DESTDIR)$(libdir)/$(dlibnamev1)
	ln -srf $(DESTDIR)$(libdir)/$(dlibnamev3) $(DESTDIR)$(libdir)/$(dlibnamev0)

.PHONY: uninstall
uninstall:
	$(PRE_UNINSTALL)
	rm $(DESTDIR)$(libdir)/$(dlibnamev0) $(DESTDIR)$(libdir)/$(dlibnamev1)
	$(NORMAL_UNINSTALL)
	rm -r $(DESTDIR)$(includedir)/foxutils
	rm $(DESTDIR)$(libdir)/$(slibname)
	rm $(DESTDIR)$(libdir)/$(dlibnamev3)
