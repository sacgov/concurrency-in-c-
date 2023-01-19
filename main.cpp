#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void hello(string s){
    cout<<"Hello thread! welcome "<<s<<endl;
}

thread getThread(string s) {
    return thread(hello,s);
}
// passing will require std::move
//void waitThread(thread t);

void raiseError() {
    try {
        throw (5);
    }
    catch (int myNum) {
        cout << "caught " << myNum <<endl;
    }
}
void notCaught() {

        throw (5);

}

void waitFor() {

    this_thread::sleep_for(1s);

}



int main() {
    std::cout << "Hello, World!" << std::endl;

    auto t = getThread( "sachin");

    // copy does not work
    //    auto t1 = t;

    // new thread could be given the id if the old thread is done
    //    this_thread::sleep_for(50ms);
    t.get_id();
    this_thread::get_id();

    auto te = thread(raiseError);

    // not stack in main program but break it
    // each thread has its own catch
    // auto tne = thread(notCaught);

    // happens late because of sleep for
    auto wt = thread(waitFor);
    wt.join();
    std::cout << "Hello, World! late" << std::endl;
    auto wt2 = thread(waitFor);
    // comes instantly
    std::cout << "Hello, World! late" << std::endl;
    wt2.join();

    //    t.joinable()

    t.join();
    te.join();
    return 0;
}
