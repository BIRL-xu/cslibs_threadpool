#include <utils_threadpool/threading/threadpool.h>

using namespace std;

ThreadPool::ThreadPool()
{
}

unsigned int ThreadPool::activeThreads()
{
    lock_guard<mutex> l(mutex_);
    return threads_.size();
}

void ThreadPool::add(const Runnable::Ptr &runnable)
{
    lock_guard<mutex> l(mutex_);
    Thread::Ptr thread(new Thread(*this, runnable));
    threads_.push_back(thread);
}

void ThreadPool::shutdown()
{
    lock_guard<mutex> l(mutex_);
    for(auto t : threads_)
        t->interrupt();
}

void ThreadPool::removeThread(const Thread *thread)
{
    lock_guard<mutex> l(mutex_);

    auto it = threads_.begin();
    for(; it != threads_.end(); ++it) {
        if(it->get() == thread)
            break;
    }

    if(it != threads_.end()) {
        threads_.erase(it);
    }
}
