//
// Created by vlad on 20.09.2020.
//

#include <ros/ros.h>
#include <ros/console.h>

#include <rtp_msgs/RouteTask.h>
#include <tf2_msgs/TFMessage.h>
#include <nav_msgs/Odometry.h>
#include <nav_msgs/OccupancyGrid.h>
#include <cmath>
#include <iostream>



class RouteCreator{
private:
    //what is gis_rtk/waypoints
    ros::Subscriber;
    ros::Publisher routePublisher
public:


};
/move_base_simple/goal - geometry_msgs/PoseStamped

int main(int argc, char **argv){
    ros::init(argc, argv, "route_node");
    ros::NodeHandle nh;
    //Planner customPlanner = Planner(nh);
    ros::spin();
}