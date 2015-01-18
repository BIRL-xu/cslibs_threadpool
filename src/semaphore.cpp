#include "semaphore.h"

using namespace std;

semaphore::semaphore(const unsigned int count) :
    count_(count)
{
}

void semaphore::post()
{
    unique_lock<mutex> l(mutex_);
    ++count_;
    cv_.notify_one();
}

void semaphore::wait()
{
    unique_lock<mutex> l(mutex_);
    while(count_ == 0)
        cv_.wait(l);
    --count_;
}
