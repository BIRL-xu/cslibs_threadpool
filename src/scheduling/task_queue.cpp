#include <utils_threadpool/scheduling/task_queue.h>

using namespace std;

TaskQueue::TaskQueue()
{
}

void TaskQueue::push(const Task::Ptr &task)
{
    lock_guard<mutex> l(waiting_mutex_);
    waiting_.push(task);
    waiting_semaphore_.post();
}

void TaskQueue::push(const std::vector<Task::Ptr> &tasks)
{
    lock_guard<mutex> l(waiting_mutex_);
    for(auto it = tasks.begin() ;
        it != tasks.end() ;
        ++it)
        waiting_.push(*it);
    waiting_semaphore_.post();
}

void TaskQueue::get(Task::Ptr &task)
{
    waiting_semaphore_.wait();
    {
        lock_guard<mutex> l(waiting_mutex_);

        if(waiting_.empty()) {
            task = nullptr;
            return;
        }

        task = waiting_.front();
        waiting_.pop();
        waiting_cv_.notify_all();
    }
}

void TaskQueue::clear()
{
    lock_guard<mutex> l(waiting_mutex_);
    while(!waiting_.empty())
       waiting_.pop();
    waiting_semaphore_.release_all();
}

void TaskQueue::wait()
{
    unique_lock<mutex> l(waiting_mutex_);
    while(!waiting_.empty())
        waiting_cv_.wait(l);
}

bool TaskQueue::empty()
{
    lock_guard<mutex> l(waiting_mutex_);
    return waiting_.empty();
}
