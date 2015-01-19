#ifndef TASK_SCHEDULER_H
#define TASK_SCHEDULER_H

#include <thread>

#include "task_queue.h"
#include "task_worker.h"

class TaskScheduler
{
public:
    TaskScheduler(const unsigned int threads = 2);
    virtual ~TaskScheduler();

    void push(const Task::Ptr &task,
              const bool blocking = false);
    void push(const std::vector<Task::Ptr> &tasks,
              const bool blocking = false);

    void wait();

    void shutdown();

private:
    TaskQueue   queue_;

    std::vector<TaskWorker::Ptr> workers_;

};

#endif // TASK_SCHEDULER_H