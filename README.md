# tagmp3

[![Build Status](https://travis-ci.org/ooola/tagmp3.svg?branch=master)](https://travis-ci.org/ooola/tagmp3)

Tagmp3 is a command line program to edit mp3 tags. This program is statically built so that it can be downloaded and run on any Linux system without dependencies.

## Download

Downloads can be found on the [releases page](https://github.com/ooola/tagmp3/releases).

## Usage
```
Usage: tagmp3 [options] filename
	[-h]              prints this screen
	[-v]              prints version information
	[-p]              prints existing tag information
	[-r]              remove all existing tag information
	[-u]              set unspecified tags to empty string
	[-t title]        sets the title
	[-a artist]       sets the artist
	[-l album]        sets the album
	[-b album-artist] sets the album artist
	[-g genre]        sets the genre
	[-k track]        sets the track
	[-y year]         sets the year
	[-c comment]      sets the comment
	[-n disc-number]  sets the disc number
	[-o composer]     sets the composer
```

## Building

First download and build dependencies.

```
git clone --recursive git@github.com:taglib/taglib.git
git clone --recursive git@github.com:jibsen/parg.git
./build_deps.sh
```

Next build tagmp3

```
cmake .
make
```
