﻿cmake_minimum_required (VERSION 3.2)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
	project(custom_allocator VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
	project(custom_allocator VERSION 1.1.99)
endif()

add_subdirectory (${PROJECT_SOURCE_DIR}/src)
add_subdirectory (${PROJECT_SOURCE_DIR}/test)
