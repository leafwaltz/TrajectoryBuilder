#include "task.h"

Task::Task(const char *taskname, int prior, int stacksize, int mode)
{
    m_taskname = taskname;
    m_stacksize = stacksize;
    m_priority = prior;
    m_mode = stacksize;

    rt_task_create(&m_rttask,taskname,stacksize,prior,mode);
}

Task::~Task()
{

}

bool Task::StartTask()
{
    if(m_rttask_func)
    {
        rt_task_start(&m_rttask,m_rttask_func,NULL);
        return true;
    }
    else return false;
}

void Task::DeleteTask()
{
    rt_task_delete(&m_rttask);
    delete this;
}

int Task::GetPriority() const
{
    return m_priority;
}

QString Task::GetTaskName() const
{
    return m_taskname;
}

Task& Task::operator +=(const RT_TASK_FUNC rttask_func)
{
    m_rttask_func = rttask_func;
    return *this;
}
