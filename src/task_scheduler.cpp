#include "task_scheduler.h"

TaskScheduler::TaskScheduler(const unsigned int threads)
{
}

void TaskScheduler::wait()
{
    queue_.wait();
    for(auto t : workers_)
        t.onHold();
}
