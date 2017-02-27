cmake_minimum_required(VERSION 3.6)
project(_OS__Exercise_0)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -Wextra -Wwrite-strings -O2")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(SOURCE_FILES src/error.c src/fib.c src/linked_list.c src/multiply.c src/net.c src/substr.c)

foreach( sourcefile ${SOURCE_FILES} )
    string( REPLACE ".c" "" name ${sourcefile} )
    string( REPLACE "src/" "" name ${name} )
    add_executable( ${name} ${sourcefile} )
endforeach( sourcefile ${APP_SOURCES} )