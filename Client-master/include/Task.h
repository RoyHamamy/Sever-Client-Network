//
// Created by rolantas@wincs.cs.bgu.ac.il on 02/01/2022.
//
#ifndef TASK_H
#define TASK_H
#include <iostream>
#include <mutex>
#include <thread>
#include <utility>
#include <condition_variable>
#include "connectionHandler.h"

class Task{
private:
    ConnectionHandler *_handler;
    std::condition_variable cv;
public:
    std::condition_variable &getCv();
    Task (ConnectionHandler* handler);
    Task& operator=(const Task&);
    Task(const Task& other);
    void run();
};


#endif
