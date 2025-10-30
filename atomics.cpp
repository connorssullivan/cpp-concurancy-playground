#include <thread> 
#include <iostream>
#include <vector>

static std::atomic<int> a_value = 0;
static std::atomic<bool> b_value = false;

void atomic_func()
{
    a_value += 10;
};

void holdWait() 
{
    while (b_value.load(std::memory_order_acquire))
    {
        // do something
    }

    std::cout << "Worker has been set to true\n";
};


int main()
{
    std::vector<std::thread> threads;

    for (int i {}; i < 10; i++)
        threads.emplace_back(&atomic_func);

    for (int i {}; i < threads.size(); i++)
        threads[i].join();
    
    std::cout << a_value << "\n" ;

    std::thread t(&holdWait);
    t.join();
    b_value.store(true, std::memory_order_release);

    return 0;
}