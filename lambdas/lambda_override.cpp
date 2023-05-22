#include <iostream>
#include <variant>

// this defines a overload structs which we are going to derive from lambdas.
// it'scompiler smart in selecting the actual overide () it will call.
template<typename... Ts>
struct Overload: Ts...
{
    using Ts::operator()...;
};

int main()
{
    Overload func = 
    {
        [](int i) { std::cout<<"int overload called"<<std::endl; },
        [](float f) { std::cout<<"float overload called"<<std::endl; },
    };

    std::variant<int, float> v = 2.0f;
    std::visit(func, v);

    return 0;
}

