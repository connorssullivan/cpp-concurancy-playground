#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::mutex lock;

static int shared_var = 0;

void test(int num)
{
    lock.lock();
        std::cout << num << " Is p2's parameter \n";
        shared_var++;
    lock.unlock();
};

int main() 
{
    auto lambdaThread = [] (int num) {
        lock.lock();
            std::cout << "I am lambda thread "<<  num << "\n";
            std::cout << "My ID: " << std::this_thread::get_id() <<  "\n";
            shared_var++;
            std::cout << "Shared_var is currentyly "<<  shared_var << "\n";
        lock.unlock();
    };

    std::vector<std::thread> threads;

    //threads.emplace_back(lambdaThread, 25); //Forgot to join

    for (int i {1}; i < 10; i++)
    {
        threads.emplace_back(lambdaThread, i);
        //threads.back().join();
    }
    
    threads.emplace_back(&test, 100);
    //threads.back().join();

    for (int i {}; i < threads.size(); i++)
        threads[i].join();


     std::cout << "Hardware concurrency: "
              << std::thread::hardware_concurrency()
              << " threads\n";

    //return 0;
}