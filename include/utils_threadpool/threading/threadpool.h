#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "runnable.h"
#include "thread.h"
#include <thread>
#include <mutex>
#include <vector>

class ThreadPool
{
    friend class Thread;

public:
    ThreadPool();

    unsigned int activeThreads();

    void add(const Runnable::Ptr &runnable);

    void shutdown();

private:
    std::mutex  mutex_;
    std::vector<Thread::Ptr> threads_;

    void updateThreadList();
};

#endif // THREADPOOL_H
