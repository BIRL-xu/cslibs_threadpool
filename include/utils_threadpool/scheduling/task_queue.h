#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H

#include "task.h"
#include <utils_threadpool/sync/semaphore.h>
#include <thread>
#include <mutex>
#include <memory>
#include <condition_variable>
#include <queue>

class TaskQueue
{
public:
    typedef std::shared_ptr<TaskQueue> Ptr;

    TaskQueue();

    void push(const Task::Ptr &task);
    void push(const std::vector<Task::Ptr> &tasks);

    void get(Task::Ptr &task);

    void clear();
    void wait();
    bool empty();

private:
    std::semaphore          waiting_semaphore_;
    std::mutex              waiting_mutex_;
    std::condition_variable waiting_cv_;
    std::queue<Task::Ptr>   waiting_;
};

#endif // TASK_QUEUE_H
