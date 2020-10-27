enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})
add_executable(gtestIpOketExec gtestIp4Oket.cpp)

set_target_properties(gtestIpOketExec 
	PROPERTIES 
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
	INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS})

if(MSVC)
	target_compile_options(gtestIpOketExec PRIVATE /W4)
else()
	target_compile_options(gtestIpOketExec PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

target_link_libraries(gtestIpOketExec gtest pthread libL1)

add_test(gtest_testsuite gtestIpOketExec)




