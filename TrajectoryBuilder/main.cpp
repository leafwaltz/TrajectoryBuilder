#include "guimanager.h"

//Global variables

Task task_trajectory_generator("task_trajectory_generator",98,0,0);
Task task_command_sender("task_command_sender",99,0,0);

//tPosCmd new_cmd = (tPosCmd)malloc(sizeof(_tPosCmd_));
//tAxisSetpoint axis1_setpoint = (tAxisSetpoint)malloc(sizeof(_tAxisSetpoint_));

int cycle_count = 0;

void task_trajectory_generator_proc(void *arg)
{
    rt_task_set_periodic(NULL, TM_NOW, 100000000);

    tAxisSetpoint axis1_setpoint = new _tAxisSetpoint_;

    axis1_setpoint->Position = {0,0};
    axis1_setpoint->Velocity = 0;

    Message msg;
    Point2F currentPosition = {0.0,0.0};
    //tPosCmd new_cmd = new _tPosCmd_;

    while (1)
    {
        rt_task_wait_period(NULL);

        Message cmd = Messenger::GetInstance()->ReceiveMessage(type_task_command_sender);

        if(cmd.type == type_task_command_sender)
        {
            tPosCmd new_cmd = (tPosCmd)cmd.message;

            if(new_cmd->Request)
            {
                //int count=50;
                Velocity    maxVelocity;
                Velocity    currentVelocity;
                Velocity    lastVelocity;
                Point2F     targetPosition;
                Vec2F       currentDirection;
                float       acceleration;
                float       dcceleration;
                float       distance;
                float       secondCounter;
                float       move_x;
                float       move_y;

                move_x = 0;
                move_y = 0;
                secondCounter = 0;
                targetPosition = new_cmd->Position;
                acceleration = new_cmd->Acceleration;
                dcceleration = new_cmd->Deceleration;
                maxVelocity.velocityValue = new_cmd->Velocity;
                currentVelocity.velocityValue = 0;
                lastVelocity.velocityValue = 0;
                distance = PointDistance(targetPosition,currentPosition);
                currentDirection.i = (targetPosition.x-currentPosition.x)/distance;
                currentDirection.j = (targetPosition.y-currentPosition.y)/distance;
                maxVelocity.direction = currentDirection;
                currentVelocity.direction = currentDirection;
                lastVelocity.direction = currentDirection;

                float t = distance/maxVelocity.velocityValue
                                 + maxVelocity.velocityValue/(2*acceleration)
                                 + maxVelocity.velocityValue/(2*dcceleration);
                float t1 = maxVelocity.velocityValue/acceleration;
                float t2 = t- maxVelocity.velocityValue/dcceleration;
                float period = 0.1;

                while(secondCounter<=t)
                {
                    rt_task_wait_period(NULL);

                    secondCounter+=period;

                    new_cmd->Response = true;

                    if(secondCounter<=t1)
                    {
                        currentVelocity.velocityValue+=period*acceleration;

                        if(currentVelocity.velocityValue>maxVelocity.velocityValue)
                        {

                            currentVelocity.velocityValue = maxVelocity.velocityValue;

                            move_x = (currentVelocity.velocityValue*currentVelocity.velocityValue
                                                 - lastVelocity.velocityValue*lastVelocity.velocityValue)
                                                /(2*acceleration)*currentDirection.i;
                            move_y = (currentVelocity.velocityValue*currentVelocity.velocityValue
                                                 - lastVelocity.velocityValue*lastVelocity.velocityValue)
                                                /(2*acceleration)*currentDirection.j;

                            currentPosition.x+=move_x;
                            currentPosition.y+=move_y;

                            float delta_t = (currentVelocity.velocityValue-lastVelocity.velocityValue)/acceleration;

                            move_x = maxVelocity.velocityValue*delta_t*currentDirection.i;
                            move_x = maxVelocity.velocityValue*delta_t*currentDirection.j;

                            currentPosition.x+=move_x;
                            currentPosition.y+=move_y;
                        }
                        else
                        {
                            move_x = (currentVelocity.velocityValue*currentVelocity.velocityValue
                                                 - lastVelocity.velocityValue*lastVelocity.velocityValue)
                                                /(2*acceleration)*currentDirection.i;
                            move_y = (currentVelocity.velocityValue*currentVelocity.velocityValue
                                                 - lastVelocity.velocityValue*lastVelocity.velocityValue)
                                                /(2*acceleration)*currentDirection.j;

                            currentPosition.x+=move_x;
                            currentPosition.y+=move_y;
                        }
                    }
                    else if(secondCounter<=t2)
                    {
                        currentVelocity.velocityValue = maxVelocity.velocityValue;

                        move_x = period*currentVelocity.velocityValue*currentDirection.i;
                        move_y = period*currentVelocity.velocityValue*currentDirection.j;

                        currentPosition.x+=move_x;
                        currentPosition.y+=move_y;
                    }
                    else
                    {
                        currentVelocity.velocityValue-=period*dcceleration;

                        if(currentVelocity.velocityValue<0)
                        {
                            float delta_t = (0-currentVelocity.velocityValue)/dcceleration;

                            move_x = 0.5*(period-delta_t)*lastVelocity.velocityValue*currentDirection.i;
                            move_y = 0.5*(period-delta_t)*lastVelocity.velocityValue*currentDirection.j;

                            currentPosition.x+=move_x;
                            currentPosition.y+=move_y;
                        }
                        else
                        {
                            move_x = (lastVelocity.velocityValue*lastVelocity.velocityValue
                                    -currentVelocity.velocityValue*currentVelocity.velocityValue)
                                    /(2*dcceleration)*currentDirection.i;
                            move_y = (lastVelocity.velocityValue*lastVelocity.velocityValue
                                    -currentVelocity.velocityValue*currentVelocity.velocityValue)
                                    /(2*dcceleration)*currentDirection.j;

                            currentPosition.x+=move_x;
                            currentPosition.y+=move_y;
                        }
                    }

                    axis1_setpoint->Position = currentPosition;
                    axis1_setpoint->Velocity = currentVelocity.velocityValue;
                    lastVelocity.velocityValue = currentVelocity.velocityValue;

                    if(currentVelocity.velocityValue>=0)
                    {
                        msg.type = type_task_trajectory_generator;
                        msg.message = axis1_setpoint;
                        Messenger::GetInstance()->PostMessage(msg);
                    }

                    new_cmd->Done = true;
                }
                secondCounter = 0;
                //msg.type = type_if_task_command_done;
                //msg.message = &(new_cmd->Done);
                //Messenger::GetInstance()->PostMessage(msg);
            }
            delete new_cmd;
        }
    }
}

void task_command_sender_proc(void *arg)
{
    rt_task_set_periodic(NULL, TM_NOW, 2000000000);

    while (1)
    {
        rt_task_wait_period(NULL);

        Message cmd = Messenger::GetInstance()->ReceiveMessage(type_set_task_command);

        if(cmd.type == type_set_task_command)
        {
            tPosCmd new_cmd = new _tPosCmd_;
            /*
             * Arguments: &task (NULL=self),
             *            start time,
             *            period (here: 2 s)
             */
            new_cmd->Request        = ((tPosCmd)cmd.message)->Request;
            new_cmd->Response       = ((tPosCmd)cmd.message)->Response;
            new_cmd->Done           = ((tPosCmd)cmd.message)->Done;
            new_cmd->Position.x     = ((tPosCmd)cmd.message)->Position.x;
            new_cmd->Position.y     = ((tPosCmd)cmd.message)->Position.y;
            new_cmd->Velocity       = ((tPosCmd)cmd.message)->Velocity;
            new_cmd->Acceleration   = ((tPosCmd)cmd.message)->Acceleration;
            new_cmd->Deceleration   = ((tPosCmd)cmd.message)->Deceleration;
            new_cmd->Jerk           = ((tPosCmd)cmd.message)->Jerk;

            Message msg;
            msg.type = type_task_command_sender;
            msg.message = new_cmd;

            Messenger::GetInstance()->PostMessageWithoutInforming(msg);

            //cycle_count = cycle_count + 1;

            /*if(cycle_count == 5)
            {
                new_cmd->Request = true;
                new_cmd->Response = false;
                new_cmd->Done = false;
                new_cmd->Position = {20000,20000};
                new_cmd->Velocity = 1000;
                new_cmd->Acceleration = 50;
                new_cmd->Deceleration = 50;
                new_cmd->Jerk = 0;
            }*/
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    mlockall(MCL_CURRENT|MCL_FUTURE);

    task_trajectory_generator += task_trajectory_generator_proc;
    task_command_sender += task_command_sender_proc;
    task_trajectory_generator.StartTask();
    task_command_sender.StartTask();

    GuiManager w;
    w.show();
    w.setWindowTitle("TrajectoryBuilder");

    //while(!new_cmd.Done);
    //task_trajectory_generator.DeleteTask();
    //task_command_sender.DeleteTask();

    return a.exec();
}



