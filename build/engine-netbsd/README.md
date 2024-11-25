How To Make
===========

## Build
Before building this software, please install some packages.
```
make
```

## Run
```
cd ../../games/en-adv
../../engines/netbsd/opennovel-engine
```

## Misc.
* To remove OpenGL support, remove `-DUSE_X11_OPENGL` from CFLAGS and add `-DUSE_X11_SOFTRENDER` to it.
* To add Gstreamer video support, add `-DUSE_X11_GST` from CFLAGS.
