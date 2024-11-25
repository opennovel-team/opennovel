How To Make
===========

## Build
```
make
```

## Run
```
cd ../../games/en-adv
../../engines/openbsd/opennovel-engine
```

## Misc.
* To remove OpenGL support, remove `-DUSE_X11_OPENGL` from CFLAGS and add `-DUSE_X11_SOFTRENDER` to it.
* To add Gstreamer video support, remove `-DUSE_X11_GST` from CFLAGS.
