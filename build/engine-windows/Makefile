CC = i686-w64-mingw32-gcc
CXX = i686-w64-mingw32-g++
AR = i686-w64-mingw32-ar
STRIP = i686-w64-mingw32-strip
WINDRES = i686-w64-mingw32-windres

CPPFLAGS = \
	-DUSE_SSE_DISPATCH \
	-I./res \
	-I./libroot/include \
	-I./libroot/include/freetype2

CFLAGS = \
	-O3 \
	-g0 \
	-fno-exceptions \
	-fno-stack-protector \
	-fomit-frame-pointer \
	-municode \
	-ffast-math \
	-ftree-vectorize \
	-finput-charset=utf-8 \
	-fexec-charset=utf-8 \
	-Wall \
	-Werror \
	-Wextra \
	-Wundef \
	-Wconversion \
	-Wno-unknown-pragmas

CXXFLAGS = \
	-fno-rtti

LDFLAGS = \
	-static-libgcc \
	-static-libstdc++ \
	-Wl,--gc-sections \
	-mwindows \
	-lgdi32 \
	-lole32 \
	-ldsound \
	-ldxguid \
	-lstrmiids \
	-lsapi \
	./libroot/lib/libpng.a \
	./libroot/lib/libjpeg.a \
	./libroot/lib/libwebp.a \
	./libroot/lib/libfreetype.a \
	./libroot/lib/libbz2.a \
	./libroot/lib/libz.a \
	./libroot/lib/libbrotlidec.a \
	./libroot/lib/libbrotlicommon.a \
	./libroot/lib/libvorbis.a \
	./libroot/lib/libogg.a

#
# Sources
#

include ../common.mk

SRCS = \
	$(SRCS_MAIN) \
	$(SRCS_WIN_C) \
	$(SRCS_WIN_CC) \
	res/resource.rc

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
	objs/avx2.o \
	objs/avx.o \
	objs/sse42.o \
	objs/sse4.o \
	objs/sse3.o \
	objs/sse2.o \
	objs/sse.o \
	objs/scalar.o \
	objs/cpuid.o \
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
	objs/winmain.o \
	objs/dsound.o \
	objs/d3drender.o \
	objs/d3d12render.o \
	objs/d3d11render.o \
	objs/d3d9render.o \
	objs/gdirender.o \
	objs/dsvideo.o \
	objs/tts_sapi.o \
	objs/resource.o

all: engine.exe pack.exe

#
# engine.exe
#

engine.exe: libroot $(OBJS) $(HDRS_MAIN) $(HDRS)
	@$(CXX) -o engine.exe $(OBJS) $(CFLAGS) $(LDFLAGS)
	@$(STRIP) --strip-all engine.exe

libroot:
	@../../external/build-libs.sh "" $(CC) "-O3 -g0 -s -fno-stack-protector -fomit-frame-pointer -msse3 -ffast-math -ftree-vectorize -ffunction-sections -fdata-sections" $(AR)

dx12headers:
	git clone https://github.com/microsoft/DirectX-Headers.git dx12headers

objs/anime.o: ../../src/anime.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/ciel.o: ../../src/ciel.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/conf.o: ../../src/conf.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/event.o: ../../src/event.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/file.o: ../../src/file.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/glyph.o: ../../src/glyph.c libroot
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/gui.o: ../../src/gui.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/history.o: ../../src/history.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/image.o: ../../src/image.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/log.o: ../../src/log.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/main.o: ../../src/main.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/mixer.o: ../../src/mixer.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/readimage.o: ../../src/readimage.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/readjpeg.o: ../../src/readjpeg.c libroot
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/readpng.o: ../../src/readpng.c libroot
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/readwebp.o: ../../src/readwebp.c libroot
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/save.o: ../../src/save.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/script.o: ../../src/script.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/seen.o: ../../src/seen.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/stage.o: ../../src/stage.c libroot
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/vars.o: ../../src/vars.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/wave.o: ../../src/wave.c libroot
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/avx2.o: ../../src/sse/avx2.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) -mavx2 $<

objs/avx.o: ../../src/sse/avx.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) -mavx $<

objs/sse42.o: ../../src/sse/sse42.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) -msse4.2 $<

objs/sse4.o: ../../src/sse/sse4.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) -msse4 $<

objs/sse3.o: ../../src/sse/sse3.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) -msse3 $<

objs/sse2.o: ../../src/sse/sse2.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) -msse2 $<

objs/sse.o: ../../src/sse/sse.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) -msse $<

objs/scalar.o: ../../src/sse/scalar.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/cpuid.o: ../../src/sse/cpuid.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/wms_core.o: ../../src/wms_core.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/wms_impl.o: ../../src/wms_impl.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/wms_lexer.yy.o: ../../src/wms_lexer.yy.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/wms_parser.tab.o: ../../src/wms_parser.tab.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/cmd_anime.o: ../../src/cmd_anime.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/cmd_bg.o: ../../src/cmd_bg.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/cmd_ch.o: ../../src/cmd_ch.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/cmd_chapter.o: ../../src/cmd_chapter.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/cmd_chch.o: ../../src/cmd_chch.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/cmd_choose.o: ../../src/cmd_choose.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/cmd_click.o: ../../src/cmd_click.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/cmd_config.o: ../../src/cmd_config.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/cmd_gosub.o: ../../src/cmd_gosub.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/cmd_goto.o: ../../src/cmd_goto.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/cmd_if.o: ../../src/cmd_if.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/cmd_layer.o: ../../src/cmd_layer.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/cmd_menu.o: ../../src/cmd_menu.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/cmd_message.o: ../../src/cmd_message.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/cmd_move.o: ../../src/cmd_move.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/cmd_music.o: ../../src/cmd_music.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/cmd_plugin.o: ../../src/cmd_plugin.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/cmd_return.o: ../../src/cmd_return.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/cmd_set.o: ../../src/cmd_set.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/cmd_shake.o: ../../src/cmd_shake.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/cmd_skip.o: ../../src/cmd_skip.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/cmd_sound.o: ../../src/cmd_sound.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/cmd_story.o: ../../src/cmd_story.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/cmd_text.o: ../../src/cmd_text.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/cmd_time.o: ../../src/cmd_time.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/cmd_video.o: ../../src/cmd_video.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/cmd_volume.o: ../../src/cmd_volume.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/winmain.o: ../../src/microsoft/winmain.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/dsound.o: ../../src/microsoft/dsound.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/d3drender.o: ../../src/microsoft/d3drender.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/d3d12render.o: ../../src/microsoft/d3d12render.cc dx12headers
	mkdir -p objs
	$(CXX) -o $@ -c $(CPPFLAGS) -I./dx12headers/include/directx -I./dx12headers/include/dxguids -DWINAPI_PARTITION_GAMES $(CFLAGS) $(CXXFLAGS) $<

objs/d3d11render.o: ../../src/microsoft/d3d11render.cc
	mkdir -p objs
	$(CXX) -o $@ -c $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) $<

objs/d3d9render.o: ../../src/microsoft/d3d9render.cc
	mkdir -p objs
	$(CXX) -o $@ -c $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) $<

objs/gdirender.o: ../../src/microsoft/gdirender.c
	mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

objs/dsvideo.o: ../../src/microsoft/dsvideo.cc
	mkdir -p objs
	$(CXX) -o $@ -c $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) $<

objs/tts_sapi.o: ../../src/microsoft/tts_sapi.cc
	mkdir -p objs
	$(CXX) -o $@ -c $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) $<

objs/resource.o: res/resource.rc
	mkdir -p objs
	$(WINDRES) $< $@

#
# pack.exe
#

pack.exe: ../../src/package.c ../../src/log.c
	$(CC) -o pack.exe -DUSE_EDITOR -DUSE_STANDALONE_PACK -I../../src -O2 -w -municode ../../src/package.c ../../src/log.c

#
# Phony
#

setup:
	sudo apt-get install mingw-w64

clean:
	@rm -rf objs engine.exe pack.exe libroot dx12headers errors.txt save tmp *~
