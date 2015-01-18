#ifndef TASK_WORKER_THREAD_H
#define TASK_WORKER_THREAD_H

#include "task.h"

class TaskWorker
{
public:
    TaskWorker();

    Task::Ptr getCurrentTask();
    void      onHold();

};

#endif // TASK_WORKER_THREAD_H
