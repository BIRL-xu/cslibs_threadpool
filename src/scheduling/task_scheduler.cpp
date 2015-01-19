#include <utils_threadpool/scheduling/task_scheduler.h>

TaskScheduler::TaskScheduler(const unsigned int threads)
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
    queue_.push(task);
    if(blocking)
        wait();
}

void TaskScheduler::push(const std::vector<Task::Ptr> &tasks,
                         const bool blocking)
{
    queue_.push(tasks);
    if(blocking)
        wait();
}

void TaskScheduler::wait()
{
    queue_.wait();
    for(auto &t : workers_)
        t->done();
}

void TaskScheduler::shutdown()
{
    queue_.clear();
    for(auto &t : workers_) {
        t->done();
//        t->join();
    }

}
