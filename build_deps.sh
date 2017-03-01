#!/bin/sh

echo building id3v2lib
(cd id3v2lib && mkdir -p build && cd build && cmake .. && make)
echo building parg
(cd parg && mkdir -p build && cd build && cmake .. && cmake --build .)
