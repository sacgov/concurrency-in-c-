//
// Created by Sachin Govind on 12/01/23.
//

#include <future>
#include <chrono>
#include <iostream>
using namespace std::literals;
using namespace std;

void produce(std::promise<int>&p) {

        std::this_thread::sleep_for(10ms);
        int x = 42;
        p.set_value(x);
        cout<<"set "<<x<<endl;



}

void consume(std::future<int>&f) {

        std::this_thread::sleep_for(10ms);
        int x = f.get();
        cout<<"got "<<x<<endl;


}

int main() {
    std::promise<int> p;
    std::future<int> f= p.get_future();

    thread fut(consume, std::ref(f));
    thread prom(produce, std::ref(p));

    fut.join();
    prom.join();
}


