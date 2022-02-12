//
// Created by altrof on 01.02.22.
//

#ifndef STATE_MACHINE_MAIN_H
#define STATE_MACHINE_MAIN_H

#include <ros/ros.h>
#include "as_workflow/as_workflow_ert_rtw/as_workflow.h"
#include "std_msgs/String.h"
#include "std_msgs/builtin_bool.h"
#include "std_msgs/Int8.h"
#include "std_msgs/Float32.h"
#include "dv_main/sendCan.h"

class Main {
public:
    as_workflowModelClass::ExtU_as_workflow_T inputs{};
    as_workflowModelClass::ExtY_as_workflow_T outputs{};
    as_workflowModelClass mudel;


    explicit Main(ros::NodeHandle nh): nh (nh) {
        mudel.initialize();  // init


        // Subscribers:

        // line 852 | topics = canDB => EBS_Out2
        ebs_sub = nh.subscribe("/can/messages/EBS_Out2", 10, &Main::ebsStatusCb,  this);
        // line 791 | topics = canDB => AMS_Data
        ams_sub = nh.subscribe("/can/messages/AMS_Data", 10, &Main::amsCb, this);
        // line 808 | topics = canDB => RES_TransmitPDO
        res_sub = nh.subscribe("/can/messages/RES_TransmitPDO", 10, &Main::resCb, this);
        // line 189 | topics = canDB => Dash_Out2
        dash_sub = nh.subscribe("can/message/Dash_Out2", 10, &Main::dashboardCb, this);
        // line 356 | topics = canDB => DAQ_Out1
        brakepress_sub = nh.subscribe("/can/messages/DAQ_Out1", 10, &Main::brakePressureCb, this);
        // Mission Finish Status
        mission_sub = nh.subscribe("/mission_finished", 10, &Main::missionFinishCb, this);



        // Publishers
        can_pub = nh.advertise<dv_main::sendCan>("/can/send", 10);
        sa_pub = nh.advertise<std_msgs::Bool>("/SA_state", 10);
        driveStart_pub = nh.advertise<std_msgs::Bool>("/dynamics/start", 10);

    }

    void step();

private:

    // getData from CAN for Callbacks
    static double getData(const dv_main::sendCanConstPtr& msg, const std::string& name) {
        return msg->data[std::distance(msg->name.begin(), std::find(msg->name.begin(), msg->name.end(), name))];
    }

    // Callbacks:

    void ebsStatusCb (const dv_main::sendCanConstPtr &msg) {
        inputs.EBS = EBS_STATE(getData(msg, "EBS_State")); // EBS_Out2.EBS_State, msg (842)
        inputs.IS_ASMS_ON = bool(getData(msg, "EBS_ASMS")); // EBS_Out2.EBS_ASMS, msg (843)
    }

    void amsCb (const dv_main::sendCanConstPtr &msg) {
        inputs.IS_TS_ON = bool(getData(msg, "Shutdown_active")); // AMS_Data.Shutdown_active, msg (794)
    }

    void resCb (const dv_main::sendCanConstPtr &msg) {
        inputs.IS_RES_GO = bool(getData(msg, "PushButton")); // RES_TransmitPDO.PushButton, msg (831)
        inputs.IS_RES_TRIGGERED = !bool(getData(msg, "Estop")); // RES_TransmitPDO.Estop, msg (828)
        // If button is up = >> [Estop = 1] << = Not triggered
    }

    void dashboardCb (const dv_main::sendCanConstPtr &msg) {
        inputs.MISSION_STATUS = MISSION(getData(msg, "Dash_SetAMI")); // Dash_Out2.Dash_SetAMI, msg (192)
    }

    void missionFinishCb (const std_msgs::Bool::ConstPtr& msg) {
        inputs.IS_MISSION_FINISHED = msg->data;
    }

    void brakePressureCb (const dv_main::sendCanConstPtr &msg) {
        inputs.FRONT_BRAKE = int(getData(msg, "BrakePressureF")); // DAQ_Quit1.BrakePressureF, msg (361)
        inputs.REAR_BRAKE = int(getData(msg, "BrakePressureR")); // DAQ_Quit1.BrakePressureR, msg (362)
    }



    ros::NodeHandle nh;

    // Subscribers
    ros::Subscriber ebs_sub; // Emergency Brake System
    ros::Subscriber res_sub; // Remote Emergency System
    ros::Subscriber ams_sub; // Accumulator Management System
    ros::Subscriber dash_sub; // Dashboard
    ros::Subscriber brakepress_sub; // Brake Pressure
    ros::Subscriber mission_sub; // Mission Finish Status

    // Publishers
    ros::Publisher can_pub;
    ros::Publisher sa_pub;
    ros::Publisher driveStart_pub;

    void publishSystemState();
    void publishDvGo();
};


#endif //STATE_MACHINE_MAIN_H
