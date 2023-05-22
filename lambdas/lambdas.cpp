// Lambda is a class closure.
// - has a public inline () operator.
// --- the call operator is const by default. If lamda is modifying, then it has to be mutable.
// --- the call operator is NOT noexcept by default.  
// - name of the closure type is unique.
// In C++ 11, the default constructor and assignment operator is marked deleted. 

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// lambdas are const by default. 
//mutable lambdas, 
struct Person{
    std::string name;
    int age_in_years;
};

void SortPeople(std::vector<Person>& people)
{
    std::sort(people.begin(), people.end(), 
        [](const Person& lhs, const Person& rhs)
        {
            return lhs.age_in_years < rhs.age_in_years;
        });
}

void AddN(std::vector<int> v, int n)
{
}

// Immediately invoked lamdas? we can either () at the end of lambda, or use std::invoke([](){})
// Use case: when we have to initialise conditionally?
// -- we can use ternary operator for simple cases, but not great if there are many branches. 
// -- another way is to split the code and return the object from a function and assign it to var.. 
// -----here also, if ther are many params to pass, it gets messy
void InitSomeConstObject(int input)
{
    int const_int = 10;
    if (input == 0)
    {
        const_int = 10;
    }
    else
    {
        const_int = 11;
    }
}

//another use case, if we want a method to be only called once.
// overhead that every creation would check/some locks etc., but very simple. 
struct SomeWierdType
{
    SomeWierdType()
    {
        static auto temp = std::invoke([]{ std::cout<<"called once!"<<std::endl; return 0;} );
    }
};

// lambdas can be constexpr > c++17

int main()
{
    auto fn = [](int i) { return i*i; };

    SomeWierdType s1;
    SomeWierdType s2;
    SomeWierdType s3;
    
    auto callTwice = [](auto&& f) 
            { return [=]{ f(); f(); }; };
    
    std::invoke( callTwice([] { std::cout<<"hi"; } ));

    return 0;

}


