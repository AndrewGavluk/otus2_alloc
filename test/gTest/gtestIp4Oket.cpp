
#include <gtest/gtest.h>
#include <iostream>
#include <fstream>


#include "../../libs/ipOket.h"

void testConstructorFunc (const std::string & str, const uint32_t & value)
{
	Ip4Okets test1(str);
	ASSERT_TRUE(test1.ip4_address == value);
}

void testLessOPeratorFunc (const std::string & str1, const std::string & str2 )
{
	Ip4Okets test1(str1);
	Ip4Okets test2(str2);
	ASSERT_TRUE(test1.ip4_address < test2.ip4_address);
}

void testCheck_mask(const std::string & str1, const uint8_t & mask, const uint8_t shift, const bool & value)
{
	Ip4Okets test1(str1);
	ASSERT_TRUE(test1.check_mask(mask, shift) == value);
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

	ASSERT_TRUE(str1 == str2);
}

TEST(gtest_testsuite, testConstructor)
{
	testConstructorFunc("0.0.0.0", 		0);
	testConstructorFunc("0.0.0.1", 		1);
	testConstructorFunc("0.0.0.255",	255);
	testConstructorFunc("0.0.1.0",		256);
	testConstructorFunc("0.0.255.0",	255*256);
	testConstructorFunc("0.1.0.0",		256*256);
	testConstructorFunc("0.255.0.0",	256*256*255);
	uint32_t value = 256*256*256;
	testConstructorFunc("1.0.0.0",	 	value);
	testConstructorFunc("255.0.0.0",	value*255);
}

TEST(gtest_testsuite, testLessOPerator)
{
	testLessOPeratorFunc("0.0.0.1","0.0.0.2");
	testLessOPeratorFunc("0.0.0.253","0.0.0.254");
	testLessOPeratorFunc("0.0.1.0","0.0.2.0");
	testLessOPeratorFunc("0.0.253.0","0.0.254.0");
	testLessOPeratorFunc("0.1.0.0","0.2.0.0");
	testLessOPeratorFunc("0.253.0.0","0.254.0.0");
	testLessOPeratorFunc("1.0.0.0","2.0.0.0");
	testLessOPeratorFunc("253.0.0.0","254.0.0.0");
}

TEST(gtest_testsuite, testCheckMask)
{
	testCheck_mask("34.57.38.54", 34, OKET3, true);
	testCheck_mask("34.57.38.54", 57, OKET3, false);
	testCheck_mask("34.57.38.54", 57, OKET2, true);
	testCheck_mask("34.57.38.54", 38, OKET2, false);
	testCheck_mask("34.57.38.54", 38, OKET1, true);
	testCheck_mask("34.57.38.54", 57, OKET1, false);
 	testCheck_mask("34.57.38.54", 54, OKET0, true);
	testCheck_mask("34.57.38.54", 38, OKET0, false);
}

TEST(gtest_testsuite, test_Cout)
{
	testCout("0.0.0.54");
	testCout("0.0.38.0");
	testCout("0.57.0.0");
	testCout("34.0.0.0");
	testCout("34.57.38.54");
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
