#include <ros/ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseArray.h>
#include <gazebo_msgs/ModelStates.h>
#include <nav_msgs/OccupancyGrid.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <stack>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <iostream>
#include <ros/console.h>
#include <coord_transform/coords.h>

#include "A_search.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class Planner{
private:
  ros::Subscriber goalSub;
  ros::Subscriber gridSub;
  ros::Subscriber poseSub;
  ros::Subscriber actionSub;
  ros::Publisher pub;
  ros::Rate rate = ros::Rate(50);
  ros::ServiceClient globalToGridClient;
  ros::ServiceClient gridToGlobalClient;

  geometry_msgs::PoseArray path;
  bool goalIsSet = false;
  bool gridIsSet = false;
  bool planned = false;
  Node goal;
  Node start;
  Map grid;
  A_search AStarPlanner;

  void setGoal(const geometry_msgs::Pose::ConstPtr& goalMsg);
  void setGrid(const nav_msgs::OccupancyGrid::ConstPtr& gridMsg);
  void setStart(const geometry_msgs::Pose::ConstPtr& HuskyPoseMsg);
  void action(const std_msgs::String::ConstPtr& actionMsg);
  bool checkTask();
public:
  Planner(ros::NodeHandle &nh);

  //These function allow user to get path via A* planner
  geometry_msgs::PoseArray getAStarPath();

  //This function publish created path to the publisher
  void publish();
};
////////////////////////////////////////////////////////////////////////////////
Planner::Planner(ros::NodeHandle &nh){
  globalToGridClient = nh.serviceClient<coord_transform::coords>("global_to_grid");
  gridToGlobalClient = nh.serviceClient<coord_transform::coords>("grid_to_global");
  goalSub = nh.subscribe<geometry_msgs::Pose>("set_goal", 50, &Planner::setGoal, this);
  gridSub = nh.subscribe<nav_msgs::OccupancyGrid>("set_occupancy_grid", 50, &Planner::setGrid, this);
  poseSub = nh.subscribe<geometry_msgs::Pose>("robot_pose", 50, &Planner::setStart, this);
  actionSub = nh.subscribe<std_msgs::String>("action", 50, &Planner::action, this);
  pub = nh.advertise<geometry_msgs::PoseArray>("set_path", 50);
  double e;
  std::string metricType;
  nh.param<double>("hweight", e, 1.0); //todo: add checking
  nh.param<std::string>("heuristic", metricType, "euclidean"); //todo: add checking
  AStarPlanner = AStarPlanner(e, chosen_one);
}

void Planner::setGoal(const geometry_msgs::Pose::ConstPtr& goalMsg){
  goal = Node(goalMsg->position.x, goalMsg->position.y, /*id here*/); //todo:
  if (gridIsSet){
    coord_transform::coords crd;
    crd.request.info = grid.info;
    crd.request.input = goal;
    globalToGridClient.call(crd);
    goal = crd.response.output;
    goalIsSet = true;
    ROS_INFO_STREAM("Goal was received by path_planner");
    ROS_INFO_STREAM("Goal in grid coordinates: " << goal.position.x << " " << goal.position.y);
  }else ROS_WARN_STREAM("Cannot transform goal point coordinates into grid system. Send grid info first");
}

void Planner::setGrid(const nav_msgs::OccupancyGrid::ConstPtr& gridMsg){
  grid = *gridMsg;
  gridIsSet = true;
  ROS_INFO_STREAM("Grid was received by path_planner");
}

bool Planner::checkTask(){
  if (grid.info.width * grid.info.height != grid.data.size()){
    ROS_ERROR_STREAM("Grid error. Input data incorrect. Number of grid elements does not match width and height.");
    return false;
  }
  if (isnan(grid.info.origin.position.x)){
    ROS_ERROR_STREAM("Grid error. Input data incorrect. Grid origin position x is NaN.");
    return false;
  }
  if (isnan(grid.info.origin.position.y)){
    ROS_ERROR_STREAM("Grid error. Input data incorrect. Grid origin position y is NaN.");
    return false;
  }
  if (isnan(grid.info.resolution)){
    ROS_ERROR_STREAM("Grid error. Input data incorrect. Grid resolution is NaN.");
    return false;
  }
  if (grid.info.resolution <= 0){
    ROS_ERROR_STREAM("Grid error. Input data incorrect. Grid resolution is less or equal zero.");
    return false;
  }
  if ((goal.position.x > grid.info.width) || (goal.position.y > grid.info.height)){
    ROS_ERROR_STREAM("Goal is anacceptable: point is out of occupancy grid");
    return false;
  }
  //todo: проверка current position
  return true;
}
void Planner::setStart(const geometry_msgs::Pose::ConstPtr& HuskyPoseMsg){
  start = *HuskyPoseMsg;
  coord_transform::coords crd;
  crd.request.info = grid.info;
  crd.request.input = start;
  //ROS_INFO_STREAM("before transformation: "<< start.position.x << " " << start.position.y << " " << start.position.z);
  globalToGridClient.call(crd);
  start = crd.response.output;
  //ROS_INFO_STREAM("after transformation: "<< start.position.x << " " << start.position.y << " " << start.position.z);
}

void Planner::action(const std_msgs::String::ConstPtr& actionMsg){
  if (actionMsg->data == "find-path-astar"){
    if (checkTask()) path = getAStarPath();
    else ROS_ERROR_STREAM("Path planning error. Stopping");
  }else if (actionMsg->data == "get-path"){
    publish();
  }else if (actionMsg->data == "status-planner"){
    ROS_INFO_STREAM("Current status:");
    if (planned) {
      ROS_INFO_STREAM("Planning completed");
      ROS_INFO_STREAM("Path is:");
      for (auto point : path.poses){
        ROS_INFO_STREAM(point.position.x << "  " << point.position.y);
      }
    } else ROS_INFO_STREAM("No path has been planned yet");
    if (goalIsSet){
      ROS_INFO_STREAM("Goal is " << goal.position.x << " " << goal.position.y << " in grid coordinates");
      //ROS_INFO_STREAM("Goal is " << SIZE_CELL*goal.position.x  - SIZE_CELL << " " << SIZE_CELL - SIZE_CELL*goal.position.y << " in global coordinates");
    } else ROS_INFO_STREAM("No goal has been choosed yet");
  }
}


geometry_msgs::PoseArray Planner::getAStarPath(){
  planned = true;//но это может быть не так!
  return AStarPlanner.getPath(start, goal, grid);
}

void Planner::publish(){
  while(pub.getNumSubscribers() == 0)
    rate.sleep();
  coord_transform::coords crd;
  geometry_msgs::PoseArray pub_path;
  for(auto point : path.poses){
    crd.request.info = grid.info;
    crd.request.input = point;
    gridToGlobalClient.call(crd);
    point = crd.response.output;
    pub_path.poses.push_back(point);
  }
  pub.publish(pub_path);
}
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv) {
  ros::init(argc, argv, "path_planner");
  ros::NodeHandle nh;
  Planner planner = Planner(nh);
  ros::spin();
}
