/*
多线程学习 不用条件变量的另一种解法
*/


#include <functional>
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

void printNumber(int x)
{
    cout << x;
}

class ZeroEvenOdd {
private:
    int n;

    std::mutex _mutex0;
    std::mutex _mutex1;
    std::mutex _mutex2;
    int print_n=1;

public:
    ZeroEvenOdd(int n) {
        this->n = n;
        _mutex1.lock();
        _mutex2.lock();
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        while(1)
        {
            _mutex0.lock();
            if(this->print_n > this->n)
                break;
            printNumber(0);
            if(this->print_n %2 == 1)
            {
                _mutex1.unlock();
            }
            else
            {
                _mutex2.unlock();
            }
        }
        _mutex1.unlock();
        _mutex2.unlock();
        
    }

    void even(function<void(int)> printNumber) {
        while(1)
        {
            _mutex2.lock();
            if(this->print_n > this->n)
                break;
            int num = this->print_n;
            printNumber( num );
            //cout<<this->print_n;
            this->print_n ++;
            _mutex0.unlock();
        }
    }

    void odd(function<void(int)> printNumber) {
        
        while(1)
        {
            _mutex1.lock();
            if(this->print_n > this->n)
                break;
            int num = this->print_n;
            printNumber( num );
            //cout<<this->print_n;
            this->print_n ++;
            _mutex0.unlock();
        }
    }
};



int main(int argc, char const *argv[])
{
    ZeroEvenOdd method(9);
    function<void(int)> func = printNumber;
    std::thread th1(ZeroEvenOdd::zero, &method, func);
    std::thread th2(ZeroEvenOdd::odd, &method, func);
    std::thread th3(ZeroEvenOdd::even, &method, func);

    th1.join();
    th2.join();
    th3.join();

    return 0;
}











