#ifndef TASK_SCHEDULER_H
#define TASK_SCHEDULER_H

#include <thread>
#include <memory>

#include <cslibs_threadpool/scheduling/task_queue.h>
#include <cslibs_threadpool/scheduling/task_worker.h>

namespace cslibs_threadpool {
namespace scheduling {
class TaskScheduler
{
public:
    using Ptr = std::shared_ptr<TaskScheduler>;

    TaskScheduler(const unsigned int threads = 2);
    virtual ~TaskScheduler();

    void push(const Task::Ptr &task,
              const bool blocking = false);
    void push(const std::vector<Task::Ptr> &tasks,
              const bool blocking = false);

    bool running();

    void wait();

    void shutdown();

    void restart(const unsigned int threads);

private:
    TaskQueue::Ptr               queue_;

    std::vector<TaskWorker::Ptr> workers_;

};
}
}

#endif // TASK_SCHEDULER_H
