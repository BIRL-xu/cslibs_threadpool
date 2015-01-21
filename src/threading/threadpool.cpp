#include <utils_threadpool/threading/threadpool.h>

using namespace std;
using namespace utils_threadpool;
using namespace threading;

ThreadPool::ThreadPool()
{
}

unsigned int ThreadPool::activeThreads()
{
    updateThreadList();
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

void ThreadPool::updateThreadList()
{
    lock_guard<mutex> l(mutex_);
    std::vector<Thread::Ptr> active_threads;
    for(auto t : threads_) {
        if(t->isActive())
            active_threads.push_back(t);
    }
    threads_.clear();
    std::swap(active_threads, threads_);
}
