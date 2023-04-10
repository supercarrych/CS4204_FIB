//
// Created by hc237 on 07/04/23.
//

#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include <queue>
#include <memory>
#include <mutex>
#include "farm.hpp"




typedef struct {
    int id;                         // worker ID
    void (*worker_function)();  // worker function to execute
} worker_data_t;

void *worker_function(void *arg) {
    auto *data = (worker_data_t *)arg;
    printf("Worker %d is running.\n", data->id);

    // Execute the user-defined function
    data->worker_function();

    return NULL;
}



void farm(int num_workers, void (*worker_func)()) {
    pthread_t *threads = (pthread_t *)malloc(num_workers * sizeof(pthread_t));
    worker_data_t *worker_data = (worker_data_t *)malloc(num_workers * sizeof(worker_data_t));

    for (int i = 0; i < num_workers; i++) {
        worker_data[i].id = i;
        worker_data[i].worker_function = worker_func;

        if (pthread_create(&threads[i], NULL, worker_function, (void *)&worker_data[i]) != 0) {
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < num_workers; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            exit(EXIT_FAILURE);
        }
    }

    free(threads);
    free(worker_data);
}




