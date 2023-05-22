#include <iostream>

// a recursive template
template<typename T, typename... Types>
void PrintAll(T firstArg, Types... args)
{
    std::cout<<firstArg<<std::endl;
    PrintAll(args...);
}
// issue?
// number of parameters.
// lesson to be leant:
// - all the code has be valid at compile time
// - use of constexpr

void UsePrintAll()
{
    PrintAll(1, 2, "hello", 3.5);
}

int main()
{
    UsePrintAll();
}