cmake_minimum_required(VERSION 2.6)
# =========================================================
# *CNG* - CNG not GUI | Console Non-GUI
# This project provide a console pseudo GUI wrap up library
# which is based on the N-Curses library.
# =========================================================

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_COMPILER_VERSION c++11)

project(CNG)

find_package(Curses REQUIRED)

# Define interfaces in the include directory.
include_directories(include)

# Implement some defined interfaces.
add_subdirectory("src")

# Demonstrate the usage of the library by some demo.
add_subdirectory("demo")

