//
// Created by altrof on 01.02.22.
//

#ifndef STATE_MACHINE_MAIN_H
#define STATE_MACHINE_MAIN_H

#include "ros/ros.h"
#include "as_workflow/as_workflow_ert_rtw/as_workflow.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include "std_msgs/Int8.h"
#include "std_msgs/Float32.h"

class Main {
public:
    as_workflowModelClass::ExtU_as_workflow_T inputs;
    as_workflowModelClass::ExtY_as_workflow_T outputs;
    as_workflowModelClass mudel;

    // javnoe
    explicit Main(ros::NodeHandle nh): nh (nh) {
        mudel.initialize();

        ebs_sub = nh.subscribe("ebs_topic", 1000, &Main::setEbsStatus,  this);
        ts_sub = nh.subscribe("ts_topic", 1000, &Main::seTsStatus,  this);
        asms_sub = nh.subscribe("asms_topic", 1000, &Main::setAsmsStatus, this);
        resTrigger_sub = nh.subscribe("resTrigger_topic", 1000, &Main::setResTriggeredStatus, this);
        mission_sub = nh.subscribe("mission_topic", 1000, &Main::setMissionStatus, this);
        missionFinish_sub = nh.subscribe("missionFinish_topic", 1000, &Main::setMissionFinishStatus, this);
        firstBrake_sub = nh.subscribe("firstBrake_topic", 1000, &Main::setFirstBrakePressure, this);
        secondBrake_sub = nh.subscribe("secondBrake_topic", 1000, &Main::setSecondBrakePressure, this);
    }

    void step();

private:

    void setEbsStatus (const std_msgs::Int8::ConstPtr& msg) {
        inputs.EBS_IN = EBS_STATE(msg->data);
    }

    void seTsStatus (const std_msgs::Bool::ConstPtr& msg) {
        inputs.TS_IN = msg->data;
    }

    void setAsmsStatus (const std_msgs::Bool::ConstPtr& msg) {
        inputs.ASMS_IN = msg->data;
    }

    void setResTriggeredStatus (const std_msgs::Bool::ConstPtr& msg) {
        inputs.RES_IN = msg->data;
    }

    void setMissionStatus (const std_msgs::Int8::ConstPtr& msg) {
        inputs.MISSION_IN = MISSION(msg->data);
    }

    void setMissionFinishStatus (const std_msgs::Bool::ConstPtr& msg) {
        inputs.MISSION_FINISH_IN = msg->data;
    }

    void setFirstBrakePressure (const std_msgs::Float32::ConstPtr& msg) {
        inputs.FIRST_BRAKE_IN = msg->data;
    }

    void setSecondBrakePressure (const std_msgs::Float32::ConstPtr& msg) {
        inputs.SECOND_BRAKE_IN = msg->data;
    }


    ros::NodeHandle nh;

    ros::Subscriber ebs_sub;
    ros::Subscriber ts_sub;
    ros::Subscriber asms_sub;
    ros::Subscriber resTrigger_sub;
    ros::Subscriber missionFinish_sub;
    ros::Subscriber mission_sub;
    ros::Subscriber firstBrake_sub;
    ros::Subscriber secondBrake_sub;


};


#endif //STATE_MACHINE_MAIN_H
