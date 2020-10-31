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
    t_ConstructorByInitList<int>(std::initializer_list<int>{1,2,3,4,5});
    t_ConstructorByInitList<double>(std::initializer_list<double>{1.0,2.0,3.0,4.0,5.0});
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
    t_CopyConstructor<int>(std::initializer_list<int>{1,2,3,4,5});
    t_CopyConstructor<double>(std::initializer_list<double>{1.0,2.0,3.0,4.0,5.0});
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
    t_MoveConstructor<int>(std::initializer_list<int>{1,2,3,4,5});
    t_MoveConstructor<double>(std::initializer_list<double>{1.0,2.0,3.0,4.0,5.0});
}


int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}