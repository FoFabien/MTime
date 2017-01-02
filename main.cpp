#include <iostream>
#include "mtime.hpp"

using namespace std;

// example

int main()
{
    MClock test4;

    MTime test1 = MTime::s2time(1.45);
    MTime test2 = MTime::ms2time(456);
    cout << test1.to_us() << "us + " << test2.to_us() << "us = " << (test1 + test2).to_us() << "us" << endl;

    MClock test3;
    for(int32_t i = 0; i < 0xFFFFFFF; ++i);
    cout << test3.get().to_us() << "us" << endl;

    cout << "running time :" << test4.get().to_us() << "us" << endl;
    system("PAUSE");
    return 0;
}
