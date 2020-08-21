SHELL = /bin/sh
.SUFFIXES:
.SUFFIXES: .c .h .o .so



# Names.
libname = foxutils
dlibnamev0 = lib$(libname).so
dlibnamev1 = $(dlibnamev0).1
dlibnamev3 = $(dlibnamev1).0.0dev
slibname = lib$(libname).a
pubincname = foxutils

# Build directories.
prjdir = $(realpath $(CURDIR))
srcdir = $(prjdir)/src
incdir = $(prjdir)/include
pubincdir = $(incdir)/$(pubincname)
builddir = $(prjdir)/build
docdir = $(prjdir)/docs

# Installation directories.
prefix = /usr/local
exec_prefix = $(prefix)
libdir = $(exec_prefix)/lib
includedir = $(prefix)/include

# Build files.
src = $(wildcard $(srcdir)/*/*.c)
pubinc = $(wildcard $(pubincdir)/*.h)
obj = $(src:.c=.o)
dlib = $(builddir)/$(dlibnamev3)
slib = $(builddir)/$(slibname)

# Program and flag defaults.
CFLAGS = -Wall -Wextra -O3
ALL_CFLAGS = -I$(incdir) $(CFLAGS)
LD = $(CC)
LDFLAGS = -rdynamic
ALL_LDFLAGS = -shared -Wl,-soname,$(dlibnamev1) $(LDFLAGS)
ARFLAGS = -crs
ALL_ARFLAGS = $(ARFLAGS)
DOC = doxygen
INSTALL = install



.PHONY: libs
libs: dlib slib

$(dlib): $(obj)
	mkdir -p $(builddir)
	$(LD) $(ALL_LDFLAGS) -o $@ $(obj)

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
install: install-symlinks install-headers

.PHONY: install-libs
install-libs: libs
	$(INSTALL) -Dt $(DESTDIR)$(libdir) $(dlib)
	$(INSTALL) -Dt $(DESTDIR)$(libdir) -m 644 $(slib)

.PHONY: install-symlinks
install-symlinks: install-libs
	ln -srf $(DESTDIR)$(libdir)/$(dlibnamev3) $(DESTDIR)$(libdir)/$(dlibnamev1)
	ln -srf $(DESTDIR)$(libdir)/$(dlibnamev3) $(DESTDIR)$(libdir)/$(dlibnamev0)

.PHONY: install-headers
install-headers: $(pubinc)
	$(INSTALL) -Dt $(DESTDIR)$(includedir)/$(pubincname) -m 644 $(pubinc)

.PHONY: uninstall
uninstall: uninstall-libs uninstall-headers

.PHONY: uninstall-libs
uninstall-libs: uninstall-symlinks
	rm -f $(DESTDIR)$(libdir)/$(slibname)
	rm -f $(DESTDIR)$(libdir)/$(dlibnamev3)

.PHONY: uninstall-symlinks
uninstall-symlinks:
	rm -f $(DESTDIR)$(libdir)/$(dlibnamev0) $(DESTDIR)$(libdir)/$(dlibnamev1)

.PHONY: uninstall-headers
uninstall-headers:
	rm -rf $(DESTDIR)$(includedir)/$(pubincname)
