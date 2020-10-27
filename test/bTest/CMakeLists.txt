find_package(Boost COMPONENTS unit_test_framework REQUIRED)
add_executable(btestIpOketExec btestIp4Oket.cpp )

set_target_properties(btestIpOketExec
	PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
	COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
	INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})

target_link_libraries(btestIpOketExec  
	${Boost_LIBRARIES}
	libL1)

if (MSVC)
	target_compile_options(btestIpOketExec  PRIVATE /W4)
else()
	target_compile_options(btestIpOketExec  PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

enable_testing()
add_test(testIp4Oket btestIpOketExec)

