#include <iostream>
#include <thread>
using namespace std;
void hello(){
    cout<<"Hello thread!"<<endl;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    // we do not see the hello thread
    thread t(hello);
    //now we see it
    t.join();
    return 0;
}
