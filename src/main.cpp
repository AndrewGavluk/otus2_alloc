#include <iostream>
#include <map>
#include "../libs/hw2Arr.h"
#include "../libs/Alloc.h"


int main()
{
    const int limmit = 10;
    std::map<int, int> stdAlocatorSample;
    
    long long i_factorial{1};
    for (int i=1; i<limmit; i++)
    {
        i_factorial*=i;
        stdAlocatorSample.insert(std::make_pair(i, i_factorial));
    } 
}
