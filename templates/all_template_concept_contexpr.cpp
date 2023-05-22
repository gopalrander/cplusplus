#include <set>
#include <vector>
#include <concepts>
#include <iostream>

template<typename Coll>
concept HasPushBack = requires(Coll c, Coll::value_type v) 
{
    c.push_back(v);
};

template<typename Coll>
concept HasInsert = requires(Coll c, Coll::value_type v) 
{
    c.insert(v);
};

template<typename T>
concept IsIntegerOrFloat = std::is_integral_v<T> || std::is_floating_point_v<T>;

template<typename T, typename U>
requires HasPushBack<T>
void Add(T& Coll, const U& val)
{
    Coll.push_back(val);
}

template<typename T, typename U>
requires HasInsert<T>
void Add(T& Coll, const U& val)
{
    Coll.insert(val);
}


/*
void Add(auto& Coll, const auto& val)
{
    Coll.push_back(val);
}

void Add(auto& Coll, const auto& val)
{
    Coll.insert(val);
}
*/

/*
void Add(auto& Coll, const auto& val)
{
    if constexpr( requires { Coll.push_back(val); } )
    {
        Coll.push_back(val);
    }
    else if constexpr( requires { Coll.insert(val); } )
    {
        Coll.insert(val);
    }
    else 
    {
        //...
    }
}
*/

template<typename T>
T Addition(T a, T b)
{
    if constexpr(std::is_arithmetic_v<T>)
    {
        return a + b;
    }
    else if constexpr(std::is_same_v<std::remove_cvref_t<T>, std::string>)
    {
        return a + " " + b;
    }
    else
    {
        return;
    }
}

// one way of doing it is using concepts. 
// but has many separate parts.

// Lets see if we can use 'if'

void UseAdd()
{
    std::vector<int> coll1;
    std::set<int> coll2;

    Add(coll1, 42);
    Add(coll2, 42);
}

void UseAddition()
{
    std::cout<<Addition(1,2)<<std::endl;

    std::string s1 {"foo"};
    std::string s2 {"bar"};
    std::cout<<Addition(s1,s2)<<std::endl;

    std::vector v1 {1,2,3};
    std::vector v2 {2,3,4};
    Addition(v1,v2);
}

int main()
{
    UseAddition();
}
