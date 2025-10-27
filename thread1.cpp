#include <iostream>
#include <thread>
#include <vector>

void test(int num)
{
    std::cout << num << " Is p2's parameter \n";
};

int main() 
{
    auto lambdaThread = [] (int num) {
        std::cout << "I am lambda thread "<<  num << "\n";
        std::cout << "My ID: " << std::this_thread::get_id() <<  "\n";
    };

    std::vector<std::jthread> threads;

    threads.emplace_back(lambdaThread, 25);

    for (int i {}; i < 100; i++)
    {
        threads.emplace_back(lambdaThread, i);
        //threads[i].join();
    }
    
    threads.emplace_back(&test, 100);
    

    //for (auto& t : threads)
        //t.join();

     std::cout << "Hardware concurrency: "
              << std::thread::hardware_concurrency()
              << " threads\n";

    //return 0;
}