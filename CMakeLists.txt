cmake_minimum_required(VERSION 3.10)

file(STRINGS "version" VERSION)

project(RBKLib VERSION ${VERSION})

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_VERBOSE_MAKEFILE OFF)

#set(TEST test)

if(CMAKE_BUILD_TYPE MATCHES "Release")
    add_compile_options(-O2)
    add_compile_options(-Wall)
endif()

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    add_compile_options(-W)
endif()

include_directories(include)
include_directories(include/unix)

if(CMAKE_BUILD_TYPE MATCHES "Release")
    add_link_options(-s)
endif()

# add_link_options(-fPIC)
# add_link_options(-static)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(POSTFIX d)
endif()

add_library(${PROJECT_NAME}

        src/check/brackets.cpp
        src/check/sign.cpp
        src/check/validator.cpp
        src/compare_symbol.cpp
        src/convert_double_bit.cpp
        src/convert_register_string.cpp
        src/convert_string_double.cpp
        src/find.cpp
        src/http.cpp
        src/parse_string_v1/parsestring_v1.cpp
        src/parse_string_v2/parsestring_v2.cpp
        src/parse_string_v3/node.cpp
        src/parse_string_v3/operations.cpp
        src/parse_string_v3/parsestring_v3.cpp
        src/queue/itemqueue.cpp
        src/queue/queue.cpp
        src/read_file.cpp
        src/ringbuffer.cpp
        src/sorting.cpp
        src/wtime.cpp
        src/parse_stream.cpp
        src/printx.cpp

        src/win/tools.cpp
        src/win/file.cpp
        src/win/socket/basesocket.cpp
        src/win/socket/tcpclient.cpp
        src/win/socket/tcpserver.cpp
        src/win/socket/udpclient.cpp
        src/win/socket/udpserver.cpp

        src/unix/file.cpp
        src/unix/dir.cpp

        src/unix/socket/tcpserver.cpp
        src/unix/socket/tcpbase.cpp
        src/unix/socket/tcpclient.cpp
)

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        PREFIX ""
        OUTPUT_NAME librbk${POSTFIX}
)

### Test ###

if(${TEST} MATCHES test)

    add_executable(${TEST})

    set_target_properties(${TEST}
            PROPERTIES OUTPUT_NAME ${PROJECT_NAME}-${TEST}-${CMAKE_PROJECT_VERSION}
    )

    target_include_directories(${TEST} PRIVATE $ENV{GOOGLETEST}/googletest/include)

    target_link_directories(${TEST} PRIVATE $ENV{GOOGLETEST}/lib/gcc_libx64)

    target_link_libraries(${TEST} PRIVATE gtest)
    target_link_libraries(${TEST} PRIVATE gtest_main)
    #target_link_libraries(${TEST} PRIVATE Ws2_32)

    target_sources(${TEST} PRIVATE test/test.cpp)
endif()

### Install ###

set(INSTALL_HEADER_FILES

        include/args.h
        include/check/brackets.h
        include/check/sign.h
        include/check/validator.h
        include/compare_symbol.h
        include/convert_double_bit.h
        include/convert_register_string.h
        include/convert_string_double.h
        include/find.h
        include/http.h
        include/parse_stream.h
        include/parse_string_v1/parsestring_v1.h
        include/parse_string_v2/node.h
        include/parse_string_v2/parsestring_v2.h
        include/parse_string_v2/sign.h
        include/parse_string_v2/type.h
        include/parse_string_v3/node.h
        include/parse_string_v3/operations.h
        include/parse_string_v3/parsestring_v3.h
        include/printx.h
        include/queue/itemqueue.h
        include/queue/queue.h
        include/read_file.h
        include/redefine.h
        include/ringbuffer.h
        include/sorting.h
        include/unix/dir.h
        include/unix/file.h
        include/unix/socket/tcpbase.h
        include/unix/socket/tcpclient.h
        include/unix/socket/tcpserver.h
        include/win/file.h
        include/win/socket/basesocket.h
        include/win/socket/tcpclient.h
        include/win/socket/tcpserver.h
        include/win/socket/udpclient.h
        include/win/socket/udpserver.h
        include/win/tools.h
        include/wtime.h
        include/wvector.h
)

set(INSTALL_TARGET_FILES ${PROJECT_NAME})

include(config/install.cmake)