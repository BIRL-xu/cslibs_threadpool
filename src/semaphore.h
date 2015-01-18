#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <mutex>
#include <condition_variable>

class semaphore
{
public:
    semaphore(const unsigned int count = 0);

    void post();

    void wait();

private:
    std::mutex                  mutex_;
    std::condition_variable     cv_;
    unsigned int count_;
};

#endif // SEMAPHORE_H
