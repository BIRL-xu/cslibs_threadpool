#ifndef TASK_SCHEDULER_H
#define TASK_SCHEDULER_H

#include <thread>

#include "task_queue.h"
#include "task_worker.h"

class TaskScheduler
{
public:
    TaskScheduler(const unsigned int threads = 2);

    void wait();

private:
    TaskQueue   queue_;

    std::vector<TaskWorker> workers_;

};

#endif // TASK_SCHEDULER_H
