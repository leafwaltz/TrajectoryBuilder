#ifndef USERHEADERS_H
#define USERHEADERS_H

#include <QString>
#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QApplication>
#include <QRect>
#include <QMessageBox>

#include <map>
#include <queue>
#include <vector>
#include <memory>
#include <cmath>

#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>
#include <native/task.h>
#include <native/timer.h>

#include "physics.h"

using namespace std;

#define type_task_trajectory_generator  1
#define type_task_command_sender        2
#define type_set_task_command           3
#define type_if_task_command_done       4

typedef struct _tPosCmd
{
    bool    Request;
    bool    Response;
    bool    Done;
    Point2F Position;
    float   Velocity;
    float   Acceleration;
    float   Deceleration;
    float   Jerk;
}_tPosCmd_, *tPosCmd;

typedef struct _tAxisSetpoint
{
    Point2F Position;
    float   Velocity;
}_tAxisSetpoint_,*tAxisSetpoint;

#endif // USERHEADERS_H
