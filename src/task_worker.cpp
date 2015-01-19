#include "task_worker.h"

using namespace std;

TaskWorker::TaskWorker(TaskQueue &task_queue) :
    task_(nullptr),
    task_queue_(task_queue),
    interruption_request_(false),
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
    lock_guard<mutex> l(interruption_mutex_);
    interruption_request_ = true;
}

void TaskWorker::join()
{
    thread_.join();
    lock_guard<mutex> l(task_mutex_);
    task_ = nullptr;
}

void TaskWorker::run()
{
    while(true) {
        {
            lock_guard<mutex> l(interruption_mutex_);
            if(interruption_request_)
                return;
        }
        Task::Ptr task;
        task_queue_.get(task);
        {
            lock_guard<mutex> l(task_mutex_);
            task_ = task;
        }

        if(task_ == nullptr)
            return;

        task_->execute();
    }
}
