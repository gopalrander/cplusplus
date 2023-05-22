#include <vector>
#include <iostream>

//lvalue ref
void Fun(std::vector<int>& v)
{
    std::cout<<"by ref"<<std::endl;
}

// const lvalue ref
void Fun(const std::vector<int>& v)
{
    std::cout<<"by const ref"<<std::endl;
}

//by Rvalue move ref
// this means the caller has given up on v.
void Fun(std::vector<int>&& v)
{
    std::cout<<"by move ref"<<std::endl;
}

void UseFun()
{
    std::vector v {1, 2, 3};
    const std::vector cv {4, 5, 6};

    Fun(v);
    Fun(cv);
    Fun({7, 8, 9});

    // what if we know that we are not going to use v here?
    // may be after some point this function can give up. 

    // std::move()
    // this actually does not move anything. It just marks the value passed to be moved.
    // it is actually a cast to && type (r-value).
    // it is static_cast<decltype(v)&&>(v)
    Fun(std::move(v));
    // point to note that if the rvalue overload does not exist, it will fallback to const lvalue
    
    // ideally this function should not be using/referring to 'v' after std::move(v)
    // C++ does a non-destructive move. valid, but unknown.
    std::cout<<v[1]<<std::endl;
}

struct Person
{
    std::string name;
    int age;

    //All the default constructors and destructors from compiler
};

void Excercise()
{
    std::vector<Person> people;
    for(int i=0; i<2; i++)
    {
        Person p{std::move("person"), i+1};
        people.emplace_back(std::move(p));

        std::cout<<"content: "<<i<<std::endl;
        std::cout<<p.name<<std::endl;
        std::cout<<people[i].name<<std::endl;
    }
}

// passing with non-const lvalue ref. (not recommended, know well what are you doing)
void Innocent(std::string& value)
{
    std::string local = std::move(value);
}

void UseInnocent()
{
    std::string s{"It uses a minimalist and well looking design. Many other extensions of this type simply complicate this task, using really extensive code. The main purpose of this one, is to use the less amount of code and help the developer/user to get the job done"};
    Innocent(s);
    std::cout<<s<<std::endl;   
}


int main()
{
    UseFun();

    //Excercise();

    //UseInnocent();
    
    return 0;
}