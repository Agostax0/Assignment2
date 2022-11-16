#ifndef __SCHEDULER__
#define __SCHEDULER__
#define MAX_TASKS 10

#include "Task.h"

class Scheduler{
    public:
        void init();

        bool addTask(Task *task);

        void schedule();
    private:
        int nTasks;
        Task* taskList[MAX_TASKS];
        int state;
};

#endif