#!/bin/sh

echo building taglib
(cd taglib && cmake -DCMAKE_OSX_ARCHITECTURES="x86_64" -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_BUILD_TYPE=Release . && make)
echo building parg
(cd parg && mkdir -p build && cd build && cmake .. && cmake --build .)
