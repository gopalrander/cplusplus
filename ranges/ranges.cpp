#include <ranges>
#include <vector>
#include <iostream>
//#include <views>

int main()
{
    std::vector v {1,2,3,4,5,6,7,8,9};
    auto divisible_by_three = [](const int i){return i%3 == 0;};
    auto squared = [](const int i){return i*i;};

    auto x = v | std::views::filter(divisible_by_three) | std::views::transform(squared);

    for (auto i : x)
    {
        std::cout<<i<<std::endl;
    }
    return 0;
}

