cmake_minimum_required(VERSION 3.10)
project(rbk VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_VERBOSE_MAKEFILE ON)

if(CMAKE_BUILD_TYPE MATCHES "Release")
    add_compile_options(-O2)
    add_compile_options(-Wall)
endif()

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    add_compile_options(-W)
endif()

include_directories(include)

if(CMAKE_BUILD_TYPE MATCHES "Release")
    add_link_options(-s)
endif()

#add_link_options(-fPIC)
add_link_options(-static)

link_directories($ENV{RSLibOut})

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(POSTFIX d)
endif()

add_library(${PROJECT_NAME} SHARED

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
        #src/ringbuffer.cpp
        src/sorting.cpp
        src/wtime.cpp
)

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        PREFIX ""
        OUTPUT_NAME ${PROJECT_NAME}${POSTFIX}
)