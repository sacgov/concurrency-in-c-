#include <iostream>
#include <thread>
using namespace std;
void hello(string s){
    cout<<"Hello thread! welcome "<<s<<endl;
}

void helloByRef(string &s){
    s= "changed";
    cout<<"Hello thread! welcome "<<s<<endl;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    // we do not see the hello thread
    thread t(hello, "sachin");

    string sRef = "sachin by ref";
    thread t2(helloByRef, ref(sRef));
    //now we see it
    cout<<sRef<<endl;
    t.join();
    return 0;
}
