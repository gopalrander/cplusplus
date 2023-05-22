#include <iostream>
#include <vector>
#include <set>
#include <concepts>
#include <complex>
// tempate code is compiled for all the types T,
// which compiler sees at compile time.
// One reason to define the template in header files.
 
// Concept checks for the code inside requires() {...} is not ill-formed, valid substition.
// It is not called. It is code we check if it is valid(?) 
template<typename T>
concept SupportsLessThan = requires (T x) { x < x; };

template<typename T>
requires std::copyable<T> && SupportsLessThan<T>
[[nodiscard]] T MyMax(T a, T b)
{
    return b < a ? a : b;
}

void UseMyMax ()
{
    std::cout<<MyMax(42, 77)<<std::endl;
    std::cout<<MyMax("hello", "world")<<std::endl;

    // can specifiy the type if we want to
    std::cout<<MyMax<std::string>("Hello", "world")<<std::endl;

    std::cout<<MyMax<double>(1, 1.4)<<std::endl;

    // std::complex<int> c1, c2;
    // std::cout<<MyMax(c1, c2)<<std::endl;
}

int main()
{
    UseMyMax();
    return 0;
}
