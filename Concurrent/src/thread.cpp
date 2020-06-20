//
// Created by jackstan on 20-6-20.
//

#include <iostream>
#include <thread>

void thread1(int& count) {
    for (int i = 0; i < 100; i++) {
        count--;
        std::cout << "thread 1: " <<  count << std::endl;
    }
}

void thread2(int& count) {
    for (int i = 0; i < 100; i++) {
        count--;
        std::cout << "thread 2: " <<  count << std::endl;
    }
}

void thread3(int& count) {
    for (int i = 0; i < 100; i++) {
        count--;
        std::cout << "thread 3: " <<  count << std::endl;
    }
}

int main(int argc, char* argv[]) {

    int count = 300;
    std::thread th1 = std::thread(thread1, std::ref(count));
    std::thread th2 = std::thread(thread2, std::ref(count));
    std::thread th3 = std::thread(thread3, std::ref(count));

#if 0
    th1.detach();
    th2.detach();
    th3.detach();
#endif

#if 1
    th1.join();
    th2.join();
    th3.join();
#endif

    std::cout << "main is end..." << std::endl;
    return 0;
}