OpenNovel
=========

OpenNovel is a very portable and commercial-ready game engine for visual novels.

This project is a fork of Suika2 and Polaris Engine.
The OpenNovel development team received a delegation of the copyright from the original author of Suika2 and Polaris Engine.

## Install and Run

Sample games are included in the latest zip.

* Windows
  * Download the latest zip file and extract it.
  * Copy `onengine.exe` to a sample game folder and run it.
* Web-based
  * Visit https://apps.opennovel.org/viewer/
  * Select a sample game folder.
* Linux
  * Type the following:
  ```
  git clone https://github.com/suika2team/suika2.git
  cd suika2
  sudo apt-get install build-essential libasound2-dev libx11-dev libxpm-dev mesa-common-dev libfreetype-dev libpng-dev libjpeg-dev libwebp-dev libvorbis-dev libogg-dev libbrotli-dev libbz2-dev libz-dev libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev
  ./configure
  make
  sudo make install
  ```
  * Enter a sample game directory and run `onengine`. 

## Gaming Platforms

OpenNovel supports all of the following right out of the box!

### Desktop

|Platform |Version               |
|---------|----------------------|
|Windows  |XP or later           |
|macOS    |10.13 or later        |
|Linux    |Ubuntu 16.04 or later |

### Mobile

|Platform |Version                        |
|---------|-------------------------------|
|iPhone   |iOS 13 or later                |
|iPad     |iPadOS 13 or later             |
|Android  |Android 10 or later            |

### Web (HTML5/Wasm)

|Platform         |Status|
|-----------------|------|
|Chrome           |OK    |
|Chrome Android   |OK    |
|Safari           |OK    |
|Safari iOS       |OK    |
|Edge             |OK    |
|Firefox          |OK    |

### Gaming Consoles

|Platform |Version  |Other              |
|---------|---------|-------------------|
|Unity    |2022.3   |Custom DLL required|

### Minor Platforms

|Platform  |Version       |Details            |
|----------|--------------|-------------------|
|FreeBSD   |11 or later   |                   |
|NetBSD    |9 or later    |                   |
|OpenBSD   |7 or later    |                   |
|Solaris   |11 or later   |Sound implementing |

### Compatibility List

|Platform         |Graphics   |Sound        |Video       |
|-----------------|-----------|-------------|------------|
|Windows 11       |Direct3D 12|DirectSound 5|DirectShow  |
|Windows 10       |Direct3D 12|DirectSound 5|DirectShow  |
|Windows 8        |Direct3D 11|DirectSound 5|DirectShow  |
|Windows 7        |Direct3D 11|DirectSound 5|DirectShow  |
|Windows Vista    |Direct3D 11|DirectSound 5|DirectShow  |
|Windows XP       |Direct3D 9 |DirectSound 5|DirectShow  |
|macOS            |Metal      |Audio Unit   |AVFoundation|
|Linux            |OpenGL 3.0 |ALSA         |Gstreamer   |
|FreeBSD          |OpenGL 3.0 |/dev/dsp     |Gstreamer   |

## Development Platforms

You can develop visual novels on your favorite desktop OS our engine support.
In addition, we provide an integrated development software for Windows 11 and 10.

Also, there is a Web-based game viewer which runs on Google Chrome or Chromium.
Visit https://apps.opennovel.org/viewer/ and run your game.

## Portability

* Firstly, the `Core` of our engine is written in ANSI C and it's very comformant to the standard.
* The `Core` is able to be compiled with most C compilers including GCC, Clang and MSVC.
* Secondly, we port our `Hardware Abstraction Layer` to each platform in a platform's native language.
* We have access to the full functionality of the platforms via their native languages.
* Therefore, the combination of `HAL + Core` brings high portability and functionality to our engine.

## Editor Application

The Windows version of OpenNovel has a simple, easy-to-use, and light-weight editor application.
It has three advanced features:

* On-the-fly playback
* Editing scripts by clicks
* Exporting games by clicks

Please use the editor with your favorite text editor.

## Build

### Host Build
```
./configure
make
```

### Windows Cross Build
```
./configure --host=windows
make
```

## Support and Contact

Please send an e-mail to `info@opennovel.org` anytime.
