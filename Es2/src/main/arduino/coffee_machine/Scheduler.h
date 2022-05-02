#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.h"
#define MAX_TASKS 10

class Scheduler {

 int basePeriod;
 int nTasks;
 Task* taskList[MAX_TASKS];
 
public:
 void init(int basePeriod);
 virtual bool addTask(Task* task);
 virtual void schedule();

};
#endif
