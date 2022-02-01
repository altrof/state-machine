//
// Created by altrof on 01.02.22.
//

#include "main.h"


void Main::step() {
    mudel.setExternalInputs(&inputs);
    outputs = mudel.getExternalOutputs();



    ROS_INFO("Autonomous Status: %u", outputs.AS_STATUS_OUT);
    ROS_INFO("Indicator: %u", outputs.ASSI_OUT);
    ROS_INFO("Service Brake: %u", outputs.SB_OUT);
    ROS_INFO("Steering Actuator: %u", outputs.SA_OUT);
    ROS_INFO("Brake Pressure Released: %hhd", outputs.BRAKE_PRESSURE_RELEASED_OUT);

    mudel.step();
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