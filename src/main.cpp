#include <iostream>
#include <map>

#include "../libs/hw2Arr.h"
#include "../libs/Alloc.h"

template <typename T>
void test(T& Map,const int& limmit){
    int i_factorial{1};
    for (int i=0; i<limmit; i++)
    {
        i_factorial*=(i+1);
        Map[i] = i_factorial;
    }

    for (int i=0; i<limmit; i++)
        std:: cout << "map[" << i << "]= " <<  Map[i] << ";" <<std::endl; 
    std:: cout  << std::endl; 

}

int main()
{
    // test map with std allocator
    constexpr int limmit = 10;
    using iMap = std::map<int, int>;
    iMap stdAlocatorSample;
    test<iMap>(stdAlocatorSample, limmit);
   
    // test map with custom allocator
    using customAlloc_t = Homework2::allocatorHW2< std::pair< int, int>, limmit + 1>;
    using customAllocMap_t = std::map< int, int,  std::less<int>, customAlloc_t>;
    customAllocMap_t cstAlocatorSample;
    test<customAllocMap_t>(cstAlocatorSample, limmit);

    // test custom container with  std allocator
    using ihw2Arr = hw2Array<int>;
    ihw2Arr test_ihw2Arr(limmit+1);
    test<ihw2Arr> (test_ihw2Arr, limmit);
        
    // test custom container with  std allocator
    using customAlloc_t2 = Homework2::allocatorHW2< int, limmit + 1>;
    using customAlloc_ihw2Arr = hw2Array<int, customAlloc_t2 >;
    customAlloc_ihw2Arr test_ihw2Arr2(limmit+1);
    test<customAlloc_ihw2Arr> (test_ihw2Arr2, limmit);

    

}
