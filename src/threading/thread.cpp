#include <utils_threadpool/threading/thread.h>
#include <utils_threadpool/threading/threadpool.h>


Thread::Thread(ThreadPool &pool,
               const Runnable::Ptr &runnable) :
    threadpool_(pool),
    runnable_(runnable),
    thread_(std::bind(&Thread::run, this))
{
}

void Thread::interrupt()
{

}

void Thread::run()
{
    bool can_run = true;
    do {
        if(interrupt_requested_)
            break;
        can_run = runnable_->run();
    } while(can_run);

    threadpool_.removeThread(this);

    thread_.join();
}
