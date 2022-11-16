#include "Scheduler.h"

#define MAX_TASKS 10

void Scheduler::init()
{
    this->state = NORMAL;
    nTasks = 0;
}

bool Scheduler::addTask(Task *task)
{
    if (nTasks < MAX_TASKS - 1)
    {
        this->taskList[nTasks] = task;
        this->nTasks++;
        return true;
    }
    else
    {
        return false;
    }
}

void Scheduler::schedule()
{
    
}
