#include <utils_threadpool/sync/semaphore.h>

using namespace std;

semaphore::semaphore(const unsigned int count) :
    count_(count),
    release_request_(false)
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
    while(count_ == 0) {
        cv_.wait(l);
        if(release_request_)
            return;
    }
    --count_;
}

void semaphore::release_all()
{
    release_request_ = true;
    cv_.notify_all();
}
