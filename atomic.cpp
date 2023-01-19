//
// Created by Sachin Govind on 12/01/23.
//


//volatile is needed if you are reading from a spot in memory that,
//say, a completely separate process/device/whatever may write to.
//
//I used to work with dual-port ram in a multiprocessor system in straight C.
//
//void waitForSemaphore()
//{
//    volatile uint16_t* semPtr = WELL_KNOWN_SEM_ADDR;/*well known address to my semaphore*/
//    while ((*semPtr) != IS_OK_FOR_ME_TO_PROCEED);
//}
//Without volatile, the optimizer sees the loop as useless.
//The guy never sets the value! He's nuts, get rid of that code!)
//and my code would proceed without having acquired the semaphore, causing problems later on.

//C++ threads have a nice set of surrounding classes, such as promise.
//Now you can actually throw exceptions from your threads without causing the whole program to crash!

#include <pthread.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdatomic.h>

volatile atomic_flag mut; // false; true = locked; false = unlocked

// void acquire(mut_t * m)
#define acquire(m) while (atomic_flag_test_and_set(m))
// void release(mut_t * m)
#define release(m) atomic_flag_clear(m)

int critical(char * str) {return strlen(str);};

[[noreturn]] void * pingpong(void * p) {
    char * msg = (char *) p;
    for (;;) {
        acquire(&mut);
        critical(msg);
        release(&mut);
    } // for
} // pingpong

#define PING "ping"
#define PONG "pong"

int main() {
    setvbuf(stdout, nullptr, _IONBF, 0);
    pthread_t ping;
    pthread_t pong;
    pthread_create(&ping, NULL, pingpong, (void *) PING);
    pthread_create(&pong, NULL, pingpong, (void *) PONG);
    for(;;);
    return 0;
} // main