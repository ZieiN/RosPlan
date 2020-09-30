//
// Created by vlad on 17.09.2020.
//
//#include <ros/ros.h>
//#include <ros/console.h>
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>

#include <rtp_msgs/PathStamped.h>
#include <tf2_msgs/TFMessage.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Odometry.h>
#include <cmath>
#include <iostream>

#include "astar/planner.cpp"

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

/*
 *
 * We should use timeframes as info about initial position of Husky.
 * Key topic is /tf
 * Key message is this:
 * transforms:
  -
    header:
      seq: 0
      stamp:
        secs: 1600688027
        nsecs: 458736658
      frame_id: "local_map"
    child_frame_id: "isns_link"
    transform:
      translation:
        x: -0.522678655283
        y: -0.545478372622
        z: 0.100030964836
      rotation:
        x: -0.00353503691281
        y: 0.000156997113857
        z: -0.0243503432644
        w: 0.999697223988
---

 * In this example robot faces "downside" of Coppeliasim world,
 * also looks like he in the center of the grid.
 */
class Planner{
private:
    ros::Subscriber     timeFrame;
    ros::Subscriber     occupancyGrid;
    ros::Subscriber     clickedPoint;
    ros::Subscriber     initialPose;
    ros::Subscriber     robotPose;

    ros::Publisher      trajectoryPublisher;

    nav_msgs::OccupancyGrid         grid;
    geometry_msgs::PointStamped     goal;
    rtp_msgs::PathStamped           path;
    geometry_msgs::PoseWithCovarianceStamped    start;
    geometry_msgs::PoseWithCovariance           huskyPose;
    geometry_msgs::TransformStamped             isns_link;
public:
    Planner(ros::NodeHandle nh);

    void setTimeFrame(const tf2_msgs::TFMessage::ConstPtr& timeFrameMsg){
        for(auto transform : timeFrameMsg->transforms){
            if (transform.child_frame_id == "isns_link") this->isns_link = transform;
        }

    }
    void setGrid(const nav_msgs::OccupancyGrid::ConstPtr& gridMsg){
        this->grid = *gridMsg;
    }
    void setGoal(const geometry_msgs::PointStamped::ConstPtr& goalMsg){
        this->goal = *goalMsg;
        transformPointToGrid(this->goal.point);
        this->goal.header.frame_id = "local_map";
        ROS_INFO_STREAM(goal.point);
        search(grid, start.pose.pose.position, goal.point, path);
    }
    void setStart(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& startMsg){
        this->start = *startMsg;
        transformPointToGrid(this->start.pose.pose.position);
        ROS_INFO_STREAM(start.pose.pose.position);
        this->start.header.frame_id = "local_map";
    }
    void setRobotPose(const nav_msgs::Odometry::ConstPtr& odometryMsg){
        this->huskyPose = odometryMsg->pose;
    }
    void transformPointToGrid(geometry_msgs::Point& point); //move this to tools.h
    void transformPointToGoal(geometry_msgs::Point& point); //move this to tools.h
    void transformPathToGlobal();
};



Planner::Planner(ros::NodeHandle nh){
    //todo: check hz of all nodes
    trajectoryPublisher     = nh.advertise<rtp_msgs::PathStamped>   ("/trajectory",
                                                                    50);
    timeFrame               = nh.subscribe<tf2_msgs::TFMessage>     ("tf",
                                                                    50,
                                                                    &Planner::setTimeFrame,
                                                                    this);
    occupancyGrid           = nh.subscribe<nav_msgs::OccupancyGrid> ("/occupancy/accumulated",
                                                                    14,
                                                                    &Planner::setGrid,
                                                                    this);
    clickedPoint            = nh.subscribe<geometry_msgs::PointStamped>
                                                                    ("/clicked_point",
                                                                    50,
                                                                    &Planner::setGoal,
                                                                    this);
    initialPose             = nh.subscribe<geometry_msgs::PoseWithCovarianceStamped>
                                                                    ("/initialpose",
                                                                    50,
                                                                    &Planner::setStart,
                                                                    this);
    robotPose               = nh.subscribe<nav_msgs::Odometry>      ("/odometry",
                                                                    5,
                                                                    &Planner::setRobotPose,
                                                                    this);
}



void Planner::transformPointToGrid(geometry_msgs::Point& point) {
    //At first we transform our coordinates refer to robot position
    point.x = point.x - huskyPose.pose.position.x - isns_link.transform.translation.x;
    point.y = point.y - huskyPose.pose.position.y + isns_link.transform.translation.y;
    auto thetta = sgn(2 * asin(grid.info.origin.orientation.y)) * 2 * acos(grid.info.origin.orientation.x);
    //we rotate goal coordinates to match their orientation with grid system
    auto new_x = point.x * cos(thetta) - point.y * sin(thetta);
    auto new_y = point.x * sin(thetta) + point.y * cos(thetta);
    point.x = new_x;
    point.y = new_y;
    //then we moves goal system to completely match with grid
    point.x = point.x - grid.info.origin.position.x;
    point.y = point.y - grid.info.origin.position.y;
    point.z = point.z - grid.info.origin.position.z;
    //and then we transform them to become cell-based
    point.x = int(point.x / grid.info.resolution)-1;
    point.y = int(point.y / grid.info.resolution)-1;
}
void Planner::transformPointToGoal(geometry_msgs::Point& point) {
    //We should perform similar operations as in "to grid" algorithm but in reverse
    //firstly resize back to global coords
    point.x = (point.x+1) * grid.info.resolution;
    point.y = (point.y+1) * grid.info.resolution;
    //the move refer to grid origin
    point.x = point.x + grid.info.origin.position.x;
    point.y = point.y + grid.info.origin.position.y;
    point.z = point.z + grid.info.origin.position.z;
    //then rotate
    auto thetta = -sgn(2 * asin(grid.info.origin.orientation.y)) * 2 * acos(grid.info.origin.orientation.x);
    auto new_x = point.x * cos(thetta) - point.y * sin(thetta);
    auto new_y = point.x * sin(thetta) + point.y * cos(thetta);
    point.x = new_x;
    point.y = new_y;
    //and move refer to Husky and lidar positions
    point.x = point.x + huskyPose.pose.position.x + isns_link.transform.translation.x;
    point.y = point.y + huskyPose.pose.position.y - isns_link.transform.translation.y;
}
void Planner::transformPathToGlobal() {
    for(auto element : path.path_points_with_metadata){
        element.pose.position = transformPointToGlobal(element.pose.position);
    }
}

int main(int argc, char **argv){
    ros::init(argc, argv, "planner_node");
    ros::NodeHandle nh;
    Planner customPlanner = Planner(nh);
    ros::spin();
}