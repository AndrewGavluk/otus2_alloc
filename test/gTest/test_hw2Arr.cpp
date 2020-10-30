#include <iostream>
#include <memory>
#include <gtest/gtest.h>
#include "../../libs/hw2Arr.h"
#define template_T_Alloc_default template <typename T, typename Alloc= std::allocator<T> >


//#pragma region testHWArr2Class

template_T_Alloc_default
void t_DefaultConstructor(){ 
    auto testint = std::make_unique< hw2Array<T, Alloc> > ();
    ASSERT_TRUE(testint->size() == 0);
    ASSERT_TRUE(testint->capacity() == 0);
}

template_T_Alloc_default
void t_ConstructorBySize(const size_t&  size){ 
    auto testint = std::make_unique< hw2Array<T, Alloc> > (size);
    ASSERT_TRUE(testint->size() == 0);
    ASSERT_TRUE(testint->capacity() == size);
    }

template_T_Alloc_default
void t_ConstructorBySizeAndValue (const size_t& size, const T& value){ 
    auto testint = std::make_unique< hw2Array<T, Alloc> > (size, value);
    for (size_t i=0; i<size; ++i){
        ASSERT_TRUE(testint->operator[](i) == value);
    }
}

template_T_Alloc_default
void t_ConstructorByInitList(const std::initializer_list<T>& value){ 
    auto testint = std::make_unique< hw2Array<T, Alloc> > (value);
    for (size_t i=0; i<value.size(); ++i){
        ASSERT_TRUE(testint->operator[](i) == *(value.begin() + i));
    }
}

template_T_Alloc_default
void t_CopyConstructor(const std::initializer_list<T>& value){ 
    auto testint1 = std::make_unique< hw2Array<T, Alloc> > (value);
    std::unique_ptr< hw2Array<T, Alloc> > testint2 (testint1.get());

    // changing the first 
    for (size_t i=0; i<value.size(); ++i){
        ++(testint1->operator[](i));
    }

    // check the second 
    for (size_t i=0; i<value.size(); ++i){
        (testint2->operator[](i) == *(value.begin() + i));
        (testint2->operator[](i) != testint1->operator[](i));
    }
}

TEST(gtest_testhw2Arr, testDefaultConstructor){
    
    t_DefaultConstructor <int> ();
    t_DefaultConstructor <double>();
}

TEST(gtest_testhw2Arr, testDefaultConstructorBySize){
    t_ConstructorBySize<int>(5);
    t_ConstructorBySize<double>(static_cast<size_t>(5));
}

TEST(gtest_testhw2Arr, testDefaultConstructorBySizeAndValue){
    t_ConstructorBySizeAndValue<int>(5,5);
    t_ConstructorBySizeAndValue<double>(5,5.0);
}

TEST(gtest_testhw2Arr, testDefaultConstructorByInitializerList){
    t_ConstructorByInitList<int>(std::initializer_list<int>{1,2,3,4,5});
    t_ConstructorByInitList<double>(std::initializer_list<double>{1.0,2.0,3.0,4.0,5.0});
}

TEST(gtest_testhw2Arr, testDefaultCopyConstructor){
    t_CopyConstructor<int>(std::initializer_list<int>{1,2,3,4,5});
    t_CopyConstructor<double>(std::initializer_list<double>{1.0,2.0,3.0,4.0,5.0});
}

//#pragma endregion testHWArr2Class

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}