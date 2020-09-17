//
// Created by vlad on 17.09.2020.
//
#include <ros/ros.h>
#include <ros/console.h>
#include <cmath>
#include <iostream>


class Planner{
private:
    ros::Publisher trajectoryPublisher;
    ros::Subscriber taskSubscriber;
public:
    Planner(ros::NodeHandle nh);
};

Planner::Planner(ros::NodeHandle nh){
    trajectoryPublisher = nh.ad
}

int main(){
    ros::NodeHandle nh;
    Planner customPlanner = Planner(nh);
}