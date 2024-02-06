#include <iostream>
extern "C" int _cdecl sumthree(int, int, int);

int main()
{
    std::cout << sumthree(1,2,3);
}