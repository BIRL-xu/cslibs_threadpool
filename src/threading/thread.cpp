#include <utils_threadpool/threading/thread.h>
#include <utils_threadpool/threading/threadpool.h>

using namespace utils_threadpool;
using namespace threading;

Thread::Thread(ThreadPool &pool,
               const Runnable::Ptr &runnable) :
    threadpool_(pool),
    runnable_(runnable),
    thread_(std::bind(&Thread::run, this)),
    interrupt_requested_(false),
    running_(true)
{
}

Thread::~Thread()
{
    if(thread_.joinable())
        thread_.join();
}

bool Thread::isActive()
{
    return running_;
}

void Thread::interrupt()
{
    interrupt_requested_ = true;
}

void Thread::run()
{
    bool can_run = true;
    do {
        if(interrupt_requested_)
            break;
        can_run = runnable_->run();
    } while(can_run);

    running_ = false;
}
