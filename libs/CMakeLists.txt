cmake_minimum_required(VERSION 3.2)

add_library(libL2_container STATIC hw2Arr.cpp hw2Arr.h)
add_library(libL2_allocator STATIC Alloc.cpp Alloc.h)

set_target_properties(libL2_container PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)
set_target_properties(libL2_allocator PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)

target_include_directories(libL2_container PRIVATE ${CMAKE_BINARY_DIR})
target_include_directories(libL2_allocator PRIVATE ${CMAKE_BINARY_DIR})

if(MSVC)
	target_compile_options(libL2_container PRIVATE /W4)
	target_compile_options(libL2_allocator PRIVATE /W4)
else()
	target_compile_options(libL2_container PRIVATE -Wall -Wextra -Werror)
	target_compile_options(libL2_allocator PRIVATE -Wall -Wextra -Werror)
endif()
