//
// Created by hc237 on 07/04/23.
//

#ifndef CS4204_FIB_FARM_HPP
#define CS4204_FIB_FARM_HPP
#include <iostream>
#include <queue>
#include <mutex>
class farm {
public:
    typedef struct {
        int id; // worker ID
        int parameter; // The parameter passes to the function
        bool EOS;
    } Task;

    typedef struct {
        std::queue<Task> task_queue;
        std::mutex mtx;
    } Queue;

    static void lockQueue(Queue &q) {
        q.mtx.lock();
    }

    static void unlockQueue(Queue &q) {
        q.mtx.unlock();
    }

    static void addTask(Queue &q, Task& task) {
        q.task_queue.push(task);
    }


    static Task removeTask(Queue& q) {
        Task task = q.task_queue.front();
        q.task_queue.pop();
        return task;
    }


    static void makeThread(void *(*Worker)(void *)) {
        auto *threads = (pthread_t *)malloc(sizeof(pthread_t));

        int rc;

        rc = pthread_create(threads, nullptr, Worker, nullptr);

        if (rc) {
            // Handle the error
        }


    }

    static void createFarm(void *(*worker_wrapper)(void *), int nw) {

         for(int n=0; n < nw; n++){
             makeThread(worker_wrapper);
         }

     }




    static void putTask(Queue& q, Task& t) {
        lockQueue(q);
        addTask(q, t);
        unlockQueue(q);
    }
    static Task getTask(Queue &q) {
        Task t;
        lockQueue(q);
        t = removeTask(q);
        unlockQueue(q);
        return t;
    }

    static void farmPattern(int num_workers, void (*worker_func)()){

    }
};


#endif //CS4204_FIB_FARM_HPP
