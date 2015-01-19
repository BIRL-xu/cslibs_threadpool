#ifndef RUNNABLE_H
#define RUNNABLE_H

#include <memory>

class Runnable {
public:
    typedef std::shared_ptr<Runnable> Ptr;
    virtual bool run() = 0;

protected:
    Runnable(){}
    Runnable(const Runnable &other){}

};


#endif // RUNNABLE_H

