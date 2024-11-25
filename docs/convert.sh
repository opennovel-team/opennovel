#!/bin/sh

for f in md_ja/*.md; do
	outfile="tmp.html";
	echo '<!DOCTYPE html>' > $outfile;
	echo '<html lang="ja-JP">' >> $outfile;
	echo '<head>' >> $outfile;
	echo '  <meta charset="utf-8">' >> $outfile;
	echo '  <meta name="viewport" content="width=device-width">' >> $outfile;
	echo '  <title>OpenNovel</title>' >> $outfile;
	echo '  <link rel="stylesheet" href="style.css">' >> $outfile;
	echo '</head>' >> $outfile;
	echo '<body>' >> $outfile;
	showdown makehtml -i "$f" -o "$outfile.tmp" -c tables=true;
	cat "$outfile.tmp" >> "$outfile";
	rm "$outfile.tmp";
	echo '</body>' >> $outfile;
	echo '</html>' >> $outfile;
	mv "$outfile" html_ja/`basename $f .md`.html
done

# for f in md_en/*.md; do
# 	outfile="tmp.html";
# 	echo '<!DOCTYPE html>' > $outfile;
# 	echo '<html lang="en-US">' >> $outfile;
# 	echo '<head>' >> $outfile;
# 	echo '  <meta charset="utf-8">' >> $outfile;
# 	echo '  <meta name="viewport" content="width=device-width">' >> $outfile;
# 	echo '  <title>OpenNovel</title>' >> $outfile;
# 	echo '  <link rel="stylesheet" href="style.css">' >> $outfile;
# 	echo '</head>' >> $outfile;
# 	echo '<body>' >> $outfile;
# 	showdown makehtml -i "$f" -o "$outfile.tmp";
# 	cat "$outfile.tmp" >> "$outfile";
# 	rm "$outfile.tmp";
# 	echo '</body>' >> $outfile;
# 	echo '</html>' >> $outfile;
# 	base = `basename "$f"`
# 	mv "$outfile" html_en/${base%.md}.html
# done
