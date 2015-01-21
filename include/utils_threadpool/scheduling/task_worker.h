#ifndef TASK_WORKER_THREAD_H
#define TASK_WORKER_THREAD_H

#include "task.h"
#include "task_queue.h"

#include <thread>
#include <future>
#include <mutex>
#include <atomic>

namespace utils_threadpool {
namespace scheduling {
class TaskWorker
{
public:
    typedef std::shared_ptr<TaskWorker> Ptr;

    TaskWorker(TaskQueue::Ptr &task_queue);
    virtual ~TaskWorker();

    void      done();
    void      interrupt();
    bool      running();

private:
    std::mutex       task_mutex_;
    Task::Ptr        task_;
    TaskQueue::Ptr   task_queue_;

    std::atomic_bool running_;
    std::atomic_bool interruption_requested_;
    std::thread      thread_;

    void run();

};
}
}

#endif // TASK_WORKER_THREAD_H
