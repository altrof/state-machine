//
// Created by altrof on 20.01.22.
//

#include "ros/ros.h"
#include "as_workflow/as_workflow_ert_rtw/as_workflow.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include "std_msgs/Int8.h"
#include "std_msgs/Float32.h"

as_workflowModelClass::ExtU_as_workflow_T inputs;
as_workflowModelClass::ExtY_as_workflow_T outputs;


void setEbsStatus (const std_msgs::Int8::ConstPtr& msg) {
    inputs.EBS_IN = EBS_STATE(msg->data);
}

void seTsStatus (const std_msgs::Bool::ConstPtr& msg) {
    inputs.TS_IN = msg->data;
}

void setAsmsStatus (const std_msgs::Bool::ConstPtr& msg) {
    inputs.ASMS_IN = msg->data;
}

void setMissionStatus (const std_msgs::Int8::ConstPtr& msg) {
    inputs.MISSION_IN = MISSION(msg->data);
}

void setMissionFinishStatus (const std_msgs::Bool::ConstPtr& msg) {
    inputs.MISSION_FINISH_IN = msg->data;
}

void setResTriggeredStatus (const std_msgs::Bool::ConstPtr& msg) {
    inputs.RES_IN = msg->data;
}

void setFirstBrakePressure (const std_msgs::Float32::ConstPtr& msg) {
    inputs.FIRST_BRAKE_IN = msg->data;
}

void setSecondBrakePressure (const std_msgs::Float32::ConstPtr& msg) {
    inputs.SECOND_BRAKE_IN = msg->data;
}


int main (int argc, char **argv) {
    ros::init(argc, argv, "subscriber");
    ros::NodeHandle n;

    ros::Subscriber ebs_sub = n.subscribe("ebs_topic", 1000, setEbsStatus);
    ros::Subscriber ts_sub = n.subscribe("ts_topic", 1000, seTsStatus);
    ros::Subscriber asms_sub = n.subscribe("asms_topic", 1000, setAsmsStatus);
    ros::Subscriber resTrigger_sub = n.subscribe("resTrigger_topic", 1000, setResTriggeredStatus);
    ros::Subscriber missionFinish_sub = n.subscribe("missionFinish_topic", 1000, setMissionFinishStatus);
    ros::Subscriber mission_sub = n.subscribe("mission_topic", 1000, setMissionStatus);
    ros::Subscriber firstBrake_sub = n.subscribe("firstBrake_topic", 1000, setFirstBrakePressure);
    ros::Subscriber secondBrake_sub = n.subscribe("secondBrake_topic", 1000, setSecondBrakePressure);
    as_workflowModelClass mudel;


    mudel.initialize();

    ros::Rate rate(1);

    while(ros::ok()) {

        mudel.setExternalInputs(&inputs);
        outputs = mudel.getExternalOutputs();



        ROS_INFO("Autonomous Status: %u", outputs.AS_STATUS_OUT);
        ROS_INFO("Indicator: %u", outputs.ASSI_OUT);
        ROS_INFO("Service Brake: %u", outputs.SB_OUT);
        ROS_INFO("Steering Actuator: %u", outputs.SA_OUT);
        ROS_INFO("Brake Pressure Released: %hhd", outputs.BRAKE_PRESSURE_RELEASED_OUT);

        mudel.step();
        rate.sleep();
        ros::spinOnce();
    };
}
