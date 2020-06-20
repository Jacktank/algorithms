
//
// Created by jackstan on 20-6-20.
//

#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <assert.h>

// thread dead lock
#if 0
void thread1(int& count, std::mutex& mtA, std::mutex& mtB) {
    int max_iter = count / 2;
    for (int i = 0; i < max_iter; i++) {
        std::lock_guard<std::mutex> lockGuard1(mtA);
        std::cout << "get the first mutex" << " in thread " << std::this_thread::get_id() << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        std::lock_guard<std::mutex> lockGuard2(mtB);
        std::cout << "get the second mutex" << " in thread " << std::this_thread::get_id() << std::endl;

        count--;
        std::cout << "thread 1: " <<  count << std::endl;
        ++i;
    }
}

void thread2(int& count, std::mutex& mtA, std::mutex& mtB) {
    int max_iter = count / 2;
    for (int i = 0; i < max_iter; i++) {
        std::lock_guard<std::mutex> lockGuard1(mtB);
        std::cout << "get the second mutex" << " in thread " << std::this_thread::get_id() << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        std::lock_guard<std::mutex> lockGuard2(mtA);
        std::cout << "get the first mutex" << " in thread " << std::this_thread::get_id() << std::endl;

        count--;
        std::cout << "thread 2: " <<  count << std::endl;
        ++i;
    }
}
#endif


#if 0
void thread1(int& count, std::mutex& mtA, std::mutex& mtB) {
    int max_iter = count / 2;
    for (int i = 0; i < max_iter; i++) {
        //lock multi mutex;
        std::lock(mtA, mtB);

        // make a lock_guard to unlock when deconstruct lock_guard itself;
        // give parameter std::adopt_lock to avoid relock mutex;
        std::lock_guard<std::mutex> lockGuard1(mtA, std::adopt_lock); //just construct lock_guard but not lock mt
        std::cout << "get the first mutex" << " in thread " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        // make a lock_guard to unlock when deconstruct lock_guard itself;
        // give parameter std::adopt_lock to avoid relock mutex;
        std::lock_guard<std::mutex> lockGuard2(mtB, std::adopt_lock); //just construct lock_guard but not lock mt
        std::cout << "get the second mutex" << " in thread " << std::this_thread::get_id() << std::endl;

        count--;
        std::cout << "thread 1: " <<  count << std::endl;
        ++i;
    }
}

void thread2(int& count, std::mutex& mtA, std::mutex& mtB) {
    int max_iter = count / 2;
    for (int i = 0; i < max_iter; i++) {
        //lock multi mutex;
        std::lock(mtA, mtB);

        // make a lock_guard to unlock when deconstruct lock_guard itself;
        // give parameter std::adopt_lock to avoid relock mutex;
        std::lock_guard<std::mutex> lockGuard1(mtB, std::adopt_lock);
        std::cout << "get the second mutex" << " in thread " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        // make a lock_guard to unlock when deconstruct lock_guard itself;
        // give parameter std::adopt_lock to avoid relock mutex;
        std::lock_guard<std::mutex> lockGuard2(mtA, std::adopt_lock);
        std::cout << "get the first mutex" << " in thread " << std::this_thread::get_id() << std::endl;

        count--;
        std::cout << "thread 2: " <<  count << std::endl;
        ++i;
    }
}
#endif


#if 1
void thread1(int& count, std::mutex& mtA, std::mutex& mtB) {
    int max_iter = count / 2;
    for (int i = 0; i < max_iter; i++) {
        // make a unique_lock to unlock when deconstruct unique_lock itself;
        std::unique_lock<std::mutex> unique_lock1(mtA, std::defer_lock); //just construct unique_lock but not lock mt!!!
        std::cout << "get the first mutex" << " in thread " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        // make a unique_lock to unlock when deconstruct unique_lock itself;
        std::unique_lock<std::mutex> unique_lock2(mtB, std::defer_lock); //just construct unique_lock but not lock mt!!!
        std::cout << "get the second mutex" << " in thread " << std::this_thread::get_id() << std::endl;

        //lock multi mutex;
        std::lock(mtA, mtB);

        assert(unique_lock1.owns_lock() == true);

        count--;
        std::cout << "thread 1: " <<  count << std::endl;
    }
}

void thread2(int& count, std::mutex& mtA, std::mutex& mtB) {
    int max_iter = count / 2;
    for (int i = 0; i < max_iter; i++) {
        // make a unique_lock to unlock when deconstruct unique_lock itself;
        std::unique_lock<std::mutex> unique_lock1(mtB, std::defer_lock); //just construct unique_lock but not lock mt!!!
        std::cout << "get the second mutex" << " in thread " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        // make a unique_lock to unlock when deconstruct unique_lock itself;
        std::unique_lock<std::mutex> unique_lock2(mtA, std::defer_lock); //just construct unique_lock but not lock mt!!!
        std::cout << "get the first mutex" << " in thread " << std::this_thread::get_id() << std::endl;

        //lock multi mutex;
        std::lock(mtA, mtB);

        assert(unique_lock1.owns_lock() == true);

        count--;
        std::cout << "thread 2: " <<  count << std::endl;
    }
}
#endif



int main(int argc, char* argv[]) {

    int count = 200;

    std::mutex mutex1;
    std::mutex mutex2;

    std::thread th1 = std::thread(thread1, std::ref(count), std::ref(mutex1), std::ref(mutex2));
    std::thread th2 = std::thread(thread2, std::ref(count), std::ref(mutex1), std::ref(mutex2));

    th1.join();
    th2.join();
    std::cout << "main is end..." << std::endl;
    return 0;
}

