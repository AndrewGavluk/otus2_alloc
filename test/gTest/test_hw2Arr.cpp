#include <iostream>
#include <memory>
#include <gtest/gtest.h>
#include "../../libs/hw2Arr.h"
#define template_T_Alloc_default template <typename T, typename Alloc= std::allocator<T> >

template_T_Alloc_default
void t_DefaultConstructor(){ 
    auto testint = std::make_unique< hw2Array<T, Alloc> > ();
    ASSERT_TRUE(testint->size() == 0);
    ASSERT_TRUE(testint->capacity() == 0);
}

TEST(gtest_testhw2Arr, testDefaultConstructor){
    
    t_DefaultConstructor <int> ();
    t_DefaultConstructor <double>();
}

template_T_Alloc_default
void t_ConstructorBySize(const size_t&  size){ 
    auto testint = std::make_unique< hw2Array<T, Alloc> > (size);
    ASSERT_TRUE(testint->size() == 0);
    ASSERT_TRUE(testint->capacity() == size);
    }

TEST(gtest_testhw2Arr, testConstructorBySize){
    t_ConstructorBySize<int>(5);
    t_ConstructorBySize<double>(static_cast<size_t>(5));
}

template_T_Alloc_default
void t_ConstructorBySizeAndValue (const size_t& size, const T& value){ 
    auto testint = std::make_unique< hw2Array<T, Alloc> > (size, value);
    for (size_t i=0; i<size; ++i){
        ASSERT_TRUE(testint->operator[](i) == value);
    }
}

TEST(gtest_testhw2Arr, testConstructorBySizeAndValue){
    t_ConstructorBySizeAndValue<int>(5,5);
    t_ConstructorBySizeAndValue<double>(5,5.0);
}

template_T_Alloc_default
void t_ConstructorByInitList(const std::initializer_list<T>& value){ 
    auto testint = std::make_unique< hw2Array<T, Alloc> > (value);
    for (size_t i=0; i<value.size(); ++i){
        ASSERT_TRUE(testint->operator[](i) == *(value.begin() + i));
    }
}

TEST(gtest_testhw2Arr, testConstructorByInitializerList){
    t_ConstructorByInitList<int>({1,2,3,4,5});
    t_ConstructorByInitList<double>({1.0,2.0,3.0,4.0,5.0});
}

template_T_Alloc_default
void t_CopyConstructor(const std::initializer_list<T>& value){ 
    std::unique_ptr< hw2Array<T, Alloc> > testint1 (new hw2Array<T, Alloc> (value) );
    auto testint2 = std::make_unique< hw2Array<T, Alloc> > (* testint1.get());

    // changing the first 
    for (size_t i=0; i<value.size(); ++(testint1->operator[](i++)));

    // check the second 
    for (size_t i=0; i<value.size(); ++i){
        ASSERT_TRUE(testint2->operator[](i) == *(value.begin() + i));
        ASSERT_TRUE(testint2->operator[](i) != testint1->operator[](i));
    }
}

TEST(gtest_testhw2Arr, testCopyConstructor){
    t_CopyConstructor<int>({1,2,3,4,5});
    t_CopyConstructor<double>({1.0,2.0,3.0,4.0,5.0});
}

template_T_Alloc_default
void t_MoveConstructor(const std::initializer_list<T>& value){ 
    std::shared_ptr< hw2Array<T, Alloc> > testint1 (new hw2Array<T, Alloc> (value) );
    auto testint2 = std::make_shared< hw2Array<T, Alloc> > (std::move(* testint1.get()));
        for (size_t i=0; i<value.size(); ++i){
            ASSERT_TRUE(testint2->operator[](i) == *(value.begin() + i));
        }
}

TEST(gtest_testhw2Arr, testMoveConstructor){
    t_MoveConstructor<int>({1,2,3,4,5});
    t_MoveConstructor<double>({1.0,2.0,3.0,4.0,5.0});
}

template_T_Alloc_default
void t_operatorEql(const std::initializer_list<T>& value,  const std::initializer_list<T>& value2){ 
    std::unique_ptr< hw2Array<T, Alloc> > testint (new hw2Array<T, Alloc> (value)); // 1-st hw2Array build on value
    auto testint1 = std::make_unique< hw2Array<T, Alloc> > (* testint.get());      /* 2-nd hw2Array copy of 1-st, 
                                                                                            expected eql to 1-st*/

    std::unique_ptr< hw2Array<T, Alloc> > testint2 (new hw2Array<T, Alloc> (value2) ); /* 3-rd hw2Array build on value2, 
                                                                                            expected to not eql to 1-st
                                                                                            (value should not eql value2)*/

    ASSERT_TRUE( *(testint.get()) == *(testint1.get()));
    ASSERT_FALSE( *(testint1.get()) == *(testint2.get()));
}

TEST(gtest_testhw2Arr, testOperatorEql){
    t_operatorEql<int>({1,2,3,4,5},     {1,2,3,4,5,6});
    t_operatorEql<double>({1.0,2.0,3.0,4.0,5.0},   {1.0,2.0,3.0,4.0,5.0,6.0});
}

template_T_Alloc_default
void t_operatorNotEql(const std::initializer_list<T>& value,  const std::initializer_list<T>& value2){ 
    std::unique_ptr< hw2Array<T, Alloc> > testint (new hw2Array<T, Alloc> (value)); // 1-st hw2Array build on value
    auto testint1 = std::make_unique< hw2Array<T, Alloc> > (* testint.get());      /* 2-nd hw2Array copy of 1-st, 
                                                                                            expected eql to 1-st*/

    std::unique_ptr< hw2Array<T, Alloc> > testint2 (new hw2Array<T, Alloc> (value2) ); /* 3-rd hw2Array build on value2, 
                                                                                            expected to not eql to 1-st
                                                                                            (value should not eql value2)*/

    ASSERT_FALSE( *(testint.get()) != *(testint1.get()));
    ASSERT_TRUE( *(testint1.get()) != *(testint2.get()));
}

TEST(gtest_testhw2Arr, testOperatorNotEql){
    t_operatorNotEql<int>({1,2,3,4,5},     {1,2,3,4,5,6});
    t_operatorNotEql<double>({1.0,2.0,3.0,4.0,5.0},   {1.0,2.0,3.0,4.0,5.0,6.0});
}

template_T_Alloc_default
void t_operatorCopyAssignment(const std::initializer_list<T>& value){
    hw2Array<T, Alloc> testint {value};
    hw2Array<T, Alloc> testint2 {};
    testint2 = testint;
    ASSERT_TRUE( testint == testint2);
}

TEST(gtest_testhw2Arr, testOperatorCopyAssignment){
    t_operatorCopyAssignment<int>({1, 2, 3, 4, 5});
    t_operatorCopyAssignment<double>({1.0, 2.0, 3.0, 4.0, 5.0});
}

template_T_Alloc_default
void t_operatorMoveAssignment(const std::initializer_list<T>& value){
    hw2Array<T, Alloc>  testint {value};
    hw2Array<T, Alloc>  testint2 {value};
    hw2Array<T, Alloc>  testint3 {};
    hw2Array<T, Alloc>  testint4 {};
    
    testint2 = std::move(testint3);
    
    ASSERT_TRUE(testint2 == testint4);

    ASSERT_TRUE(testint3 == testint );
    ASSERT_TRUE(testint2 != testint );
    ASSERT_TRUE(testint3 != testint4);
}

TEST(gtest_testhw2Arr, testOperatorMoveAssignment){
    t_operatorMoveAssignment<int>({1, 2, 3, 4, 5});
    t_operatorMoveAssignment<double>({1.0, 2.0, 3.0, 4.0, 5.0});
}

template_T_Alloc_default
void t_capacity(const std::initializer_list<T>& value){ 
    std::unique_ptr< hw2Array<T, Alloc> > testint (new hw2Array<T, Alloc> (value)); 
    ASSERT_TRUE(testint->capacity() == value.size());
}

TEST(gtest_testhw2Arr, testCapacity){
    t_capacity<int>({1,2,3,4,5});
    t_capacity<double>({1.0,2.0,3.0,4.0,5.0});
}

template_T_Alloc_default
void t_size1(const std::initializer_list<T>& value){ 
    std::unique_ptr< hw2Array<T, Alloc> > testint (new hw2Array<T, Alloc> (value)); 
    ASSERT_TRUE(testint->size() == value.size());
}

TEST(gtest_testhw2Arr, testSize){
    t_size1<int>({1,2,3,4,5});
    t_size1<double>({1.0,2.0,3.0,4.0,5.0});
}



int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}