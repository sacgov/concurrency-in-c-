//
// Created by Sachin Govind on 12/01/23.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <shared_mutex>
#include <vector>

using namespace std;

shared_mutex mut;

void write() {


//    lock_guard<shared_mutex> lk(mut);
    mut.lock();
    cout<<"Writing the data"<<endl;
    this_thread::sleep_for(100ms);

    // without unlocking readers wont start;
    mut.unlock();
}

void read(int i) {

    while (!mut.try_lock_shared()) {
        // this data is garbled
        cout<<"reader "<<i<<" trying"<<endl;
        this_thread::sleep_for(50ms);
    }
    cout<<"reader "<<i<<" completed"<<endl;

    // without this will block writer
    mut.unlock_shared();
}
// shared data can be declared in static inside the function
// global variable
// class member static

#include <mutex>

class some_type {
    // ...
public:
    void do_it() { /*...*/ }
};

//some_type *ptr{nullptr};            // Variable to be lazily initialized
//std::mutex process_mutex;
//
//void process() {
//    if (!ptr) {                                                                                  // First check of ptr
//        std::lock_guard<std::mutex> lk(process_mutex);
//
//        if (!ptr)                  // Second check of ptr
//            ptr = new some_type;   // Initialize ptr
//    }
//    ptr->do_it();
//}

//some_type* ptr{nullptr};         // Variable to be lazily initialized
//
//std::once_flag ptr_flag;         // The flag stores synchronization data
//
//void process() {
//    // Pass a callable object which performs the initialization
//    std::call_once(ptr_flag, []() { ptr = new some_type; });
//    ptr->do_it();
//}
//void process() {
//    static some_type *ptr{new some_type};            // Variable to be lazily initialized
//
//    ptr->do_it();
//}


int main() {
    thread t1{write};
    std::vector<std::thread> rt;
    for(int i =0;i<10;i++) {
        thread t(read,i);
        rt.push_back(std::move(t));
        // join here does not work
    }
    t1.join();
    for(int i=0;i<10;i++) {
        rt[i].join();
    }
    return 0;
}
