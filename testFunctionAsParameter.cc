#include <stdio.h>
#include <iostream>
#include <functional>
#include <chrono>

namespace cr = std::chrono;

using my_clock = cr::high_resolution_clock;
using Callback = std::function<void()>;

static const int kIterateCount = 100000000;

class CallbackHolder
{
public:

    void SetCallbackValue(Callback cb)
    {
        cb_ = std::move(cb);
    }

    void SetCallbackConstRef(const Callback& cb)
    {
        cb_ = cb;
    }

    void SetCallbackRefRef(Callback&& cb)
    {
        cb_ = std::move(cb);
    }

    void DoCallback()
    {
        cb_();
    }

private:

    Callback cb_;
};

class CallbackProvider
{
public:

    CallbackProvider()
        : value_(0)
    {
    }

    void DoSomething()
    {
        ++value_;
        //std::cout << "DoSomething value:" << value_ << std::endl;
    }

    int GetValue() const { return value_; }

private:

    int value_;
};

void TestConstRef()
{
    auto start_time = my_clock::now();

    CallbackHolder holder;
    CallbackProvider provider;
    for (int i = 0; i < kIterateCount; ++i)
    {
        //holder.SetCallbackConstRef(BIND_REF(provider, CallbackProvider::DoSomething));
        holder.SetCallbackConstRef([&](){provider.DoSomething();});
        holder.DoCallback();
    }

    auto end_time = my_clock::now();
    auto diff = end_time - start_time;
    auto milliseconds = cr::duration_cast<cr::milliseconds>(diff);
    auto millisecond_count = milliseconds.count();

    std::cout << "TestConstRef value: " << provider.GetValue() << std::endl;
    std::cout << "TestConstRef: " << millisecond_count << " ms\n";
}

void TestRefRef()
{
    auto start_time = my_clock::now();

    CallbackHolder holder;
    CallbackProvider provider;
    for (int i = 0; i < kIterateCount; ++i)
    {
        //holder.SetCallbackRefRef(BIND_REF(provider, CallbackProvider::DoSomething));
        holder.SetCallbackRefRef([&](){provider.DoSomething();});
        holder.DoCallback();
    }

    auto end_time = my_clock::now();
    auto diff = end_time - start_time;
    auto milliseconds = cr::duration_cast<cr::milliseconds>(diff);
    auto millisecond_count = milliseconds.count();

    std::cout << "TestRefRef value: " << provider.GetValue() << std::endl;
    std::cout << "TestRefRef: " << millisecond_count << " ms\n";
}

void TestValue()
{
    auto start_time = my_clock::now();

    CallbackHolder holder;
    CallbackProvider provider;
    for (int i = 0; i < kIterateCount; ++i)
    {
        //holder.SetCallbackValue(BIND_REF(provider, CallbackProvider::DoSomething));
        holder.SetCallbackValue([&](){provider.DoSomething();});
        holder.DoCallback();
    }

    auto end_time = my_clock::now();
    auto diff = end_time - start_time;
    auto milliseconds = cr::duration_cast<cr::milliseconds>(diff);
    auto millisecond_count = milliseconds.count();

    std::cout << "TestValue value: " << provider.GetValue() << std::endl;
    std::cout << "TestValue: " << millisecond_count << " ms\n";
}

int main()
{
    TestValue();
    TestConstRef();
    TestRefRef();
    return 0;
}
