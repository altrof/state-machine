//
// Created by altrof on 20.01.22.
//

#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include "std_msgs/Int8.h"
#include "std_msgs/Float32.h"

int main (int argc, char **argv) {
    ros::init(argc, argv, "publisher");
    ros::NodeHandle n;
    ros::Publisher ebs_pub = n.advertise<std_msgs::Int8>("ebs_topic", 1000);
    ros::Publisher ts_pub = n.advertise<std_msgs::Bool>("ts_topic", 1000);
    ros::Publisher asms_pub = n.advertise<std_msgs::Bool>("asms_topic", 1000);
    ros::Publisher resTrigger_pub = n.advertise<std_msgs::Bool>("resTrigger_topic", 1000);
    ros::Publisher missionFinish_pub = n.advertise<std_msgs::Bool>("missionFinish_topic", 1000);
    ros::Publisher mission_pub = n.advertise<std_msgs::Int8>("mission_topic", 1000);
    ros::Publisher firstBrake_pub = n.advertise<std_msgs::Float32>("firstBrake_topic", 1000);
    ros::Publisher secondBrake_pub = n.advertise<std_msgs::Float32>("secondBrake_topic", 1000);

//    while(ros::ok()) {
//        std_msgs::Int8 ebs_data;
//        ebs_data.data = 1; // 1 - ARMED
//        ebs_pub.publish(ebs_data);
//
//        std_msgs::Bool ts_data;
//        ts_data.data = true;
//        ts_pub.publish(ts_data);
//
//        std_msgs::Bool asms_data;
//        asms_data.data = true;
//        asms_pub.publish(asms_data);
//
//        std_msgs::Bool resTrigger_data;
//        resTrigger_data.data = false;
//        resTrigger_pub.publish(resTrigger_data);
//
//        std_msgs::Bool missionFinish;
//        missionFinish.data = false;
//        missionFinish_pub.publish(missionFinish);
//
//        std_msgs::Int8 mission_data;
//        mission_data.data = 2;
//        mission_pub.publish(mission_data);
//
//        std_msgs::Float32 firstBrake_data;
//        firstBrake_data.data = 2.5;
//        firstBrake_pub.publish(firstBrake_data);
//
//        std_msgs::Float32 secondBrake_data;
//        secondBrake_data.data = 2.5;
//        secondBrake_pub.publish(firstBrake_data);
//    }

}