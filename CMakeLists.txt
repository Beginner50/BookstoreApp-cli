# Specifies minimum version of cmake, establishing policy settings and ensuring following CMake functions are run with compatible version of CMake
cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD_REQUIRED=C++17)

project(BookstoreApp)

if(UNIX AND NOT APPLE)
	# Find the SQLite3 library
	find_path(SQLITE3_INCLUDE_DIR sqlite3.h)
	find_library(SQLITE3_LIBRARY sqlite3)
elseif(WIN32)
	set(SQLITE3_INCLUDE_DIR ".")
	set(SQLITE3_LIBRARY "libsqlite3.a")
endif()

# Include the SQLite3 headers
include_directories(${SQLite3_INCLUDE_DIR})

add_executable(BookstoreApp src/appBookstore.cpp src/dbops.cpp src/io.cpp src/library.cpp src/userAuth.cpp src/user.cpp)

target_link_libraries(BookstoreApp ${SQLITE3_LIBRARY})



