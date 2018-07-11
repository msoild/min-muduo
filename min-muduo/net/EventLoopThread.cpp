#include "EventLoopThread.h"
#include "EventLoop.h"
#include <functional>
#include <assert.h>

EventLoopThread::EventLoopThread() 
    : loop_(nullptr),
      exiting_(false),
      mutex_(),
      cond_()
{
   
}

EventLoopThread::~EventLoopThread() {
    exiting_ = true;
    loop_->quit();
    thread_.join();
}



EventLoop* EventLoopThread::startLoop() {
    assert(!thread_.joinable()); 
    thread_ = std::move(std::thread(std::bind(&EventLoopThread::threadFunc, this)) ); 
    
    {
        std::unique_lock<std::mutex> locker(mutex_);
        while(loop_ == NULL) {
            cond_.wait(locker); //Who notice?
        }
    }

    return loop_;
}

void EventLoopThread::threadFunc() { 
    EventLoop loop;
    {
        std::unique_lock<std::mutex> locker(mutex_);
        loop_ = &loop;
        cond_.notify_one();
    }
    loop.loop();

    assert(exiting_); //
    loop_ = NULL;
}
