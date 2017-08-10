cmake_minimum_required (VERSION 2.6)

include_directories("./taglib/bindings/c/")
include_directories("./parg/")

add_definitions(-DTAGLIB_STATIC)

# detect operating system
message(STATUS "We are on a ${CMAKE_SYSTEM_NAME} system")
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    target_link_libraries(tagmp3 "-static" ${CMAKE_SOURCE_DIR}/taglib/bindings/c/libtag_c.a ${CMAKE_SOURCE_DIR}/taglib/taglib/libtag.a ${CMAKE_SOURCE_DIR}/parg/build/libparg.a z)
else()
    target_link_libraries(tagmp3 ${CMAKE_SOURCE_DIR}/taglib/bindings/c/libtag_c.a ${CMAKE_SOURCE_DIR}/taglib/taglib/libtag.a ${CMAKE_SOURCE_DIR}/parg/build/libparg.a z)
endif()

add_executable(tagmp3 main.cpp)
