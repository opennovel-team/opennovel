#!/bin/sh

set -eu

#
# Banner
#

# Get the version string.
VERSION=`grep -a1 '<!-- BEGIN-LATEST-EN -->' ChangeLog | tail -n1`
VERSION=`echo $VERSION | cut -d ' ' -f 2`
NOTE=`cat ChangeLog | awk '/BEGIN-LATEST-EN/,/END-LATEST-EN/' | tail -n +2 | ghead -n -1`

# Show the version and the release note.
echo "Going to release the version $VERSION of the OpenNovel project."
echo ''
echo '[Note]'
echo "$NOTE"
echo ''
echo 'Press enter to continue.'

read str

#
# Make Directories
#

echo 'Preparing target directories...'

TARGET_DIR="`pwd`/opennovel-$VERSION"
TARGET_ZIP="`pwd`/opennovel-$VERSION.zip"
rm -rf "$TARGET_DIR" "$TARGET_ZIP"
mkdir "$TARGET_DIR"
mkdir "$TARGET_DIR/tools"

echo '...Done preparing target directories.'
echo ''

#
# Windows build (Binary)
#

echo 'Building the Windows engine...'
cd build/engine-windows
rm -rf objs
make -j$(nproc)
cd ../..
cp build/engine-windows/engine.exe "$TARGET_DIR/"
echo '...Done building the Windows engine.'

echo 'Building the Windows editor...'
cd build/editor-windows
rm -rf objs
make -j$(nproc) editor.exe web-test.exe
cd ../../
cp build/editor-windows/editor.exe "$TARGET_DIR/"
cp build/editor-windows/web-test.exe "$TARGET_DIR/tools/"
echo '...Done building the Windows editor.'

echo ''

#
# Linux build (Binary)
#

#echo 'Building the Linux engine...'
#rm -rf build/engine-linux/objs
#docker run -it -v `pwd`:/work "cd /work/build/engine-linux && make"
#cp build/engine-linux/onengine "$TARGET_DIR/tools/onengine-linux"
#echo '...Done building the Linux engine.'
#
#echo ''

#
# Wasm build (Binary)
#

echo 'Building Wasm binaries...'

cd build/engine-wasm
"$HOME/opt/emsdk/emsdk" activate latest
source "$HOME/opt/emsdk/emsdk_env.sh"
make
cp -R html "$TARGET_DIR/tools/wasm-src"
cd ../../

echo '...Done building Wasm binaries.'
echo ''

#
# iOS source tree build (Source)
#

echo 'Building the iOS source tree...'

cd build/engine-ios
make src
cp -R ios-src "$TARGET_DIR/tools/"
cd ../../

echo '...Done building the iOS source tree.'
echo ''

#
# Android source tree build (Source)
#

echo 'Building the Android source tree...'

cd build/engine-android
make src
cp -R android-src "$TARGET_DIR/tools/"
cd ../../

echo '...Done building the Android source tree.'
echo ''

#
# macOS source tree build (Source)
#

echo 'Building the macOS source tree...'

cd build/engine-macos
make engine.dmg
make src
cd ../../
cp build/engine-macos/engine.dmg "$TARGET_DIR/tools/"
cp -R build/engine-macos/macos-src "$TARGET_DIR/tools/"

echo '...Done building the macOS source tree.'
echo ''

#
# Unity source tree build (Source)
#

echo 'Building the Unity source tree...'

cd build/engine-unity
make -j$(nproc) libopennovel.dll
make src
cd ../../
cp -R build/engine-unity/unity-src "$TARGET_DIR/tools/"

echo '...Done building the Unity source tree.'
echo ''

#
# Samples
#

echo 'Copying samples...'

cp -R games "$TARGET_DIR/games"

echo '...Done copying samples.'
echo ''

#
# Documents
#

echo 'Copying documents...'

mkdir "$TARGET_DIR/manual"
cp docs/index.html "$TARGET_DIR/manual/"
cp -R docs/html_ja "$TARGET_DIR/manual/"
cp -R docs/html_en "$TARGET_DIR/manual/"

echo '...Done copying documents.'
echo ''

#
# ZIP
#

zip -9 -r "$TARGET_ZIP" "opennovel-$VERSION"

#
# GitHub Release
#

echo 'Making a release on GitHub...'

yes '' | gh release create "$VERSION" --title "$VERSION" --notes "$NOTE" "$TARGET_ZIP"
rm -rf "$TARGET_DIR" "$TARGET_ZIP"

echo '...Done releasing on GitHub.'
echo ''

#
# Discord Notification
#

discord-release.sh

echo 'Release completed!'
