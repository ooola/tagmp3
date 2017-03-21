cmake_minimum_required (VERSION 2.6)
project (tagmp3 C)

include_directories("./id3v2lib/include/")
include_directories("./parg/")

add_executable(tagmp3 main.c)
target_link_libraries(tagmp3 ${CMAKE_SOURCE_DIR}/id3v2lib/build/src/libid3v2.a ${CMAKE_SOURCE_DIR}/parg/build/libparg.a)
