# Specifies minimum version of cmake, establishing policy settings and ensuring following CMake functions are run with compatible version of CMake
cmake_minimum_required(VERSION 3.28.3)
set(CMAKE_CXX_STANDARD_REQUIRED=C++17)

project(BookstoreApp)

# Find the SQLite3 library
find_path(SQLITE3_INCLUDE_DIR sqlite3.h)
find_library(SQLITE3_LIBRARY sqlite3)

# Include the SQLite3 headers
include_directories(${SQLite3_INCLUDE_DIRS})

add_executable(BookstoreApp src/appBookstore.cpp src/dbops.cpp src/io.cpp src/library.cpp src/userAuth.cpp src/user.cpp)

target_link_libraries(BookstoreApp ${SQLITE3_LIBRARY})



