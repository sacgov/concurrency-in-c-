//
// Created by Sachin Govind on 12/01/23.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex the_mutex;

void task1() {
    cout << "Task1 trying to get lock" << endl;
    the_mutex.lock();
    cout << "Task1 has lock" << endl;
    this_thread::sleep_for(500ms);
    cout << "Task1 releasing lock" << endl;
    the_mutex.unlock();
}

void task2() {
    this_thread::sleep_for(500ms);
    cout << "Task2 trying to get lock" << endl;
    while (!the_mutex.try_lock()) {
        cout << "Task2 could not get lock" << endl;
        this_thread::sleep_for(100ms);
    }
    cout << "Task2 has lock" << endl;
    the_mutex.unlock();
}


void exc() {
    //throw std::exception();
    the_mutex.lock();
    throw std::exception();
    cout << "Task2 has lock" << endl;
    the_mutex.unlock();
}

void texc() {
    try {
        //throw std::exception();

        the_mutex.lock();
        throw std::exception();
        cout << "Task2 has lock" << endl;
        the_mutex.unlock();

    }catch (...) {
        the_mutex.unlock();
    }

}

void lexc (){
    //acquires lock
    lock_guard<mutex> m(the_mutex);
    bool shallUnlock = false;
    if(shallUnlock) {
        the_mutex.unlock();
    }
    cout<<"exiting lexc";

};


void utask1() {
    cout << "Task1 trying to get lock" << endl;
    unique_lock ul(the_mutex);
    cout << "Task1 has lock" << endl;
    this_thread::sleep_for(500ms);
    cout << "Task1 releasing lock" << endl;
}

void utask2() {
    this_thread::sleep_for(500ms);
    cout << "Task2 trying to get lock" << endl;
    unique_lock ul(the_mutex, std::defer_lock);

    while (!ul.try_lock()) {
        cout << "Task2 could not get lock" << endl;
        this_thread::sleep_for(100ms);
    }
    cout << "Task2 has lock" << endl;
}


int main() {
//    thread t1{task1}, t2{task2};
//    t1.join();
//    t2.join();


//    thread te(exc);
//    te.join();

    // task 2 will never start and while loops continously
    // add unlock in catch to fix
//    thread te(texc);
//    te.join();


//    thread te(lexc);
//    te.join();
//    thread ts(task2);
//    ts.join();

//    thread t1{utask1}, t2{utask2};
//    t1.join();
//    t2.join();

// recursive mutex is not normally needed
}
