//
// Created by jackstan on 20-6-20.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <assert.h>

std::mutex mtx;

#if 1
void thread1(int& count) {
    for (int i = 0; i < 100;) {
        if (mtx.try_lock()) {
            count--;
            std::cout << "thread 1: " <<  count << std::endl;

            ++i;
            mtx.unlock();
        }
    }
}

void thread2(int& count) {
    for (int i = 0; i < 100;) {
        if (mtx.try_lock()) {
            count--;
            std::cout << "thread 2: " <<  count << std::endl;

            ++i;
            mtx.unlock();
        }
    }
}


void thread3(int& count) {
    for (int i = 0; i < 100;) {
        if (mtx.try_lock()) {
            count--;
            std::cout << "thread 3: " <<  count << std::endl;

            ++i;
            mtx.unlock();
        }
    }
}
#endif


#if 0
void thread1(int& count) {
    for (int i = 0; i < 100;) {
        if (mtx.try_lock()) {
            count--;
            std::cout << "thread 1: " <<  count << std::endl;
            if (count > 200 && count < 299) {
                // neither exit error or not, but with no unlock;
                // other thread will block forever until user kill program
                return;
            }

            ++i;
            mtx.unlock();
        }
    }
}

void thread2(int& count) {
    for (int i = 0; i < 100;) {
        if (mtx.try_lock()) {
            count--;
            std::cout << "thread 2: " <<  count << std::endl;
            
            ++i;
            mtx.unlock();
        }
    }
}


void thread3(int& count) {
    for (int i = 0; i < 100;) {
        if (mtx.try_lock()) {
            count--;
            std::cout << "thread 3: " <<  count << std::endl;

            ++i;
            mtx.unlock();
        }
    }
}
#endif


int main(int argc, char* argv[]) {

    int count = 300;
    std::thread th1 = std::thread(thread1, std::ref(count));
    std::thread th2 = std::thread(thread2, std::ref(count));
    std::thread th3 = std::thread(thread3, std::ref(count));

    th1.join();
    th2.join();
    th3.join();
    std::cout << "main is end..." << std::endl;
    return 0;
}