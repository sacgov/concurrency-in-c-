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
