#include <iostream>

//capture lambda within itself, and pass it recursively. 
// or use 'this' for implicit first param. 'python'
int main()
{
    auto f = [] (int i) {
        if (i < 1)
        {
            return 1;
        }
        else
        {
            return i * f(i-1);
        }
    };

    std::cout<<f(5)<<std::endl;

    return 0;
}