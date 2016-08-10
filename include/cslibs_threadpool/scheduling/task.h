#ifndef TASK_H
#define TASK_H

#include <memory>
#include <future>
#include <functional>

namespace cslibs_threadpool {
namespace scheduling {
class Task
{
public:
    typedef std::shared_ptr<Task> Ptr;

    Task(std::function<void()> &todo);

    void append(const Task::Ptr &task);
    void execute();
    void done();

private:
    std::packaged_task<void()> pt_;
    std::future<void>          ft_;

    Task::Ptr appendix_;

};
}
}

#endif // TASK_H
