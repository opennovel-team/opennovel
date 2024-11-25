How To Make
===========

## Prerequisite
Before building this software, please install some packages.
```
make setup
```

## Build
```
make
```

## Run
```
cd ../../games/en-adv
../../engines/linux/opennovel-engine
```

## Misc.
* To remove OpenGL support, remove `-DUSE_X11_OPENGL` from CFLAGS and add `-DUSE_X11_SOFTRENDER` to it.
* To remove Gstreamer video support, add `-DUSE_X11_GST` from CFLAGS.
