CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(xnu_zlib_fuzz)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})

OPTION(CMAKE_C_COMPILER afl-gcc)
SET(XNU_ZLIB_SOURCE_FILES adler32.c compress.c crc32.c deflate.c infback.c inffast.c inflate.c inftrees.c trees.c uncompr.c zutil.c)
ADD_LIBRARY(xnu_zlib STATIC ${XNU_ZLIB_SOURCE_FILES})

ADD_EXECUTABLE(xnu zlib.c)
TARGET_LINK_LIBRARIES(xnu xnu_zlib)

