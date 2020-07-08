#include <ros/ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseArray.h>
#include <std_msgs/Bool.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <ros/console.h>

class Dispenser {
private:
  std::vector<geometry_msgs::Pose> path;
  ros::Subscriber sub;
  ros::Subscriber arv;
  //ros::Subscriber rcv;
  ros::Subscriber act;
  ros::Publisher pub;
  bool pause = true;
public:
  Dispenser(ros::NodeHandle nh);
  void fillPath(const geometry_msgs::PoseArray::ConstPtr &posesMsg);
  void dispense(const std_msgs::Bool::ConstPtr &arrival);
  void erase(const std_msgs::Bool::ConstPtr &recieved);
  void action(const std_msgs::String::ConstPtr & actionMsg);
};

Dispenser::Dispenser(ros::NodeHandle nh){
  sub = nh.subscribe<geometry_msgs::PoseArray>("set_path", 50, &Dispenser::fillPath, this);
  arv = nh.subscribe<std_msgs::Bool>("arrival", 50, &Dispenser::dispense, this);
  act = nh.subscribe<std_msgs::String>("action", 50, &Dispenser::action, this);
  pub = nh.advertise<geometry_msgs::Pose>("set_target", 50);
}


void Dispenser::fillPath(const geometry_msgs::PoseArray::ConstPtr &posesMsg){
  if (path.empty()) {
    for (auto pose : posesMsg->poses){
      path.push_back(pose);
    }
    ROS_INFO_STREAM("Path was recieved by target_dispatcher");
  }else ROS_WARN_STREAM("Attempt to give another path. You need to STOP first");
}

void Dispenser::dispense(const std_msgs::Bool::ConstPtr &arrival){
  if(!pause){
    if(arrival->data){
      if(path.size() != 0){
        pub.publish(path[0]);
        path.erase(path.begin());
      }else {ROS_INFO_STREAM("path complete"); pause = true;}
    }
  }
}

void Dispenser::action(const std_msgs::String::ConstPtr &actionMsg){
  if (actionMsg->data == "status-dispatcher"){
    ROS_INFO_STREAM("Current status of target dispatcher");
    if (!pause) ROS_INFO_STREAM("Dispatcher is operational"); else ROS_INFO_STREAM("Dispatcher is paused");
    ROS_INFO_STREAM("Path is:");
    for (auto point = path.begin(); point != path.end(); ++point){
      ROS_INFO_STREAM((*point).position.x << "  " << (*point).position.y);
    }
    if (path.size() == 0) ROS_INFO_STREAM("NULL");
    ROS_INFO_STREAM("Next point is:");
    if (path.size() != 0) ROS_INFO_STREAM((path[0]).position.x << "  " << (path[0]).position.y);
    else ROS_INFO_STREAM("None");
  }else if (actionMsg->data == "start"){
    pause = false;
  }else if (actionMsg->data == "pause"){
    pause = true;
  }else if (actionMsg->data == "continue") {
    pause = false;
  }else if (actionMsg->data == "stop"){
    pause = true;
    path.clear();
  }
}


int main(int argc, char **argv) {

  ros::init(argc, argv, "target_dispatcher");
  ros::NodeHandle nh;
  Dispenser pathDispenser = Dispenser(nh);

  ros::Rate rate(50);

  while(ros::ok()) {
    ros::spinOnce();
    rate.sleep();
  }
}
