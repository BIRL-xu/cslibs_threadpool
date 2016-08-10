#include <cslibs_threadpool/scheduling/task_scheduler.h>

#include <iostream>

using namespace cslibs_threadpool;
using namespace scheduling;

std::mutex cnt_lock;
int cnt = 0;

void increment()
{
    std::lock_guard<std::mutex> l(cnt_lock);
    ++cnt;
    std::cout << std::this_thread::get_id() << " " << cnt << std::endl;
}



int main(int argc, char *argv[])
{
    TaskScheduler ts(4);
    auto f = std::function<void()>(increment);
    for(auto i = 0 ; i < 5000000 ; ++i)
    {
        Task::Ptr task(new Task(f));
        ts.push(task);
    }
    ts.shutdown();
    ts.wait();
    ts.shutdown();

    return 0;
}
