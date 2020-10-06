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
    // I changed start to normal point for easier work when searching for path.
    geometry_msgs::Point            start;
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
        ROS_INFO_STREAM(start);
        ROS_INFO_STREAM(goal.point);
        search(grid, start, goal.point, path);
        transformPathToGlobal();
        // This must be changed to publish every time we receive /occupancy/accumulated. I let it here now, because there are some functions don't work with empty paths.
        trajectoryPublisher.publish(path);
    }
    void setRobotPose(const nav_msgs::Odometry::ConstPtr& odometryMsg){
        this->huskyPose = odometryMsg->pose;
        this->start = huskyPose.pose.position;
        transformPointToGrid(this->start);
    }
    void transformPointToGrid(geometry_msgs::Point& point); //move this to tools.h
    void transformPointToGlobal(geometry_msgs::Point& point); //move this to tools.h
    void transformPathToGlobal();
    void publish();
};

void Planner::publish(){
    trajectoryPublisher.publish(path);
}

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
    // We don't need startpos, we will manipulate with robotpose all time (even in the beginning, odometry give us correct data).
    robotPose               = nh.subscribe<nav_msgs::Odometry>      ("/odometry",
                                                                    5,
                                                                    &Planner::setRobotPose,
                                                                    this);
    clickedPoint            = nh.subscribe<geometry_msgs::PointStamped>
                                                                    ("/clicked_point",
                                                                    50,
                                                                    &Planner::setGoal,
                                                                    this);

    // We need something for initializing because we must send the trajectory every time we receive /occupancy/accumulated.
    // this is not enough - other functions must able to send empty paths.
    goal.point.x = start.x = 299;
    goal.point.y = start.y = 299;
}



void Planner::transformPointToGrid(geometry_msgs::Point& point) {
    point.x = point.x - huskyPose.pose.position.x;
    point.y = point.y - huskyPose.pose.position.y;

    // auto thetta = atan2(huskyPose.pose.orientation.z, huskyPose.pose.orientation.w) * 2.0;

    // seems that the orientation of the map is fixed to below:
    auto thetta = 1.57079632679;

    auto new_x = point.x * cos(thetta) - point.y * sin(thetta);
    auto new_y = point.x * sin(thetta) + point.y * cos(thetta);
    point.x = new_x;
    point.y = new_y;

    point.x = int(point.x / grid.info.resolution)-1;
    point.y = int(point.y / grid.info.resolution)-1;

    point.x += 299;
    point.y += 299;
}
void Planner::transformPointToGlobal(geometry_msgs::Point& point) {
    point.x -= 299;
    point.y -= 299;

    point.x = (point.x+1) * grid.info.resolution;
    point.y = (point.y+1) * grid.info.resolution;

    // auto thetta = -atan2(huskyPose.pose.orientation.z, huskyPose.pose.orientation.w) * 2.0;

    // seems that the orientation of the map is fixed to below:
    auto thetta = -1.57079632679;

    auto new_x = point.x * cos(thetta) - point.y * sin(thetta);
    auto new_y = point.x * sin(thetta) + point.y * cos(thetta);
    point.x = new_x;
    point.y = new_y;

    point.x = point.x + huskyPose.pose.position.x;
    point.y = point.y + huskyPose.pose.position.y;
}
void Planner::transformPathToGlobal() {
    
    for(int i=0; i<path.path_points_with_metadata.size(); ++i){
        transformPointToGlobal(path.path_points_with_metadata[i].pose.position);
    }
    reverse(path.path_points_with_metadata.begin(), path.path_points_with_metadata.end());
    
}

int main(int argc, char **argv){
    ros::init(argc, argv, "planner_node");
    ros::NodeHandle nh;
    Planner customPlanner = Planner(nh);
    ros::spin();
}
