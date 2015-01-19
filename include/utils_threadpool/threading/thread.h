#ifndef THREAD_H
#define THREAD_H

#include <thread>
#include <atomic>
#include <memory>

#include "runnable.h"

class ThreadPool;

class Thread {
public:
    typedef std::shared_ptr<Thread> Ptr;

    Thread(ThreadPool &pool,
           const Runnable::Ptr &runnable);
    virtual ~Thread();

    void interrupt();

    bool isActive();

private:
    ThreadPool      &threadpool_;
    Runnable::Ptr    runnable_;
    std::thread      thread_;
    std::atomic_bool interrupt_requested_;
    std::atomic_bool running_;

    void run();


};


#endif // THREAD_H

