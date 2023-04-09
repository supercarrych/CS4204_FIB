//
// Created by hc237 on 07/04/23.
//

#ifndef CS4204_FIB_TASK_H
#define CS4204_FIB_TASK_H

class Task {
public:
    Task() = default;
    virtual ~Task() = default;

    virtual void execute() = 0;//needs to be overridden in derived classes
};


#endif //CS4204_FIB_TASK_H
