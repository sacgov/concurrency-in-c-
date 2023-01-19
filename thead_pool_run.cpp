//
// Created by Sachin Govind on 13/01/23.
//

#include "concurrent_queue.h"
#include "thread_pool.h"
#include <iostream>
using namespace std;

void hello() {
    cout<<time(0)<<" "<<"sachin"<<endl;
//    this_thread::sleep_for(1s);

}

int main() {
    thread_pool pool(5);
    time_t t = time(0);
    for(int i =0;i<4;i++){
        pool.submit(t,hello);
    }
    this_thread::sleep_for(5s);


}