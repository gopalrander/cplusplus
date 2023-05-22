#include <concepts>
#include <iostream>

class OuterClass
{
    public:
    int GetValue()
    {
        return 10;
    }

    public:
    class InnerClass
    {
        public:
        int GetInnerValue()
        {
            if constexpr ( requires { GetValue(); } )
            {
                return GetValue();
            }
            else
            {
                return 0;
            }
        }
    };
};

int main()
{
    OuterClass::InnerClass x;
    int val = x.GetInnerValue();
    std::cout<<val<<std::endl;
}

/*
Question: 

Why does the code compile when the 'if constexpr' is inside the 'lambda', but does not compile if I remove the lambda enclosing it?
compilation error is "'OuterClass::GetValue': a call of a non-static member function requires an object"

How is the lambda guarding from this error?
*/