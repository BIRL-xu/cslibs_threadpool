#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <deque>
#include <vector>


namespace utils_boost_general {
namespace threadpool {

template<typename T>
class Queue {
public:
    Queue(const unsigned int worker_threads) :
        semaphore_(0),
        waiting_threads_(0),
        process_q_(true),
        worker_threads_(worker_threads)
    {
    }

    void push(const T &item)
    {
        synchro::Lock lock(mutex_items_);
        items_.push_back(item);
        semaphore_.post();
    }

    void push(const std::vector<T> &items)
    {
        synchro::Lock lock(mutex_items_);
        items_.insert(items_.end(), items.begin(), items.end());
        post(items.size());
    }

    void push(const std::deque<T> &items)
    {
        synchro::Lock lock(mutex_items_);
        items_.insert(items_.end(), items.begin(), items.end());
        post(items.size());
    }

    bool pop(T &item)
    {
        {
            synchro::Lock lock(mutex_waiting_);
            ++waiting_threads_;
        }

        semaphore_.wait();

        {
            synchro::Lock lock(mutex_waiting_);
            --waiting_threads_;
        }


        if(!process_q_)
            return false;

        {
            synchro::Lock lock(mutex_items_);
            if(items_.empty())
                return false;

            item = items_.front();
            items_.pop_front();
        }
        return true;
    }

    void cancel()
    {
        {
            synchro::Lock lock(mutex_waiting_);
            if(worker_threads_ == waiting_threads_)
                return;
        }

        items_.clear();
//        process_q_ = false;
//        post(waiting_threads_);
    }

    bool empty()
    {
        synchro::Lock lock(mutex_items_);
        return items_.empty();
    }

    bool pausing()
    {
        synchro::Lock lock(mutex_waiting_);
        return waiting_threads_ == worker_threads_;
    }


private:
    synchro::Semaphore      semaphore_;
    synchro::Mutex          mutex_items_;

    bool                    process_q_;
    unsigned int            worker_threads_;
    unsigned int            waiting_threads_;
    synchro::Mutex          mutex_waiting_;

    std::deque<T>           items_;

    inline void post(const unsigned int posts)
    {
        for(unsigned int i = 0 ; i < posts ; ++i)
            semaphore_.post();
    }
};
}
}
#endif // QUEUE_HPP
