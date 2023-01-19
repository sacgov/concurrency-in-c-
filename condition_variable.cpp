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


mutex mut;
condition_variable cv;
string sdata{"Empty"};

// Waiting thread
void reader() {
    unique_lock<std::mutex> guard(mut);      // Acquire lock
    cv.wait(guard);                         // Wait for condition variable to be notified
    cout << "Data is " << sdata << endl;        // Wake up and use the new value
}

// Modyifing thread
void writer() {
    cout << "Writing data..." << endl;
    {
        lock_guard<std::mutex> lg(mut);            // Acquire lock
        std::this_thread::sleep_for(2s);           // Pretend to be busy...
        sdata = "Populated";                       // Modify the data
    }
    cv.notify_one();                               // Notify the condition variable
}

void read() {

    unique_lock<mutex> ul(mut);
    cout << "Starting to wait :" << endl;
    cv.wait(ul);
    cout << "Reading the data :" << sdata << endl;
}

void write() {
    {
        lock_guard<mutex> lk(mut);
        cout << "Writing the data" << endl;
        this_thread::sleep_for(2s);
        sdata = "Populated";
    }

    // note this important wait
    this_thread::sleep_for(10ms);
    cv.notify_one();
    cout<<"notified"<<endl;
}
/*
 * The condition_variable class is a synchronization primitive used with
 * a std::mutex to block one or more threads until another thread both
 * modifies a shared variable (the condition) and notifies the condition_variable.

The thread that intends to modify the shared variable must:

Acquire a std::mutex (typically via std::lock_guard)
Modify the shared variable while the lock is owned
Call notify_one or notify_all on the std::condition_variable (can be done
 after releasing the lock)
Even if the shared variable is atomic, it must be modified while owning
 the mutex to correctly publish the modification to the waiting thread.

Any thread that intends to wait on a std::condition_variable must:

Acquire a std::unique_lock<std::mutex> on the mutex used to protect the shared variable
Do one of the following:
Check the condition, in case it was already updated and notified
Call wait, wait_for, or wait_until on the std::condition_variable
 (atomically releases the mutex and suspends thread execution until
 the condition variable is notified, a timeout expires,
 or a spurious wakeup occurs, then atomically acquires the mutex before returning)
Check the condition and resume waiting if not satisfied
or:
Use the predicated overload of wait, wait_for, and wait_until,
 which performs the same three steps
std::condition_variable works only with std::unique_lock<std::mutex>,
 which allows for maximal efficiency on some platforms.
 std::condition_variable_any provides a condition variable
 that works with any BasicLockable object, such as std::shared_lock.
 */
/*
 *
wait causes the current thread to block until the condition variable is notified or
 a spurious wakeup occurs, optionally looping until some predicate is satisfied
 (bool(stop_waiting()) == true).

1) Atomically unlocks lock, blocks the current executing thread, and adds it to the list of threads
 waiting on *this. The thread will be unblocked when notify_all() or notify_one() is executed.
 It may also be unblocked spuriously. When unblocked, regardless of the reason, lock is reacquired and wait exits.
2) Equivalent to
while (!stop_waiting()) {
    wait(lock);
}
This overload may be used to ignore spurious awakenings while waiting for a specific condition to become true.
Note that lock must be acquired before entering this method, and it is reacquired
 after wait(lock) exits, which means that lock can be used to guard access to stop_waiting().

If these functions fail to meet the postconditions (lock.owns_lock()==true
 and lock.mutex() is locked by the calling thread), std::terminate is called.
 For example, this could happen if relocking the mutex throws an exception.
 */

/*
 *
There are at least two things 'spurious wakeup' could mean:

A thread blocked in pthread_cond_wait can return from the call
 even though no call to pthread_call_signal or pthread_cond_broadcast
 on the condition occurred.
A thread blocked in pthread_cond_wait returns because
 of a call to pthread_cond_signal or pthread_cond_broadcast,
 however after reacquiring the mutex the underlying predicate is found to no longer be true.
But the latter case can occur even if the condition
 variable implementation does not allow the former case.
 Consider a producer consumer queue, and three threads.

Thread 1 has just dequeued an element and released the
 mutex, and the queue is now empty. The thread is doing
 whatever it does with the element it acquired on some CPU.
Thread 2 attempts to dequeue an element, but finds the
 queue to be empty when checked under the mutex, calls
 pthread_cond_wait, and blocks in the call awaiting signal/broadcast.
Thread 3 obtains the mutex, inserts a new element into
 the queue, notifies the condition variable, and releases the lock.
In response to the notification from thread 3, thread 2,
 which was waiting on the condition, is scheduled to run.
However before thread 2 manages to get on the CPU and grab
 the queue lock, thread 1 completes its current task, and
 returns to the queue for more work. It obtains the queue
 lock, checks the predicate, and finds that there is work
 in the queue. It proceeds to dequeue the item that thread 3 inserted, releases the lock, and does whatever it does with the item that thread 3 enqueued.
Thread 2 now gets on a CPU and obtains the lock, but when
 it checks the predicate, it finds that the queue is empty.
 Thread 1 'stole' the item, so the wakeup appears to be
 spurious. Thread 2 needs to wait on the condition again.
So since you already always need to check the predicate
 under a loop, it makes no difference if the underlying
 condition variables can have other sorts of spurious wakeups.

 */

int main() {
    cout << "Data is " << sdata << endl;

    thread w{write};
    thread r{read};
    /*
    // If the writer thread finishes before the reader thread starts, the notification is lost
    thread write{writer};
    std::this_thread::sleep_for(500ms);
    thread read{reader};
    */
    w.join();
    r.join();
}