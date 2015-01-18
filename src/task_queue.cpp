#include "task_queue.h"

using namespace std;

TaskQueue::TaskQueue()
{
}

void TaskQueue::push(const Task::Ptr &task)
{
    lock_guard<mutex> l(waiting_mutex_);
    waiting_.push(task);
}

void TaskQueue::push(const std::vector<Task::Ptr> &tasks)
{
    lock_guard<mutex> l(waiting_mutex_);
    for(auto it = tasks.begin() ;
        it != tasks.end() ;
        ++it)
        waiting_.push(*it);
}

void TaskQueue::get(Task::Ptr &task)
{
    lock_guard<mutex> l(waiting_mutex_);
    task = waiting_.front();
    waiting_.pop();
    waiting_cv_.notify_one();
}

void TaskQueue::cancel()
{
    lock_guard<mutex> l(waiting_mutex_);
    while(!waiting_.empty())
        waiting_.pop();
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
