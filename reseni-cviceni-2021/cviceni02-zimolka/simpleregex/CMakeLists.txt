cmake_minimum_required(VERSION 3.17)
project(cviceni02)

set(CMAKE_CXX_STANDARD 14)

add_executable(cviceni02
#        cviceni02-src/regexmain.cpp
        cviceni02-src/regexmain_hard.cpp
        cviceni02-src/simpleregex.cpp cviceni02-src/simpleregex.h)
