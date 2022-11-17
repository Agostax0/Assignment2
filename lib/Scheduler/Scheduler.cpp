#include "Scheduler.h"
#include "Arduino.h"
#define MAX_TASKS 10

Scheduler::Scheduler(){
}

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
    taskList[0]->tick();
    Serial.println("TASK 0");
}
