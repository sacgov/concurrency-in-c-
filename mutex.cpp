//
// Created by Sachin Govind on 12/01/23.
//

#include <mutex>
#include <iostream>
#include <thread>
using namespace std;


string largeString(string s) {
    int count = 10;
    while(count--) {
        string copy = s;
       s.append(copy);
    }
    return s;
}
void hello( string s) {
    for(auto  c : largeString(s)) cout<<c;
}


//catch (const std::exception &exc)
//{
//    // catch anything thrown within try block that derives from std::exception
//    std::cerr << exc.what();
//}

class Printer {
    mutex m;
public:
    void print(string s) {
        m.lock();
        hello(s);
        m.unlock();
    }
};

void mhello( string s) {
    Printer p;
    p.print(s);
}
int main (){

    // interleaves a,b
//    thread t1(hello,a);
//    thread t2(hello, "b");
//    t1.join();
//    t2.join();

    // does not interleaves a,b
    thread t1(mhello,"a");
    thread t2(mhello, "b");
    t1.join();
    t2.join();

}
