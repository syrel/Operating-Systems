cmake_minimum_required(VERSION 3.6)
project(Exercise_0)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -Wextra -Wwrite-strings -O2")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(SOURCE_FILES src/statistics.c src/zombies.c)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

foreach( sourcefile ${SOURCE_FILES} )
    string( REPLACE ".c" "" name ${sourcefile} )
    string( REPLACE "src/" "" name ${name} )
    add_executable( ${name} ${sourcefile} )
    target_link_libraries(${name} Threads::Threads)
endforeach( sourcefile ${APP_SOURCES} )