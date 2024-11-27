@echo off

echo Removing directories...
rd /s /q libroot > NUL 2>&1
rd /s /q zlib > NUL 2>&1
rd /s /q libpng > NUL 2>&1
rd /s /q jpeg > NUL 2>&1
rd /s /q libogg > NUL 2>&1
rd /s /q libvorbis > NUL 2>&1
rd /s /q freetype > NUL 2>&1
rd /s /q bzip2 > NUL 2>&1
rd /s /q libwebp > NUL 2>&1

echo Making target directories...
mkdir libroot
mkdir libroot\include
mkdir libroot\lib

echo Extracting zlib...
tar -xzf ../../external/zlib-1.2.11.tar.gz
ren zlib-1.2.11 zlib
cd zlib
cl.exe /c /MT /O2 adler32.c
cl.exe /c /MT /O2 infback.c
cl.exe /c /MT /O2 trees.c
cl.exe /c /MT /O2 compress.c
cl.exe /c /MT /O2 inffast.c
cl.exe /c /MT /O2 uncompr.c
cl.exe /c /MT /O2 crc32.c
cl.exe /c /MT /O2 inflate.c
cl.exe /c /MT /O2 deflate.c
cl.exe /c /MT /O2 inftrees.c
cl.exe /c /MT /O2 zutil.c
lib.exe /OUT:zlib.lib adler32.obj infback.obj trees.obj compress.obj inffast.obj uncompr.obj crc32.obj inflate.obj deflate.obj inftrees.obj zutil.obj
copy zlib.h ..\libroot\include\
copy zconf.h ..\libroot\include\
copy zlib.lib ..\libroot\lib\
cd ..
rd /s /q zlib > NUL 2>&1

echo Building libpng...
tar -xzf ../../external/libpng-1.6.43.tar.gz
ren libpng-1.6.43 libpng
cd libpng
copy scripts\pnglibconf.h.prebuilt pnglibconf.h
cl.exe /c /MT /O2 /I..\libroot\include pngget.c
cl.exe /c /MT /O2 /I..\libroot\include pngread.c
cl.exe /c /MT /O2 /I..\libroot\include pngrutil.c
cl.exe /c /MT /O2 /I..\libroot\include pngtrans.c
cl.exe /c /MT /O2 /I..\libroot\include pngwtran.c
cl.exe /c /MT /O2 /I..\libroot\include png.c
cl.exe /c /MT /O2 /I..\libroot\include pngmem.c
cl.exe /c /MT /O2 /I..\libroot\include pngrio.c
cl.exe /c /MT /O2 /I..\libroot\include pngset.c
cl.exe /c /MT /O2 /I..\libroot\include pngwio.c
cl.exe /c /MT /O2 /I..\libroot\include pngwutil.c
cl.exe /c /MT /O2 /I..\libroot\include pngerror.c
cl.exe /c /MT /O2 /I..\libroot\include pngpread.c
cl.exe /c /MT /O2 /I..\libroot\include pngrtran.c
cl.exe /c /MT /O2 /I..\libroot\include pngwrite.c
lib.exe /OUT:libpng.lib pngget.obj pngread.obj pngrutil.obj pngtrans.obj pngwtran.obj png.obj pngmem.obj pngrio.obj pngset.obj pngwio.obj pngwutil.obj pngerror.obj pngpread.obj pngrtran.obj pngwrite.obj
mkdir ..\libroot\include\png
copy *.h ..\libroot\include\png\
copy libpng.lib ..\libroot\lib\
cd ..
rd /s /q libpng > NUL 2>&1

echo Building jpeg...
tar -xzf ../../external/jpegsrc.v9e.tar.gz
ren jpeg-9e jpeg
cd jpeg
copy jconfig.txt jconfig.h
cl.exe /c /MT /O2 cdjpeg.c
cl.exe /c /MT /O2 jaricom.c
cl.exe /c /MT /O2 jcapimin.c
cl.exe /c /MT /O2 jcapistd.c
cl.exe /c /MT /O2 jcarith.c
cl.exe /c /MT /O2 jccoefct.c
cl.exe /c /MT /O2 jccolor.c
cl.exe /c /MT /O2 jcdctmgr.c
cl.exe /c /MT /O2 jchuff.c
cl.exe /c /MT /O2 jcinit.c
cl.exe /c /MT /O2 jcmainct.c
cl.exe /c /MT /O2 jcmarker.c
cl.exe /c /MT /O2 jcmaster.c
cl.exe /c /MT /O2 jcomapi.c
cl.exe /c /MT /O2 jcparam.c
cl.exe /c /MT /O2 jcprepct.c
cl.exe /c /MT /O2 jcsample.c
cl.exe /c /MT /O2 jctrans.c
cl.exe /c /MT /O2 jdapimin.c
cl.exe /c /MT /O2 jdapistd.c
cl.exe /c /MT /O2 jdarith.c
cl.exe /c /MT /O2 jdatadst.c
cl.exe /c /MT /O2 jdatasrc.c
cl.exe /c /MT /O2 jdcoefct.c
cl.exe /c /MT /O2 jdcolor.c
cl.exe /c /MT /O2 jddctmgr.c
cl.exe /c /MT /O2 jdhuff.c
cl.exe /c /MT /O2 jdinput.c
cl.exe /c /MT /O2 jdmainct.c
cl.exe /c /MT /O2 jdmarker.c
cl.exe /c /MT /O2 jdmaster.c
cl.exe /c /MT /O2 jdmerge.c
cl.exe /c /MT /O2 jdpostct.c
cl.exe /c /MT /O2 jdsample.c
cl.exe /c /MT /O2 jdtrans.c
cl.exe /c /MT /O2 jerror.c
cl.exe /c /MT /O2 jfdctflt.c
cl.exe /c /MT /O2 jfdctfst.c
cl.exe /c /MT /O2 jfdctint.c
cl.exe /c /MT /O2 jidctflt.c
cl.exe /c /MT /O2 jidctfst.c
cl.exe /c /MT /O2 jidctint.c
cl.exe /c /MT /O2 jmemansi.c
cl.exe /c /MT /O2 jmemmgr.c
cl.exe /c /MT /O2 jquant1.c
cl.exe /c /MT /O2 jquant2.c
cl.exe /c /MT /O2 jutils.c
cl.exe /c /MT /O2 transupp.c
lib.exe /OUT:jpeg.lib cdjpeg.obj jaricom.obj jcapimin.obj jcapistd.obj jcarith.obj jccoefct.obj jccolor.obj jcdctmgr.obj jchuff.obj jcinit.obj jcmainct.obj jcmarker.obj jcmaster.obj jcomapi.obj jcparam.obj jcprepct.obj jcsample.obj jctrans.obj jdapimin.obj jdapistd.obj jdarith.obj jdatadst.obj jdatasrc.obj jdcoefct.obj jdcolor.obj jddctmgr.obj jdhuff.obj jdinput.obj jdmainct.obj jdmarker.obj jdmaster.obj jdmerge.obj jdpostct.obj jdsample.obj jdtrans.obj jerror.obj jfdctflt.obj jfdctfst.obj jfdctint.obj jidctflt.obj jidctfst.obj jidctint.obj jmemansi.obj jmemmgr.obj jquant1.obj jquant2.obj jutils.obj transupp.obj
mkdir ..\libroot\include\jpeg
copy *.h ..\libroot\include\jpeg\
copy jpeg.lib ..\libroot\lib\
cd ..
rd /s /q jpeg > NUL 2>&1

echo Building bzip2...
tar -xzf ../../external/bzip2-1.0.6.tar.gz
ren bzip2-1.0.6 bzip2
cd bzip2
cl.exe /c /MT /O2 unzcrash.c
cl.exe /c /MT /O2 blocksort.c
cl.exe /c /MT /O2 compress.c
cl.exe /c /MT /O2 decompress.c
cl.exe /c /MT /O2 huffman.c
cl.exe /c /MT /O2 randtable.c
cl.exe /c /MT /O2 bzlib.c
cl.exe /c /MT /O2 crctable.c
lib.exe /OUT:libbz2.lib unzcrash.obj blocksort.obj compress.obj decompress.obj huffman.obj randtable.obj bzlib.obj crctable.obj
copy bzlib.h ..\libroot\include\
copy libbz2.lib ..\libroot\lib\
cd ..
rd /s /q bzip2 > NUL 2>&1

echo Building libwebp...
tar -xzf ../../external/libwebp-1.3.2.tar.gz
ren libwebp-1.3.2 libwebp
cd libwebp
cl.exe /c /MT /O2 /I.\ src\dec\alpha_dec.c
cl.exe /c /MT /O2 /I.\ src\dec\buffer_dec.c
cl.exe /c /MT /O2 /I.\ src\dec\frame_dec.c
cl.exe /c /MT /O2 /I.\ src\dec\idec_dec.c
cl.exe /c /MT /O2 /I.\ src\dec\io_dec.c
cl.exe /c /MT /O2 /I.\ src\dec\quant_dec.c
cl.exe /c /MT /O2 /I.\ src\dec\tree_dec.c
cl.exe /c /MT /O2 /I.\ src\dec\vp8_dec.c
cl.exe /c /MT /O2 /I.\ src\dec\vp8l_dec.c
cl.exe /c /MT /O2 /I.\ src\dec\webp_dec.c
cl.exe /c /MT /O2 /I.\ src\demux\anim_decode.c
cl.exe /c /MT /O2 /I.\ src\demux\demux.c
cl.exe /c /MT /O2 /I.\ src\dsp\alpha_processing.c
cl.exe /c /MT /O2 /I.\ src\dsp\alpha_processing_sse2.c
cl.exe /c /MT /O2 /I.\ src\dsp\alpha_processing_sse41.c
cl.exe /c /MT /O2 /I.\ src\dsp\cost.c
cl.exe /c /MT /O2 /I.\ src\dsp\cost_neon.c
cl.exe /c /MT /O2 /I.\ src\dsp\cost_sse2.c
cl.exe /c /MT /O2 /I.\ src\dsp\cpu.c
cl.exe /c /MT /O2 /I.\ src\dsp\dec.c
cl.exe /c /MT /O2 /I.\ src\dsp\dec_neon.c
cl.exe /c /MT /O2 /I.\ src\dsp\dec_sse2.c
cl.exe /c /MT /O2 /I.\ src\dsp\dec_sse41.c
cl.exe /c /MT /O2 /I.\ src\dsp\dec_clip_tables.c
cl.exe /c /MT /O2 /I.\ src\dsp\enc.c
cl.exe /c /MT /O2 /I.\ src\dsp\filters.c
cl.exe /c /MT /O2 /I.\ src\dsp\filters_neon.c
cl.exe /c /MT /O2 /I.\ src\dsp\filters_sse2.c
cl.exe /c /MT /O2 /I.\ src\dsp\lossless.c
cl.exe /c /MT /O2 /I.\ src\dsp\lossless_neon.c
cl.exe /c /MT /O2 /I.\ src\dsp\lossless_sse2.c
cl.exe /c /MT /O2 /I.\ src\dsp\lossless_sse41.c
cl.exe /c /MT /O2 /I.\ src\dsp\lossless_enc.c
cl.exe /c /MT /O2 /I.\ src\dsp\lossless_enc_neon.c
cl.exe /c /MT /O2 /I.\ src\dsp\lossless_enc_sse2.c
cl.exe /c /MT /O2 /I.\ src\dsp\lossless_enc_sse41.c
cl.exe /c /MT /O2 /I.\ src\dsp\rescaler.c
cl.exe /c /MT /O2 /I.\ src\dsp\rescaler_neon.c
cl.exe /c /MT /O2 /I.\ src\dsp\rescaler_sse2.c
cl.exe /c /MT /O2 /I.\ src\dsp\ssim.c
cl.exe /c /MT /O2 /I.\ src\dsp\ssim_sse2.c
cl.exe /c /MT /O2 /I.\ src\dsp\upsampling.c
cl.exe /c /MT /O2 /I.\ src\dsp\upsampling_neon.c
cl.exe /c /MT /O2 /I.\ src\dsp\upsampling_sse2.c
cl.exe /c /MT /O2 /I.\ src\dsp\upsampling_sse41.c
cl.exe /c /MT /O2 /I.\ src\dsp\yuv.c
cl.exe /c /MT /O2 /I.\ src\dsp\yuv_neon.c
cl.exe /c /MT /O2 /I.\ src\dsp\yuv_sse2.c
cl.exe /c /MT /O2 /I.\ src\dsp\yuv_sse41.c
cl.exe /c /MT /O2 /I.\ src\enc\alpha_enc.c
cl.exe /c /MT /O2 /I.\ src\enc\analysis_enc.c
cl.exe /c /MT /O2 /I.\ src\enc\backward_references_cost_enc.c
cl.exe /c /MT /O2 /I.\ src\enc\backward_references_enc.c
cl.exe /c /MT /O2 /I.\ src\enc\config_enc.c
cl.exe /c /MT /O2 /I.\ src\enc\cost_enc.c
cl.exe /c /MT /O2 /I.\ src\enc\filter_enc.c
cl.exe /c /MT /O2 /I.\ src\enc\frame_enc.c
cl.exe /c /MT /O2 /I.\ src\enc\histogram_enc.c
cl.exe /c /MT /O2 /I.\ src\enc\iterator_enc.c
cl.exe /c /MT /O2 /I.\ src\enc\near_lossless_enc.c
cl.exe /c /MT /O2 /I.\ src\enc\picture_csp_enc.c
cl.exe /c /MT /O2 /I.\ src\enc\picture_enc.c
cl.exe /c /MT /O2 /I.\ src\enc\picture_psnr_enc.c
cl.exe /c /MT /O2 /I.\ src\enc\picture_rescale_enc.c
cl.exe /c /MT /O2 /I.\ src\enc\picture_tools_enc.c
cl.exe /c /MT /O2 /I.\ src\enc\predictor_enc.c
cl.exe /c /MT /O2 /I.\ src\enc\quant_enc.c
cl.exe /c /MT /O2 /I.\ src\enc\syntax_enc.c
cl.exe /c /MT /O2 /I.\ src\enc\token_enc.c
cl.exe /c /MT /O2 /I.\ src\enc\tree_enc.c
cl.exe /c /MT /O2 /I.\ src\enc\vp8l_enc.c
cl.exe /c /MT /O2 /I.\ src\enc\webp_enc.c
cl.exe /c /MT /O2 /I.\ src\mux\anim_encode.c
cl.exe /c /MT /O2 /I.\ src\mux\muxedit.c
cl.exe /c /MT /O2 /I.\ src\mux\muxinternal.c
cl.exe /c /MT /O2 /I.\ src\mux\muxread.c
cl.exe /c /MT /O2 /I.\ src\utils\bit_reader_utils.c
cl.exe /c /MT /O2 /I.\ src\utils\bit_writer_utils.c
cl.exe /c /MT /O2 /I.\ src\utils\color_cache_utils.c
cl.exe /c /MT /O2 /I.\ src\utils\filters_utils.c
cl.exe /c /MT /O2 /I.\ src\utils\huffman_encode_utils.c
cl.exe /c /MT /O2 /I.\ src\utils\huffman_utils.c
cl.exe /c /MT /O2 /I.\ src\utils\quant_levels_dec_utils.c
cl.exe /c /MT /O2 /I.\ src\utils\quant_levels_utils.c
cl.exe /c /MT /O2 /I.\ src\utils\random_utils.c
cl.exe /c /MT /O2 /I.\ src\utils\rescaler_utils.c
cl.exe /c /MT /O2 /I.\ src\utils\thread_utils.c
cl.exe /c /MT /O2 /I.\ src\utils\utils.c
lib.exe /OUT:libwebp.lib alpha_dec.obj buffer_dec.obj frame_dec.obj idec_dec.obj io_dec.obj quant_dec.obj tree_dec.obj vp8_dec.obj vp8l_dec.obj webp_dec.obj anim_decode.obj demux.obj alpha_processing.obj cost.obj cost_neon.obj cost_sse2.obj cpu.obj dec.obj dec_neon.obj dec_sse2.obj dec_sse41.obj dec_clip_tables.obj enc.obj filters.obj filters_neon.obj filters_sse2.obj lossless.obj lossless_neon.obj lossless_sse2.obj lossless_sse41.obj lossless_enc.obj lossless_enc_neon.obj lossless_enc_sse2.obj lossless_enc_sse41.obj rescaler.obj rescaler_neon.obj rescaler_sse2.obj ssim.obj ssim_sse2.obj upsampling.obj upsampling_neon.obj upsampling_sse2.obj upsampling_sse41.obj yuv.obj yuv_neon.obj yuv_sse2.obj yuv_sse41.obj alpha_enc.obj analysis_enc.obj backward_references_cost_enc.obj backward_references_enc.obj config_enc.obj cost_enc.obj filter_enc.obj frame_enc.obj histogram_enc.obj iterator_enc.obj near_lossless_enc.obj picture_csp_enc.obj picture_enc.obj picture_psnr_enc.obj picture_rescale_enc.obj picture_tools_enc.obj predictor_enc.obj quant_enc.obj syntax_enc.obj token_enc.obj tree_enc.obj vp8l_enc.obj webp_enc.obj anim_encode.obj muxedit.obj muxinternal.obj muxread.obj bit_reader_utils.obj bit_writer_utils.obj color_cache_utils.obj filters_utils.obj huffman_encode_utils.obj huffman_utils.obj quant_levels_dec_utils.obj quant_levels_utils.obj random_utils.obj rescaler_utils.obj thread_utils.obj utils.obj alpha_processing_sse2.obj alpha_processing_sse41.obj
mkdir ..\libroot\include\webp
copy src\webp\* ..\libroot\include\webp\
copy libwebp.lib ..\libroot\lib\
cd ..
rd /s /q libwebp > NUL 2>&1

echo Building libogg...
tar -xzf ../../external/libogg-1.3.3.tar.gz
ren libogg-1.3.3 libogg
cd libogg
cl.exe /c /MT /O2 /I.\include src\bitwise.c
cl.exe /c /MT /O2 /I.\include src\framing.c
lib.exe /OUT:libogg.lib bitwise.obj framing.obj
mkdir ..\libroot\include\ogg
xcopy include\ogg ..\libroot\include\ogg
copy libogg.lib ..\libroot\lib\
cd ..
rd /s /q libogg > NUL 2>&1

echo Building libvorbis...
tar -xzf ../../external/libvorbis-1.3.6.tar.gz
ren libvorbis-1.3.6 libvorbis
cd libvorbis
cl.exe /c /MT /O2 /I.\include /I.\lib /I..\libroot\include lib/analysis.c
cl.exe /c /MT /O2 /I.\include /I.\lib /I..\libroot\include lib/barkmel.c
cl.exe /c /MT /O2 /I.\include /I.\lib /I..\libroot\include lib/bitrate.c
cl.exe /c /MT /O2 /I.\include /I.\lib /I..\libroot\include lib/block.c
cl.exe /c /MT /O2 /I.\include /I.\lib /I..\libroot\include lib/codebook.c
cl.exe /c /MT /O2 /I.\include /I.\lib /I..\libroot\include lib/envelope.c
cl.exe /c /MT /O2 /I.\include /I.\lib /I..\libroot\include lib/floor0.c
cl.exe /c /MT /O2 /I.\include /I.\lib /I..\libroot\include lib/floor1.c
cl.exe /c /MT /O2 /I.\include /I.\lib /I..\libroot\include lib/info.c
cl.exe /c /MT /O2 /I.\include /I.\lib /I..\libroot\include lib/lookup.c
cl.exe /c /MT /O2 /I.\include /I.\lib /I..\libroot\include lib/lpc.c
cl.exe /c /MT /O2 /I.\include /I.\lib /I..\libroot\include lib/lsp.c
cl.exe /c /MT /O2 /I.\include /I.\lib /I..\libroot\include lib/mapping0.c
cl.exe /c /MT /O2 /I.\include /I.\lib /I..\libroot\include lib/mdct.c
cl.exe /c /MT /O2 /I.\include /I.\lib /I..\libroot\include lib/psy.c
cl.exe /c /MT /O2 /I.\include /I.\lib /I..\libroot\include lib/registry.c
cl.exe /c /MT /O2 /I.\include /I.\lib /I..\libroot\include lib/res0.c
cl.exe /c /MT /O2 /I.\include /I.\lib /I..\libroot\include lib/sharedbook.c
cl.exe /c /MT /O2 /I.\include /I.\lib /I..\libroot\include lib/smallft.c
cl.exe /c /MT /O2 /I.\include /I.\lib /I..\libroot\include lib/synthesis.c
rem cl.exe /c /MT /O2 /I.\include /I.\lib /I..\libroot\include lib/tone.c
cl.exe /c /MT /O2 /I.\include /I.\lib /I..\libroot\include lib/vorbisenc.c
cl.exe /c /MT /O2 /I.\include /I.\lib /I..\libroot\include lib/vorbisfile.c
cl.exe /c /MT /O2 /I.\include /I.\lib /I..\libroot\include lib/window.c
rem lib.exe /OUT:libvorbis.lib analysis.obj barkmel.obj bitrate.obj block.obj codebook.obj envelope.obj floor0.obj floor1.obj info.obj lookup.obj lpc.obj lsp.obj mapping0.obj mdct.obj psy.obj registry.obj res0.obj sharedbook.obj smallft.obj synthesis.obj tone.obj vorbisenc.obj vorbisfile.obj window.obj
lib.exe /OUT:libvorbis.lib analysis.obj barkmel.obj bitrate.obj block.obj codebook.obj envelope.obj floor0.obj floor1.obj info.obj lookup.obj lpc.obj lsp.obj mapping0.obj mdct.obj psy.obj registry.obj res0.obj sharedbook.obj smallft.obj synthesis.obj vorbisenc.obj vorbisfile.obj window.obj
mkdir ..\libroot\include\vorbis
xcopy include\vorbis ..\libroot\include\vorbis
copy libvorbis.lib ..\libroot\lib\
cd ..
rd /s /q libvorbis > NUL 2>&1

echo Building freetype...
tar -xzf ../../external/freetype-2.13.2.tar.gz
ren freetype-2.13.2 freetype
cd freetype
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I..\libroot\include src/base/ftadvanc.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I..\libroot\include src/base/ftbase.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I..\libroot\include src/base/ftbbox.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I..\libroot\include src/base/ftbdf.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I..\libroot\include src/base/ftbitmap.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/ftcalc.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/ftcid.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/ftcolor.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/ftdbgmem.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/ftdebug.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/fterrors.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/ftfntfmt.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/ftfstype.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/ftgasp.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/ftgloadr.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/ftglyph.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/ftgxval.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/fthash.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/ftinit.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/ftlcdfil.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/ftmac.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/ftmm.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/ftobjs.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/ftotval.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/ftoutln.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/ftpatent.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/ftpfr.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/ftpsprop.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/ftrfork.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/ftsnames.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/ftstream.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/ftstroke.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/ftsynth.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/ftsystem.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/fttrigon.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/fttype1.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/ftutil.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/ftwinfnt.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/base/md5.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/bdf/bdf.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/bdf/bdfdrivr.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/bdf/bdflib.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/bzip2/ftbzip2.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/cache/ftcache.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/cache/ftcbasic.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/cache/ftccache.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/cache/ftccmap.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/cache/ftcglyph.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/cache/ftcimage.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/cache/ftcmanag.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/cache/ftcmru.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/cache/ftcsbits.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/cff/cff.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/cff/cffcmap.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/cff/cffdrivr.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/cff/cffgload.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/cff/cffload.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/cff/cffobjs.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/cff/cffparse.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/cid/cidgload.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/cid/cidload.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/cid/cidobjs.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/cid/cidparse.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/cid/cidriver.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/cid/type1cid.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/otvalid/otvalid.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/otvalid/otvbase.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/otvalid/otvcommn.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/otvalid/otvgdef.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/otvalid/otvgpos.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/otvalid/otvgsub.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/otvalid/otvjstf.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/otvalid/otvmath.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/otvalid/otvmod.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/pfr/pfr.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/pfr/pfrcmap.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/pfr/pfrdrivr.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/pfr/pfrgload.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/pfr/pfrload.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/pfr/pfrobjs.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/pfr/pfrsbit.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/psaux/afmparse.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/psaux/cffdecode.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/psaux/psarrst.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/psaux/psaux.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/psaux/psauxmod.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/psaux/psblues.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/psaux/psconv.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/psaux/pserror.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/psaux/psfont.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/psaux/psft.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/psaux/pshints.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/psaux/psintrp.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/psaux/psobjs.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/psaux/psread.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/psaux/psstack.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/psaux/t1decode.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/psaux/t1cmap.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/pshinter/pshalgo.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/pshinter/pshglob.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/pshinter/pshinter.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/pshinter/pshmod.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/pshinter/pshrec.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/psnames/psmodule.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/psnames/psnames.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/raster/ftraster.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/sdf/ftbsdf.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/sdf/ftsdf.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/sdf/ftsdfcommon.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/sdf/ftsdfrend.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/sfnt/pngshim.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/sfnt/sfdriver.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/sfnt/sfobjs.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/sfnt/ttbdf.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/sfnt/ttcmap.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/sfnt/ttcolr.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/sfnt/ttcpal.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/sfnt/ttkern.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/sfnt/ttload.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/sfnt/ttmtx.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/sfnt/ttpost.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/sfnt/ttsbit.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/sfnt/ttsvg.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/sfnt/sfwoff.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/smooth/ftgrays.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/smooth/ftsmooth.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/svg/ftsvg.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/truetype/truetype.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/truetype/ttdriver.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/truetype/ttgload.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/truetype/ttgxvar.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/truetype/ttinterp.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/truetype/ttobjs.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/truetype/ttpload.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/winfonts/winfnt.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/gzip/adler32.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/gzip/crc32.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/gzip/ftgzip.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/gzip/inffast.c
rem cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/gzip/inflate.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/gzip/inftrees.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/gzip/zutil.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/lzw/ftlzw.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/pcf/pcf.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/autofit/autofit.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/type1/type1.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/type42/type42.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/raster/raster.c
cl.exe /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I.\include /I..\libroot\include src/svg/svg.c
rem lib.exe /OUT:freetype.lib ftadvanc.obj ftbase.obj ftbbox.obj ftbdf.obj ftbitmap.obj ftcalc.obj ftcid.obj ftcolor.obj ftdbgmem.obj ftdebug.obj fterrors.obj ftfntfmt.obj ftfstype.obj ftgasp.obj ftgloadr.obj ftglyph.obj ftgxval.obj fthash.obj ftinit.obj ftlcdfil.obj ftmac.obj ftmm.obj ftobjs.obj ftotval.obj ftoutln.obj ftpatent.obj ftpfr.obj ftpsprop.obj ftrfork.obj ftsnames.obj ftstream.obj ftstroke.obj ftsynth.obj ftsystem.obj fttrigon.obj fttype1.obj ftutil.obj ftwinfnt.obj md5.obj bdf.obj bdfdrivr.obj bdflib.obj ftbzip2.obj ftcache.obj ftcbasic.obj ftccache.obj ftccmap.obj ftcglyph.obj ftcimage.obj ftcmanag.obj ftcmru.obj ftcsbits.obj cff.obj cffcmap.obj cffdrivr.obj cffgload.obj cffload.obj cffobjs.obj cffparse.obj cidgload.obj cidload.obj cidobjs.obj cidparse.obj cidriver.obj type1cid.obj otvalid.obj otvbase.obj otvcommn.obj otvgdef.obj otvgpos.obj otvgsub.obj otvjstf.obj otvmath.obj otvmod.obj pfr.obj pfrcmap.obj pfrdrivr.obj pfrgload.obj pfrload.obj pfrobjs.obj pfrsbit.obj afmparse.obj cffdecode.obj psarrst.obj psaux.obj psauxmod.obj psblues.obj psconv.obj pserror.obj psfont.obj psft.obj pshints.obj psintrp.obj psobjs.obj psread.obj psstack.obj pshalgo.obj pshglob.obj pshinter.obj pshmod.obj pshrec.obj psmodule.obj psnames.obj ftraster.obj ftbsdf.obj ftsdf.obj ftsdfcommon.obj ftsdfrend.obj pngshim.obj sfdriver.obj sfobjs.obj ttbdf.obj ttcmap.obj ttcolr.obj ttcpal.obj ttkern.obj ttload.obj ttmtx.obj ttpost.obj ttsbit.obj ttsvg.obj sfwoff.obj ftgrays.obj ftsmooth.obj ftsvg.obj truetype.obj ttdriver.obj ttgload.obj ttgxvar.obj ttinterp.obj ttobjs.obj ttpload.obj winfnt.obj adler32.obj crc32.obj ftgzip.obj inffast.obj inflate.obj inftrees.obj zutil.obj ftlzw.obj pcf.obj autofit.obj type1.obj type42.obj raster.obj svg.obj
lib.exe /OUT:freetype.lib ftadvanc.obj ftbase.obj ftbbox.obj ftbdf.obj ftbitmap.obj ftcalc.obj ftcid.obj ftcolor.obj ftdbgmem.obj ftdebug.obj fterrors.obj ftfntfmt.obj ftfstype.obj ftgasp.obj ftgloadr.obj ftglyph.obj ftgxval.obj fthash.obj ftinit.obj ftlcdfil.obj ftmac.obj ftmm.obj ftotval.obj ftoutln.obj ftpatent.obj ftpfr.obj ftpsprop.obj ftrfork.obj ftsnames.obj ftstream.obj ftstroke.obj ftsynth.obj ftsystem.obj fttrigon.obj fttype1.obj ftutil.obj ftwinfnt.obj md5.obj bdfdrivr.obj bdflib.obj ftbzip2.obj ftcbasic.obj ftccache.obj ftccmap.obj ftcglyph.obj ftcimage.obj ftcmanag.obj ftcmru.obj ftcsbits.obj cffcmap.obj cffdrivr.obj cffgload.obj cffload.obj cffobjs.obj cffparse.obj cidgload.obj cidload.obj cidobjs.obj cidparse.obj type1cid.obj otvalid.obj otvbase.obj otvcommn.obj otvgdef.obj otvgpos.obj otvgsub.obj otvjstf.obj otvmath.obj pfrcmap.obj pfrdrivr.obj pfrgload.obj pfrload.obj pfrobjs.obj pfrsbit.obj afmparse.obj cffdecode.obj psarrst.obj psauxmod.obj psblues.obj psconv.obj pserror.obj psfont.obj psft.obj pshints.obj psintrp.obj psobjs.obj psread.obj psstack.obj pshalgo.obj pshglob.obj pshmod.obj pshrec.obj psmodule.obj t1decode.obj t1cmap.obj ftraster.obj ftbsdf.obj ftsdf.obj ftsdfcommon.obj ftsdfrend.obj pngshim.obj sfdriver.obj sfobjs.obj ttbdf.obj ttcmap.obj ttcolr.obj ttcpal.obj ttkern.obj ttload.obj ttmtx.obj ttpost.obj ttsbit.obj ttsvg.obj sfwoff.obj ftgrays.obj ftsmooth.obj ftsvg.obj ttdriver.obj ttgload.obj ttgxvar.obj ttinterp.obj ttobjs.obj ttpload.obj winfnt.obj adler32.obj crc32.obj ftgzip.obj inffast.obj inftrees.obj zutil.obj ftlzw.obj pcf.obj autofit.obj type1.obj type42.obj raster.obj
mkdir ..\libroot\include\freetype
mkdir ..\libroot\include\freetype\config
xcopy include\freetype ..\libroot\include\freetype
xcopy include\freetype\config ..\libroot\include\freetype\config
copy include\ft2build.h ..\libroot\include\
copy freetype.lib ..\libroot\lib\
cd ..
rd /s /q freetype > NUL 2>&1
