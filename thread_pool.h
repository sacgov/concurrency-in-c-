//
// Created by Sachin Govind on 13/01/23.
//

#ifndef CONCURRENCY_THREAD_POOL_H
#define CONCURRENCY_THREAD_POOL_H

#endif //CONCURRENCY_THREAD_POOL_H

#include "concurrent_queue.h"
#include <functional>
#include <thread>
#include <vector>
#include <iostream>
using namespace std;
using Func = std::function<void()>;

class thread_pool {
    concurrent_queue<Func > tasks;
    std::vector<std::thread> threads;
    void worker() {
        while(true) {
            Func task;
            tasks.pop(task);
            task();
        }
    };
    unsigned int _capacity;
public:
    thread_pool(unsigned int capacity) {
        _capacity = capacity;
        cout<<"creating with "<<capacity<<endl;
        for (unsigned i = 0; i < _capacity; ++i)
            threads.emplace_back(&thread_pool::worker, this);
        cout<<"creating done "<<capacity<<endl;
    };
    thread_pool() {
        _capacity  = std::thread::hardware_concurrency();
        for (unsigned i = 0; i < _capacity; ++i)
            threads.emplace_back(&thread_pool::worker, this);
    };
    ~thread_pool(){
        cout<<"destructor"<<endl;
        for(auto &t:threads) {
            t.join();
        }
    };
    void submit(time_t t, Func f) {
        cout<<"submitting "<<t<<" "<<endl;
        tasks.push(t,f);
    }
};
