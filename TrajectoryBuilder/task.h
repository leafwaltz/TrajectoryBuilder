#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "userheaders.h"

class Task
{

public:

    typedef void(*RT_TASK_FUNC)(void*);

    Task(const char* taskname, int prior, int stacksize = 0, int mode = 0);

    ~Task();

    bool StartTask();

    void DeleteTask();

    int GetPriority() const;

    QString GetTaskName() const;

    Task& operator +=(const RT_TASK_FUNC rttask_func);

private:

    RT_TASK_FUNC m_rttask_func;

    RT_TASK m_rttask;

    QString m_taskname;

    int m_stacksize;

    int m_priority;

    int m_mode;

};


#endif // TASKMANAGER_H
