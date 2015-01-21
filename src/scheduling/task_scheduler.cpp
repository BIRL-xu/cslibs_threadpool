#include <utils_threadpool/scheduling/task_scheduler.h>

using namespace utils_threadpool;
using namespace scheduling;

TaskScheduler::TaskScheduler(const unsigned int threads) :
    queue_(new TaskQueue)
{
    for(unsigned int i = 0 ; i < threads ; ++i) {
        workers_.push_back(TaskWorker::Ptr(new TaskWorker(queue_)));
    }
}

TaskScheduler::~TaskScheduler()
{
}

void TaskScheduler::push(const Task::Ptr &task,
                         const bool blocking)
{
    queue_->push(task);
    if(blocking)
        wait();
}

void TaskScheduler::push(const std::vector<Task::Ptr> &tasks,
                         const bool blocking)
{
    queue_->push(tasks);
    if(blocking)
        wait();
}

bool TaskScheduler::running()
{
    bool running = !queue_->empty();
    for(auto &t : workers_)
        running |= t->running();
    return running;
}

void TaskScheduler::wait()
{
    queue_->wait();
    for(auto &t : workers_)
        t->done();
}

void TaskScheduler::shutdown()
{
    queue_->clear();
    for(auto &t : workers_) {
        t->done();
    }
    workers_.clear();
}

void TaskScheduler::restart(const unsigned int threads)
{
    queue_.reset(new TaskQueue);
    for(unsigned int i = 0 ; i < threads ; ++i) {
        workers_.push_back(TaskWorker::Ptr(new TaskWorker(queue_)));
    }
}
