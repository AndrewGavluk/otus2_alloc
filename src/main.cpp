#include <iostream>
#include "../libs/hw2Arr.h"

#define UNUSED(expr) do { (void)(expr); } while (0)


int main(void)
{
    hw2Array<double> * hw2arr;
    UNUSED(hw2arr);

    hw2arr = new hw2Array<double>();
    delete hw2arr;
    return 0;
}
