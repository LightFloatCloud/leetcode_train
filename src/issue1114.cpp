/*
多线程学习第一课
*/


#include <functional>
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

class Foo {
protected:
    std::mutex _mutex1;
    std::mutex _mutex2;
public:
    Foo() {
        _mutex1.lock();
        _mutex2.lock();
    }

    void first(function<void()> printFirst) {
        
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        _mutex1.unlock();
    }

    void second(function<void()> printSecond) {
        std::unique_lock<std::mutex> lock1(_mutex1); //结束自动解锁
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        _mutex2.unlock();
    }

    void third(function<void()> printThird) {
        std::unique_lock<std::mutex> lock2(_mutex2); //结束自动解锁
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};


