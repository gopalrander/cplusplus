#include <coroutine>
#include <iostream>

struct resumable_thing
{
    resumable_thing() = default;
    resumable_thing(resumable_thing const&) = delete;
    resumable_thing& operator=(resumable_thing const&) = delete;

    resumable_thing(resumable_thing&& other) : _coroutine(other._coroutine)
    {
        other._coroutine = nullptr;
    }

    resumable_thing& operator=(resumable_thing&& other) 
    {
        if(&other != this)
        {
            _coroutine = other._coroutine;
            other._coroutine = nullptr;
        }
    }

    struct promise_type
    {
        resumable_thing get_return_object()
        {
            return resumable_thing(std::coroutine_handle<promise_type>::from_promise(*this));
        }

        auto initial_suspend() { return std::suspend_never{}; }
        auto final_suspend() noexcept { return std::suspend_never{}; }

        void return_void() {}

        void unhandled_exception() {}
    };

    std::coroutine_handle<promise_type> _coroutine = nullptr;

    explicit resumable_thing(std::coroutine_handle<promise_type> coroutine) :
        _coroutine(coroutine) {}

    ~resumable_thing()
    {
        if (_coroutine) 
        {
            _coroutine.destroy();
        }
    }

    void resume() {}
};

resumable_thing generator()
{
    for (int i = 0; ; i++)
    {
        co_await std::suspend_always{};
        std::cout<<"counter resumed: #" << i << std::endl;
    }
};

int main()
{
    resumable_thing the_gen = generator();
    the_gen.resume();
    the_gen.resume();
    return 0;
}