//
// Created by altrof on 01.02.22.
//

#include "main.h"

void Main::publishSystemState() {
    dv_main::sendCan outMsg;

    outMsg.message_name = "DV_SystemStatus";

    outMsg.name.push_back("DV_AS_State"); //  DV_SystemStatus.DV_AS_State = outputs.AS_STATUS_OUT
    outMsg.data.push_back(outputs.AS_STATUS_OUT);

    outMsg.name.push_back("DV_EBS_State"); //  DV_SystemStatus.DV_EBS_State = inputs.EBS
    outMsg.data.push_back(inputs.EBS);

    outMsg.name.push_back("DV_AMI_State"); //  DV_SystemStatus.DV_AMI_State = inputs.MISSION_STATUS
    outMsg.data.push_back(inputs.MISSION_STATUS);

    outMsg.name.push_back("DV_SteeringState"); //  DV_SystemStatus.DV_SteeringState = outputs.SA_OUT
    outMsg.data.push_back(outputs.SA_OUT);

    outMsg.name.push_back("DV_ServiceBrakeState"); // DV_SystemStatus.DV_ServiceBrakeState = outputs.SB_OUT
    outMsg.data.push_back(outputs.SB_OUT);

    outMsg.name.push_back("DV_LapCounter"); //  DV_SystemStatus.ConeCountAll = 1
    outMsg.data.push_back(1);

    outMsg.name.push_back("DV_ConeCountActual"); //  DV_SystemStatus.ConeCountAll = 1
    outMsg.data.push_back(1);

    outMsg.name.push_back("DV_ConeCountAll"); // DV_SystemStatus.ConeCountAll = 1
    outMsg.data.push_back(1);

    can_pub.publish(outMsg);
}

void Main::publishDvGo() {
    dv_main::sendCan outMsg;

    outMsg.message_name = "DV_Go";
    outMsg.name.push_back("GO");
    if(outputs.AS_STATUS_OUT == AS_STATE_AS_DRIVING) {
        outMsg.data.push_back(1);
    } else outMsg.data.push_back(0);

    can_pub.publish(outMsg);
}

void Main::step() {
    mudel.setExternalInputs(&inputs);
    outputs = mudel.getExternalOutputs();


    ROS_INFO("Autonomous Status: %u", outputs.AS_STATUS_OUT);
    ROS_INFO("Indicator: %u", outputs.ASSI_OUT);
    ROS_INFO("Service Brake: %u", outputs.SB_OUT);
    ROS_INFO("Steering Actuator: %u", outputs.SA_OUT);
    ROS_INFO("Brake Pressure Released: %hhd", outputs.BRAKE_PRESSURE_RELEASED_OUT);
    mudel.step();

    publishDvGo();
    publishSystemState();

}

int main(int argc, char **argv) {
    ros::init(argc, argv, "state_machine");
    ros::NodeHandle nh;

    ros::Rate rate(10);
    Main main(nh);
    while (ros::ok()) {
        main.step();
        rate.sleep();
        ros::spinOnce();
    }
}