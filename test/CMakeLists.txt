enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})
add_executable(gtestHW2Arr test_hw2Arr.cpp)

set_target_properties(gtestHW2Arr 
	PROPERTIES 
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
	INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS})

if(MSVC)
	target_compile_options(gtestHW2Arr PRIVATE /W4)
else()
	target_compile_options(gtestHW2Arr PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

target_link_libraries(gtestHW2Arr gtest pthread libL2_container libL2_allocator)


add_test(gtest_testhw2Arr gtestHW2Arr)