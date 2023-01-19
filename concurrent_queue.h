//
// Created by Sachin Govind on 13/01/23.
//

#ifndef CONCURRENCY_CONCURRENT_QUEUE_H
#define CONCURRENCY_CONCURRENT_QUEUE_H

#include <mutex>
#include <queue>
#include <utility>
#include <map>
#include <ctime>
#include <iostream>
using namespace std;

template <class T>
class concurrent_queue {
    std::mutex m;
    std::condition_variable cv;
    std::priority_queue<std::pair<time_t,int>,std::vector<std::pair<time_t,int>>,std::greater<>> q;
    std::map<int,T> items;
    int current_task = 0;
public:
    void push(time_t t,T value){
        cout<<"start pushing "<<t<<endl;
        std::lock_guard<std::mutex> lk(m);
        current_task++;
        items[current_task] = value;
        q.emplace(t,current_task);
        cv.notify_one();
        cout<<"done pushing "<<t<<endl;

    }
    void pop(T& value) {
        std::unique_lock<std::mutex> ul(m);
        //&& q.top().first < time(nullptr)
        cv.wait(ul,[this]{

            bool notEmpty = !q.empty() ;
            if(notEmpty) {
                cout<< q.top().first<<" "<<time(nullptr)<<endl;
            }
            return notEmpty && q.top().first<=time(nullptr) ;
        });
        int item = q.top().second;
        value = items[item];
        q.pop();
        cout<<"popoed "<<item<<endl;
    }



};


#endif //CONCURRENCY_CONCURRENT_QUEUE_H
