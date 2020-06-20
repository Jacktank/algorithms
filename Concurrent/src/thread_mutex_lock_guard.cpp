//
// Created by jackstan on 20-6-20.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <assert.h>

#if 0
void thread1(int& count, std::mutex& mtx) {
    for (int i = 0; i < 100;) {
        if (mtx.try_lock()) {
            count--;
            std::cout << "thread 1: " <<  count << std::endl;
            if (count > 100 && count < 199) {
                // neither exit error or not, but with no unlock;
                // other thread will block forever until user kill program
                return;
            }

            ++i;
            mtx.unlock();
        }
    }
}

void thread2(int& count, std::mutex& mtx) {
    for (int i = 0; i < 100;) {
        if (mtx.try_lock()) {
            count--;
            std::cout << "thread 2: " <<  count << std::endl;

            ++i;
            mtx.unlock();
        }
    }
}

void thread3(int& count, std::mutex& mtx) {
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


#if 1
void thread1(int& count, std::mutex& mtx) {
    for (int i = 0; i < 100;) {
        std::lock_guard<std::mutex> lockGuard(mtx);
        count--;
        std::cout << "thread 1: " <<  count << std::endl;
        if (count > 200 && count < 269) {
            // neither exit error or not, mutex will unlock along with lockGuard's deconstruction
            // and other threads will continue;
            return;
        }

        ++i;
        //mtx.unlock(); //no need unlock as lock_gurad will deconstruct itself and unlock the mutex;
    }
}

void thread2(int& count, std::mutex& mtx) {
    for (int i = 0; i < 100;) {
        std::lock_guard<std::mutex> lockGuard(mtx);
        count--;
        std::cout << "thread 2: " <<  count << std::endl;

        ++i;
        //mtx.unlock(); //no need unlock as lock_gurad will deconstruct itself and unlock the mutex;
    }
}

void thread3(int& count, std::mutex& mtx) {
    for (int i = 0; i < 100;) {
        std::lock_guard<std::mutex> lockGuard(mtx);
        count--;
        std::cout << "thread 3: " <<  count << std::endl;

        ++i;
        //mtx.unlock(); //no need unlock as lock_gurad will deconstruct itself and unlock the mutex;
    }
}
#endif


int main(int argc, char* argv[]) {

    int count = 300;
    std::mutex mtx;

    std::thread th1 = std::thread(thread1, std::ref(count), std::ref(mtx));
    std::thread th2 = std::thread(thread2, std::ref(count), std::ref(mtx));
    std::thread th3 = std::thread(thread3, std::ref(count), std::ref(mtx));

    th1.join();
    th2.join();
    th3.join();
    std::cout << "main is end..." << std::endl;
    return 0;
}