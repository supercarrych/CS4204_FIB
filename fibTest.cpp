//
// Created by hc237 on 07/04/23.
//
#include <chrono>
#include <cstdio>
#include <iostream>
#include "Farm/farm.hpp"
#include "fibonacci/fibonacci.h"

int worker(int i) {
    printf("Worker %d is running.\n",i);
    int res;
    res = payload1(i);
    payload2(res);
    return res;
}

void *WorkerWrapper(void *args) {
    // Assuming your farm::Queue and farm::Task are defined, adjust the names if needed
    farm::Queue *inputQueue = ((farm::Queue **)args)[0];
    farm::Queue *outputQueue = ((farm::Queue **)args)[1];
    farm::Task task;
    int result;


    while (!inputQueue->EOS) {
        task = farm::getTask(*inputQueue);
        if (inputQueue->task_queue.empty()) {
            inputQueue->EOS = true;
        }
        result = worker(task.parameter);
        task.result = result;
        farm::putTask(*outputQueue, task);
    }

    pthread_exit(nullptr);
}

void fibonacci() {
    farm::Queue inputQueue;
    farm::Queue outputQueue;
    farm::Task task;

    inputQueue.EOS = false;

    for (int i = 0; i < 100; i++) {
        task.id = i;
        task.parameter = i;
        farm::putTask(inputQueue, task);
    }

    farm::Queue *args[] = {&inputQueue, &outputQueue};

    printf("create thread\n");
    farm::createFarm(reinterpret_cast<void (*)()>(WorkerWrapper), 4, args);

    std::cout<<inputQueue.EOS;

    for (int i = 0; i < 100; i++) {
        task = farm::getTask(outputQueue);
        printf("fib(%d) = ", i);
        std::cout<<task.result<<std::endl;
    }

}


//int main() {
//
//    // 获取开始时间点
//    auto start = std::chrono::high_resolution_clock::now();
//    printf("Begin\n");
//    fibonacci();
//    printf("End");
//    // 获取结束时间点
//    auto end = std::chrono::high_resolution_clock::now();
//
//    // 计算经过的时间（以毫秒为单位）
//    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//    std::cout << "Execution time: " << duration << " ms" << std::endl;
//
//    return 0;
//}
