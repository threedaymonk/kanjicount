Kanji count
===========

This is a revival/extension of [something I did several years ago][kp] to list
Japanese kanji by their frequency in actual usage. At that time, I spidered a
small corner of Wikipedia; this time, I've used a Wikipedia dump directly,
which is both quicker and covers a larger data set.

[kp]: http://po-ru.com/projects/kanji-project/

How to use it
-------------

Build `count-codepoints` (edit `Makefile` if you're not using gcc):

    make

Analyse something; Japanese wikipedia, for example:

    bunzip2 < jawiki-*-pages-articles.xml.bz2 | ./count-codepoints | ./sort-kanji > results.csv

Or if you just want to try a smaller data set:

    curl -s http://... | ./count-codepoints | ./sort-kanji > results.csv

More to come ...
