//
// Created by hc237 on 07/04/23.
//

#ifndef CS4204_FIB_FARM_HPP
#define CS4204_FIB_FARM_HPP
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>

class farm {
public:
    typedef struct {
        int id; // worker ID
        int parameter; // The parameter passes to the function
        unsigned short **result;
    } Task;

    typedef struct {
        std::queue<Task> task_queue;
        std::mutex queue_mutex;
        std::condition_variable not_empty_cv;
        bool EOS;
    } Queue;

    static void addTask(Queue &q, Task& task) {
        q.task_queue.push(task);
    }

    static Task removeTask(Queue& q) {
        Task task;
        if (!q.task_queue.empty()) {
            task = q.task_queue.front();
            q.task_queue.pop();
            Task t_copy = task;
            return t_copy;
        } else {
            q.EOS = true;
        }
        return task;
    }

    static void makeThread(void (*Worker)(),void *args) {
        auto *thread = (pthread_t *)malloc(sizeof(pthread_t));

        int rc;

        rc = pthread_create(thread, nullptr, (void *(*)(void *))Worker, args);

        if (rc) {
            printf("error");
            // Handle the error
        } else{
            printf("success create thread %d\n",thread);
        }

    }

    static void createFarm(void (*worker_wrapper)( ), int nw,void *args) {
         for(int n=0; n < nw; n++){
             makeThread(worker_wrapper,args);
         }

     }

    static void putTask(Queue& q, Task& t) {
        //
        std::unique_lock<std::mutex> lock(q.queue_mutex);
        addTask(q, t);
        q.not_empty_cv.notify_one(); // Notify a waiting thread that the queue is not empty
    }

    static Task getTask(Queue &q) {
        Task t;
        std::unique_lock<std::mutex> lock(q.queue_mutex);
        q.not_empty_cv.wait(lock, [&q]() { return !q.task_queue.empty(); }); // Wait until the queue is not empty
        t = removeTask(q);
        return t;
    }

};


#endif //CS4204_FIB_FARM_HPP