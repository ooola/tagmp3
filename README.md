# tagmp3

Tagmp3 is a command line program to edit mp3 tags.

## Building

First download and build dependencies.

```
git clone --recursive git@github.com:larsbs/id3v2lib.git
git clone --recursive git@github.com:jibsen/parg.git
./build_deps.sh
```

Next build tagmp3

```
cmake .
make
```
