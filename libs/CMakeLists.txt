cmake_minimum_required(VERSION 3.2)

add_library(libL2 STATIC hw2Arr.cpp hw2Arr.h)
set_target_properties(libL2 PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)
target_include_directories(libL2 PRIVATE ${CMAKE_BINARY_DIR})

if(MSVC)
	target_compile_options(libL2 PRIVATE /W4)
else()
	target_compile_options(libL2 PRIVATE -Wall -Wextra -Werror)
endif()
