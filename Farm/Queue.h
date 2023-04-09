//
// Created by hc237 on 07/04/23.
//

#ifndef CS4204_FIB_QUEUE_H
#define CS4204_FIB_QUEUE_H
#include <queue>
#include <mutex>
#include <condition_variable>

typedef struct  {
    void* func;      // The function pointer
    void* parameter; // The parameter passes to the function
} Task;

class Queue {
private:
    std::queue<std::shared_ptr<Task>> task_queue;
    std::mutex mtx;


public:
    Queue() = default;

    void addTask(const std::shared_ptr<Task>& task) {
        task_queue.push(task);
    }

    std::shared_ptr<Task> removeTask() {
        if (task_queue.empty()) {
            return nullptr;
        }
        auto task = task_queue.front();
        task_queue.pop();
        return task;
    }

     void lockQueue() {
        mtx.lock();
    }

    void unlockQueue() {
        mtx.unlock();
    }
};

#endif //CS4204_FIB_QUEUE_H
