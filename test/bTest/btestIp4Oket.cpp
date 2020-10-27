#define BOOST_TEST_MODULE btestIp4Oket
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <boost/test/unit_test.hpp>
#include "../../libs/ipOket.h"

void testConstructorFunc (const std::string & str, const uint32_t & value)
{
	Ip4Okets test1(str);
	BOOST_CHECK_EQUAL(test1.ip4_address, value);
}

void testLessOPeratorFunc (const std::string & str1, const std::string & str2 )
{
	Ip4Okets test1(str1);
	Ip4Okets test2(str2);
	BOOST_CHECK(test1 < test2 );
}

void testCheck_mask(const std::string & str1, const uint8_t & mask, const uint8_t shift, const bool & value)
{
	Ip4Okets test1(str1);
	BOOST_CHECK_EQUAL(test1.check_mask(mask, shift), value);
}

void testCout(const std::string & str1)
{
	std::ofstream test("test.txt", std::ofstream::out | std::ofstream::trunc);
	Ip4Okets testtOket(str1);
	test << testtOket;
	test.close();

	std::ifstream test_chek("test.txt");
	std::string str2;
	std::getline(test_chek, str2);
	test_chek.close();

	BOOST_CHECK_EQUAL(str1, str2);
}


BOOST_AUTO_TEST_SUITE(btestIp4Oket)

// testConstructor
BOOST_AUTO_TEST_CASE(testZero) 		{ testConstructorFunc("0.0.0.0", 	0);}
BOOST_AUTO_TEST_CASE(testOket1_1)	{ testConstructorFunc("0.0.0.1", 	1);}
BOOST_AUTO_TEST_CASE(testOket1_255) { testConstructorFunc("0.0.0.255",	255);}
BOOST_AUTO_TEST_CASE(testOket2_1)	{ testConstructorFunc("0.0.1.0",	256);}
BOOST_AUTO_TEST_CASE(testOket2_255) { testConstructorFunc("0.0.255.0",	255*256);}
BOOST_AUTO_TEST_CASE(testOket3_1)	{ testConstructorFunc("0.1.0.0",	256*256);}
BOOST_AUTO_TEST_CASE(testOket3_255) { testConstructorFunc("0.255.0.0",	256*256*255);}
uint32_t value = 256*256*256;
BOOST_AUTO_TEST_CASE(testOket4_1) { testConstructorFunc("1.0.0.0",	 	value);}
BOOST_AUTO_TEST_CASE(testOket4_255) { testConstructorFunc("255.0.0.0",	value*255);}

// testLessOPerator
BOOST_AUTO_TEST_CASE(testLessOpOket1_1)		{ testLessOPeratorFunc("0.0.0.1","0.0.0.2");	}
BOOST_AUTO_TEST_CASE(testLessOpOket1_255)	{ testLessOPeratorFunc("0.0.0.253","0.0.0.254");}
BOOST_AUTO_TEST_CASE(testLessOpOket2_1)		{ testLessOPeratorFunc("0.0.1.0","0.0.2.0");	}
BOOST_AUTO_TEST_CASE(testLessOpOket2_255)	{ testLessOPeratorFunc("0.0.253.0","0.0.254.0");}
BOOST_AUTO_TEST_CASE(testLessOpOket3_1)		{ testLessOPeratorFunc("0.1.0.0","0.2.0.0");	}
BOOST_AUTO_TEST_CASE(testLessOpOket3_255)	{ testLessOPeratorFunc("0.253.0.0","0.254.0.0");}
BOOST_AUTO_TEST_CASE(testLessOpOket4_1)		{ testLessOPeratorFunc("1.0.0.0","2.0.0.0");	}
BOOST_AUTO_TEST_CASE(testLessOpOket4_255)	{ testLessOPeratorFunc("253.0.0.0","254.0.0.0");}

// testCheckMask
BOOST_AUTO_TEST_CASE(testCheckMaskOpOket0_t){ testCheck_mask("34.57.38.54", 34, OKET3, true);}
BOOST_AUTO_TEST_CASE(testCheckMaskOpOket0_f){ testCheck_mask("34.57.38.54", 57, OKET3, false);}
BOOST_AUTO_TEST_CASE(testCheckMaskOpOket1_t){ testCheck_mask("34.57.38.54", 57, OKET2, true);}
BOOST_AUTO_TEST_CASE(testCheckMaskOpOket1_f){ testCheck_mask("34.57.38.54", 38, OKET2, false);}
BOOST_AUTO_TEST_CASE(testCheckMaskOpOket2_t){ testCheck_mask("34.57.38.54", 38, OKET1, true);}
BOOST_AUTO_TEST_CASE(testCheckMaskOpOket2_f){ testCheck_mask("34.57.38.54", 57, OKET1, false);}
BOOST_AUTO_TEST_CASE(testCheckMaskOpOket3_t){ testCheck_mask("34.57.38.54", 54, OKET0, true);}
BOOST_AUTO_TEST_CASE(testCheckMaskOpOket3_f){ testCheck_mask("34.57.38.54", 38, OKET0, false);}

// testCout
BOOST_AUTO_TEST_CASE(testCoutOpOket0_t){ testCout("0.0.0.54");}
BOOST_AUTO_TEST_CASE(testCoutOpOket1_t){ testCout("0.0.38.0");}
BOOST_AUTO_TEST_CASE(testCoutOpOket2_t){ testCout("0.57.0.0");}
BOOST_AUTO_TEST_CASE(testCoutOpOket3_t){ testCout("34.0.0.0");}
BOOST_AUTO_TEST_CASE(testCoutOpOket4_t){ testCout("34.57.38.54");}

BOOST_AUTO_TEST_SUITE_END()
