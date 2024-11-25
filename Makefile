DESTDIR=/usr/local
BUILDDIR=apps/engine-linux
TARGET_ENGINE=onengine
TARGET_PACK=onpack
CC=cc
CXX=c++
AR=ar
STRIP=strip
WINDRES=windres

build:
	@cd $(BUILDDIR) && \
	make clean && \
	make $(TARGET_ENGINE) $(TARGET_PACK) CC=$(CC) CXX=$(CXX) AR=$(AR) STRIP=$(STRIP) WINDRES=$(WINDRES) && \
	cp $(TARGET_ENGINE) $(TARGET_PACK) ../../ && \
	cd ../..

install:
	@install -v -d $(DESTDIR)/bin
	@install -v $(TARGET_ENGINE) $(DESTDIR)/bin/onengine
	@install -v $(TARGET_PACK) $(DESTDIR)/bin/onpack
