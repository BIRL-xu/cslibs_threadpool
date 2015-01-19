#include <utils_threadpool/threading/threadpool.h>

#include <chrono>
#include <thread>
#include <iostream>

struct Increment : public Runnable {
    int count;

    Increment() :
        count(0)
    {
    }

    bool run() {
        if(count > 10)
            return false;
        std::chrono::milliseconds dura( 500 );
        std::this_thread::sleep_for( dura );
        ++count;
        return true;
    }

};

int main(int argc, char *argv[])
{
    ThreadPool pool;



    for(unsigned int i = 0 ; i < 10 ; ++i) {
        Runnable::Ptr run(new Increment);
        pool.add(run);
        std::chrono::milliseconds dura( 250 );
        std::this_thread::sleep_for( dura );
        std::cout << "Active Threads " << pool.activeThreads() << std::endl;
    }

    while(pool.activeThreads() > 0) {
        std::chrono::milliseconds dura( 250 );
        std::this_thread::sleep_for( dura );
        std::cout << pool.activeThreads() << std::endl;
    }

    std::cout << "Done all!" << std::endl;

    return 0;
}

