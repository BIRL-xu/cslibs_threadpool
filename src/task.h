#ifndef TASK_H
#define TASK_H

#include <memory>

class Task
{
public:
    typedef std::shared_ptr<Task> Ptr;

    Task();

    void done();
};

#endif // TASK_H
