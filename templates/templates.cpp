#include <iostream>
#include <vector>
#include <set>
#include <complex>
// tempate code is compiled for all the types T,
// which compiler sees at compile time.
// One reason to define the template in header files.
 
// the constraints here:
// defined: both the elements are of same type.
// defined: the type is passed by value. so they must be copyable/movable
// assumed: operator '<' is well defined
// defined: return type is same as input type
template<typename T>
T MyMax(T a, T b)
{
    return b < a ? a : b;
}

// C++20 now allow function template without specifying type names
// the constraints here:
// defined: function is called with reference type.
// assumed: the parameter supports iterating over
// assumed: std::cout << element is well defined for each element
void PrintColl(const auto& collection)
{
    for(const auto& element: collection){
        std::cout<<element<<std::endl;
    }
}

// mutiple template paramaters
template<typename T1, typename T2>
void PrintTwoTypes(const T1& val1, const T2& val2)
{
    std::cout<<val1<<' '<<val2<<std::endl;
}

// what about MyMax? What type should this return now?
// It can either of T1 or T2. This type is known at compile type.
// There are inbuilt rules to decide the return type. 
template<typename T1, typename T2>
T1 MyMaxTwoTypes(T1 a, T2 b)
{
    return b < a ? a : b;
}

// lesson to check by decltype,?
void UseMyMax ()
{
    std::cout<<MyMax(42, 77)<<std::endl;
    std::cout<<MyMax("hello", "world")<<std::endl;

    // can specifiy the type if we want to
    std::cout<<MyMax<std::string>("Hello", "world")<<std::endl;

    std::cout<<MyMax<double>(1, 1.4)<<std::endl;

    std::complex<int> c1, c2;
    std::cout<<MyMax(c1, c2)<<std::endl;
}

void UsePrint()
{
    std::vector v {1, 2, 3};
    PrintColl(v);

    std::vector vf {1.0, 2.0, 3.0};
    PrintColl(v);

    std::set s {"hello", "world"};
    PrintColl(s);

    PrintColl("hello there");
}

int main()
{
    UseMyMax();
    UsePrint();

    return 0;
}

// Now these requirements, which are not explicit are pain to find if some comipilation unit failed due to some requirement failed.
// C++ 20 introduces explicit constraints "Concepts"
