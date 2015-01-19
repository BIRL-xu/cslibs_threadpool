#include <utils_threadpool/scheduling/task.h>

#include <chrono>
#include <thread>

Task::Task(std::function<void()> &todo) :
    appendix_(nullptr)
{
    pt_ = std::packaged_task<void()>(todo);
    ft_ = pt_.get_future();
}
void Task::append(const Task::Ptr &task)
{
    if(appendix_ == nullptr)
        appendix_ = task;
    else
        appendix_->append(task);
}

void Task::execute()
{
    pt_();

    if(appendix_ != nullptr)
        appendix_->execute();

}

void Task::done()
{
    ft_.wait();
    if(appendix_ != nullptr)
        appendix_->done();
}
