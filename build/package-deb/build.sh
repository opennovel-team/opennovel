#!/bin/sh

set -eu

LANG=C
LANGUAGE=C
LC_ALL=C

# Get the version of Suika2.
VERSION=`grep -a1 '<!-- BEGIN-LATEST -->' ../../ChangeLog | tail -n1`
VERSION=`echo $VERSION | cut -d ' ' -f 2`

# Get the minor version.
MINOR=1
if [ $# != 0 ]; then
    MINOR="$1";
fi

# Update the changelog
echo "opennovel ($VERSION-$MINOR) UNRELEASED; urgency=medium" > meta/debian/changelog;
echo '' >> meta/debian/changelog;
echo '  * Sync upstream' >> meta/debian/changelog;
echo '' >> meta/debian/changelog;
echo " -- Maiku Kamishiro <info@opennovel.org>  `date '+%a, %d %b %Y %T %z'`" >> meta/debian/changelog;

# Make a directory and enter it.
rm -rf work
mkdir work
cd work

# Create a source tarball.
SAVE_DIR=`pwd`
cd ../../../
git archive HEAD --output=apps/package-deb/work/opennovel_$VERSION.orig.tar.gz
cd "$SAVE_DIR"

# Make a sub-directory with version number, and enter it.
rm -rf opennovel-$VERSION
mkdir opennovel-$VERSION
cp -R ../meta/debian opennovel-$VERSION/
cd opennovel-$VERSION
tar xzf ../opennovel_$VERSION.orig.tar.gz

# Build a source package.
debuild
cd ../../
cp work/*.deb ./

# Cleanup.
rm -rf work
