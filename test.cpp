//
// Created by hc237 on 07/04/23.
//


#include <chrono>
#include <cstdio>
#include <iostream>
#include "fibonacci/fibonacci.h"
#include "Farm/farm.hpp"


int worker(int i) {
    int res;
    res = payload1(i);
    payload2(res);
    return res;
}

static void WorkerWrapper(farm::Queue inputQueue, farm::Queue outputQueue) {
    farm::Task task;
    int result;
    if (inputQueue.task_queue.empty()) {
        task.EOS = true;
    }
    while (!task.EOS) {
        task = farm::getTask(inputQueue);
        result = worker(task.parameter);
        farm::putTask(outputQueue, reinterpret_cast<farm::Task &>(result));
    }

}

void fibonacci() {
    farm::Queue inputQueue;
    farm::Queue outputQueue;
    farm::Task task;
    printf("1");
    task.EOS = false;
    printf("%s", reinterpret_cast<const char *>(task.EOS));
    for (int i = 0; i < 100; i++) {
        task.id = i;
        task.parameter = i;
        farm::putTask(inputQueue, task);
//        res = payload1(i);
//        payload2(res);

    }

    farm::createFarm(reinterpret_cast<void *(*)(void *)>(WorkerWrapper), 4);

    for (int i = 0; i < 100; i++) {
        task = farm::getTask(outputQueue);
        printf("fib(%d) = % d\n", i, task.id);
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
