#!/bin/sh

for f in html_ja/*.html; do
    ftp-upload.sh $f docs-ja/`basename $f`
done
ftp-upload.sh html_ja/style.css docs-ja/style.css

for f in html_en/*.html; do
    ftp-upload.sh $f docs-en/`basename $f`
done
ftp-upload.sh html_en/style.css docs-en/style.css
