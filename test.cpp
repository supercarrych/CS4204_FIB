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
    if (inputQueue->task_queue.empty()) {
        task.EOS = true;
    }
    while (!task.EOS) {
        task = farm::getTask(*inputQueue);
        result = worker(task.parameter);
        task.result = result;
        printf("Worker %d result is %d.\n",task.id,task.result);
        printf("EOS = %d.\n",task.EOS);
        farm::putTask(*outputQueue, task);
    }

    return nullptr;
}

void fibonacci() {
    farm::Queue inputQueue;
    farm::Queue outputQueue;
    farm::Task task;
    printf("1");
    task.EOS = false;
    std::cout<<task.EOS;
    for (int i = 0; i < 100; i++) {
        task.id = i;
        task.parameter = i;
        farm::putTask(inputQueue, task);
    }

    farm::createFarm(WorkerWrapper, 3,&inputQueue,&outputQueue);

    for (int i = 0; i < 100; i++) {
        task = farm::getTask(outputQueue);
        printf("fib(%d) = ", i);
        std::cout<<task.result<<std::endl;
    }
}


int main() {

    // 获取开始时间点
    auto start = std::chrono::high_resolution_clock::now();
    printf("Begin\n");
    fibonacci();
    printf("End");
    // 获取结束时间点
    auto end = std::chrono::high_resolution_clock::now();

    // 计算经过的时间（以毫秒为单位）
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Execution time: " << duration << " ms" << std::endl;

    return 0;
}
