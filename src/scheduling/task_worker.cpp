#include <utils_threadpool/scheduling/task_worker.h>

using namespace std;
using namespace utils_threadpool;
using namespace scheduling;

TaskWorker::TaskWorker(TaskQueue::Ptr &task_queue) :
    task_(nullptr),
    task_queue_(task_queue),
    running_(false),
    interruption_requested_(false),
    thread_(bind(&TaskWorker::run, this))
{
}

TaskWorker::~TaskWorker()
{
    thread_.join();
}

void TaskWorker::done()
{
    lock_guard<mutex> l(task_mutex_);
    if(task_ == nullptr)
        return;
    task_->done();
}

void TaskWorker::interrupt()
{
    interruption_requested_ = true;
}

bool TaskWorker::running()
{
    return running_;
}

void TaskWorker::run()
{
    while(true) {
        if(interruption_requested_)
             return;
        Task::Ptr task;
        task_queue_->get(task);
        {
            lock_guard<mutex> l(task_mutex_);
            task_ = task;
        }

        if(task_ == nullptr)
            return;

        running_ = true;
        task_->execute();
        running_ = false;
    }
}
