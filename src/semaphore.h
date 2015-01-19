#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <mutex>
#include <condition_variable>

namespace std {

class semaphore
{
public:
    semaphore(const unsigned int count = 0);

    void post();
    void wait();
    void release_all();

private:
    std::mutex                  mutex_;
    std::condition_variable     cv_;
    unsigned int                count_;
    bool                        release_request_;
};
}

#endif // SEMAPHORE_H
