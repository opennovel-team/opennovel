CC=cc
AR=ar

CPPFLAGS = \
	-DUSE_X11_SOFTRENDER \
	-I./libroot-solaris/include \
	-I./libroot-solaris/include/png \
	-I./libroot-solaris/include/freetype \
	-I/usr/local/include \
	-I/usr/X11R6/include

CFLAGS = \
	-O2 \
	-g0 \
	-std=gnu11

LDFLAGS = \
	-lpthread \
	-lm \
	-L/usr/X11R6/lib \
	-lX11 \
	-lXpm \
	./libroot-solaris/lib/libpng.a \
	./libroot-solaris/lib/libjpeg.a \
	./libroot-solaris/lib/libwebp.a \
	./libroot-solaris/lib/libfreetype.a \
	./libroot-solaris/lib/libbz2.a \
	./libroot-solaris/lib/libz.a \
	./libroot-solaris/lib/libbrotlidec.a \
	./libroot-solaris/lib/libbrotlicommon.a \
	./libroot-solaris/lib/libvorbis.a \
	./libroot-solaris/lib/libogg.a

#
# Source
#

include ../common.mk

SRCS = $(SRCS_MAIN) $(SRCS_LINUX) $(SRCS_OPENGL)

#
# Objects
#

OBJS = \
	objs/anime.o \
	objs/ciel.o \
	objs/conf.o \
	objs/event.o \
	objs/file.o \
	objs/glyph.o \
	objs/gui.o \
	objs/history.o \
	objs/image.o \
	objs/log.o \
	objs/main.o \
	objs/mixer.o \
	objs/readimage.o \
	objs/readjpeg.o \
	objs/readpng.o \
	objs/readwebp.o \
	objs/save.o \
	objs/script.o \
	objs/seen.o \
	objs/stage.o \
	objs/vars.o \
	objs/wave.o \
	objs/wms_core.o \
	objs/wms_impl.o \
	objs/wms_lexer.yy.o \
	objs/wms_parser.tab.o \
	objs/cmd_anime.o \
	objs/cmd_bg.o \
	objs/cmd_ch.o \
	objs/cmd_chapter.o \
	objs/cmd_chch.o \
	objs/cmd_choose.o \
	objs/cmd_click.o \
	objs/cmd_config.o \
	objs/cmd_gosub.o \
	objs/cmd_goto.o \
	objs/cmd_if.o \
	objs/cmd_layer.o \
	objs/cmd_menu.o \
	objs/cmd_message.o \
	objs/cmd_move.o \
	objs/cmd_music.o \
	objs/cmd_plugin.o \
	objs/cmd_return.o \
	objs/cmd_set.o \
	objs/cmd_shake.o \
	objs/cmd_skip.o \
	objs/cmd_sound.o \
	objs/cmd_story.o \
	objs/cmd_text.o \
	objs/cmd_time.o \
	objs/cmd_video.o \
	objs/cmd_volume.o \
	objs/x11main.o \
	objs/x11softrender.o \
	objs/bsdsound.o \
	objs/gstplay.o

all: onengine onpack

#
# onengine
#

onengine: libroot-solaris $(OBJS)
	$(CC) -o onengine $(CPPFLAGS) $(CFLAGS) $(OBJS) $(LDFLAGS)

libroot-solaris:
	@../../external/build-libs.sh "solaris" $(CC) "-O2" $(AR)

objs/anime.o: ../../src/anime.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/anime.c

objs/ciel.o: ../../src/ciel.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/ciel.c

objs/conf.o: ../../src/conf.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/conf.c

objs/event.o: ../../src/event.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/event.c

objs/file.o: ../../src/file.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/file.c

objs/glyph.o: ../../src/glyph.c libroot-solaris
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/glyph.c

objs/gui.o: ../../src/gui.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/gui.c

objs/history.o: ../../src/history.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/history.c

objs/image.o: ../../src/image.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/image.c

objs/log.o: ../../src/log.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/log.c

objs/main.o: ../../src/main.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/main.c

objs/mixer.o: ../../src/mixer.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/mixer.c

objs/readimage.o: ../../src/readimage.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/readimage.c

objs/readjpeg.o: ../../src/readjpeg.c libroot-solaris
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/readjpeg.c

objs/readpng.o: ../../src/readpng.c libroot-solaris
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/readpng.c

objs/readwebp.o: ../../src/readwebp.c libroot-solaris
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/readwebp.c

objs/save.o: ../../src/save.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/save.c

objs/script.o: ../../src/script.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/script.c

objs/seen.o: ../../src/seen.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/seen.c

objs/stage.o: ../../src/stage.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/stage.c

objs/vars.o: ../../src/vars.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/vars.c

objs/wave.o: ../../src/wave.c libroot-solaris
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/wave.c

objs/wms_core.o: ../../src/wms_core.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/wms_core.c

objs/wms_impl.o: ../../src/wms_impl.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/wms_impl.c

objs/wms_lexer.yy.o: ../../src/wms_lexer.yy.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/wms_lexer.yy.c

objs/wms_parser.tab.o: ../../src/wms_parser.tab.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/wms_parser.tab.c

objs/cmd_anime.o: ../../src/cmd_anime.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/cmd_anime.c

objs/cmd_bg.o: ../../src/cmd_bg.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/cmd_bg.c

objs/cmd_ch.o: ../../src/cmd_ch.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/cmd_ch.c

objs/cmd_chapter.o: ../../src/cmd_chapter.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/cmd_chapter.c

objs/cmd_chch.o: ../../src/cmd_chch.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/cmd_chch.c

objs/cmd_choose.o: ../../src/cmd_choose.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/cmd_choose.c

objs/cmd_click.o: ../../src/cmd_click.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/cmd_click.c

objs/cmd_config.o: ../../src/cmd_config.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/cmd_config.c

objs/cmd_gosub.o: ../../src/cmd_gosub.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/cmd_gosub.c

objs/cmd_goto.o: ../../src/cmd_goto.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/cmd_goto.c

objs/cmd_if.o: ../../src/cmd_if.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/cmd_if.c

objs/cmd_layer.o: ../../src/cmd_layer.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/cmd_layer.c

objs/cmd_menu.o: ../../src/cmd_menu.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/cmd_menu.c

objs/cmd_message.o: ../../src/cmd_message.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/cmd_message.c

objs/cmd_move.o: ../../src/cmd_move.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/cmd_move.c

objs/cmd_music.o: ../../src/cmd_music.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/cmd_music.c

objs/cmd_plugin.o: ../../src/cmd_plugin.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/cmd_plugin.c

objs/cmd_return.o: ../../src/cmd_return.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/cmd_return.c

objs/cmd_set.o: ../../src/cmd_set.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/cmd_set.c

objs/cmd_shake.o: ../../src/cmd_shake.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/cmd_shake.c

objs/cmd_skip.o: ../../src/cmd_skip.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/cmd_skip.c

objs/cmd_sound.o: ../../src/cmd_sound.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/cmd_sound.c

objs/cmd_story.o: ../../src/cmd_story.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/cmd_story.c

objs/cmd_text.o: ../../src/cmd_text.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/cmd_text.c

objs/cmd_time.o: ../../src/cmd_time.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/cmd_time.c

objs/cmd_video.o: ../../src/cmd_video.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/cmd_video.c

objs/cmd_volume.o: ../../src/cmd_volume.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/cmd_volume.c

objs/x11main.o: ../../src/x11/x11main.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/x11/x11main.c

objs/x11opengl.o: ../../src/x11/x11opengl.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/x11/x11opengl.c

objs/x11vulkan.o: ../../src/x11/x11vulkan.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/x11/x11vulkan.c

objs/x11softrender.o: ../../src/x11/x11softrender.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/x11/x11softrender.c

objs/bsdsound.o: ../../src/bsd/bsdsound.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/bsd/bsdsound.c

objs/gstplay.o: ../../src/x11/gstplay.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) ../../src/x11/gstplay.c

#
# onpack
#

onpack: ../../src/package.c ../../src/log.c
	$(CC) -o onpack -DUSE_EDITOR -DUSE_STANDALONE_PACK -I../../src -O2 -w ../../src/package.c ../../src/log.c

#
# Phony
#

clean:
	@rm -rf onengine onpack objs libroot-solaris errors.txt save tmp *~
