#include <ros/ros.h>

#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/Bool.h>

#include <ros/console.h>

#include <stdlib.h>
#include <cmath>
#include "Pid.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>
#include <unistd.h>
using namespace std::chrono;
//Constants:
const double MAX_LINEAR_SPEED {0.5};
const double MAX_ANGULAR_SPEED {0.3};
const double PI_NUM {3.1415926535};
float cut (double a){
  if (abs(a) > MAX_ANGULAR_SPEED) return a*MAX_ANGULAR_SPEED/abs(a);
}

class Driver {
private:
  ros::Publisher pub;
  ros::Publisher arv;
  ros::Subscriber pos;
  ros::Subscriber trg;
  ros::Subscriber act;
  geometry_msgs::Twist spd;
  geometry_msgs::Pose robot_pose;
  std_msgs::Bool arrival;
  std::vector<double> direction = {.0, .0};
  std::pair<double, double> target = std::make_pair(0,0);
  PID linearPid = PID(0.016, MAX_LINEAR_SPEED, -MAX_LINEAR_SPEED, 0.1, 0.01, 0.5); //TODODODODOD
  PID angularPid = PID(0.016, MAX_ANGULAR_SPEED, -MAX_ANGULAR_SPEED, 2, 0.01, 0.001);
  double distance = 0;
  double signed_distance = 0;
  double delta_thetta = 0;
  bool driving = false;
public:
  Driver(ros::NodeHandle& nh);
  void set_pose(const geometry_msgs::Pose::ConstPtr& HuskyPoseMsg);
  void set_target(const geometry_msgs::Pose::ConstPtr& targetMsg);
  void action(const std_msgs::String::ConstPtr& actionMsg);
  void calc_direction();
  bool check_error();
  void calc_distance();
  void calc_thetta();
  void define_speed();
  void drive();

};



Driver::Driver(ros::NodeHandle& nh){
  pub = nh.advertise<geometry_msgs::Twist>("set_model_velocity", 50);
  arv = nh.advertise<std_msgs::Bool>("arrival", 50);
  pos = nh.subscribe<geometry_msgs::Pose>("husky_pose", 50, &Driver::set_pose, this);
  trg = nh.subscribe<geometry_msgs::Pose>("set_target", 50, &Driver::set_target, this);
  act = nh.subscribe<std_msgs::String>("action", 50, &Driver::action, this);
  arrival.data = true;
}

void Driver::set_pose(const geometry_msgs::Pose::ConstPtr& HuskyPoseMsg){
  robot_pose = *HuskyPoseMsg;
}

void Driver::set_target(const geometry_msgs::Pose::ConstPtr& targetMsg){
  target.first = targetMsg->position.x;
  target.second = targetMsg->position.y;
  arrival.data = false;
  driving = true;
}

void Driver::action(const std_msgs::String::ConstPtr& actionMsg){
  if (actionMsg->data == "status-driver"){
    ROS_INFO_STREAM("Driver status:");
    if (driving == true){
      ROS_INFO_STREAM("DRIVING");
      ROS_INFO_STREAM("Next target is:" << target.first << " " << target.second);
    }
    else{
      ROS_INFO_STREAM("STAND BY");
    }
  }else if (actionMsg->data == "pause"){
    driving = false;
    ROS_INFO_STREAM("Pausing");
  }else if (actionMsg->data == "continue"){
    driving = true;
    ROS_INFO_STREAM("Continuing");
  }else if (actionMsg->data == "stop"){
    ROS_INFO_STREAM("Stopping");
    driving = false;
    arrival.data = true;
    target.first = .0;
    target.second = .0;
  }
}

//check_error returns true if robot is too far from the target
bool Driver::check_error(){
  if (((robot_pose.position.x - target.first)*(robot_pose.position.x - target.first)+(robot_pose.position.y - target.second)*(robot_pose.position.y - target.second)) >= 0.02) {
      return true;
    }
  else return false;
}

//fills 2D-vector "direction"
void Driver::calc_direction(){
    direction[0] = target.first  - robot_pose.position.x;
    direction[1] = target.second - robot_pose.position.y;
}

void Driver::calc_distance(){
  distance = pow(direction[0]*direction[0]+direction[1]*direction[1], 0.5);
}

void Driver::calc_thetta(){
  ROS_INFO_STREAM("direction angle = " << acos(direction[0]/distance)*direction[1]/abs(direction[1]) << " robot angle = " << 2*asin(robot_pose.orientation.z));
  double direction_angle = acos(direction[0]/distance)*direction[1]/abs(direction[1]);
  double robot_angle = acos(robot_pose.orientation.w*robot_pose.orientation.w - robot_pose.orientation.z*robot_pose.orientation.z);
  robot_angle =  (robot_pose.orientation.z*robot_pose.orientation.w > 0 ? 1: -1)*robot_angle;
  delta_thetta = direction_angle - robot_angle;
  if(abs(delta_thetta) > PI_NUM) delta_thetta = (delta_thetta > 0 ? -1 : 1) * (2*PI_NUM - abs(delta_thetta));
}



void Driver::define_speed(){
  calc_direction();
  calc_distance();
  calc_thetta();
  signed_distance = (abs(delta_thetta) < PI_NUM ? distance : -distance);
  //std::cout << direction[0] << "   " << direction[1] << "   " << delta_thetta << std::endl;
  //Сначала доворачиваемся на нужный угол
  //делаем это циклом while с моментом времени из chrono
  //если довернулись - продолжаем движение
  /*
  if(distance > 0.2){
    if(abs(delta_thetta) > 0.05){
      linearPid.reset();
      spd.linear.x = 0;
      spd.angular.z = -angularPid.calculate(0, delta_thetta);
    }else{
      angularPid.reset();
      spd.linear.x  = -linearPid.calculate(0, signed_distance);
      spd.angular.z = 0;
    }
  }else{
    angularPid.reset();
    linearPid.reset();
    arrival.data = true;
    arv.publish(arrival);
    driving = false;
    spd.angular.z = .0;
    spd.linear.x = .0;
  }
  */
  /*
  if(distance > 0.2){
    spd.linear.x  = MAX_LINEAR_SPEED * tanh(distance * cos(delta_thetta));
    spd.angular.z = 0.5 * delta_thetta + MAX_LINEAR_SPEED*tanh(distance)*sin(2*delta_thetta) / (2*distance);
  }else{
    arrival.data = true;
    driving = false;
    spd.angular.z = .0;
    spd.linear.x = .0;
  }
  pub.publish(spd);
  */

  if(distance > 0.2){
    if(abs(delta_thetta) > 0.2){
      spd.linear.x = 0;
      spd.angular.z = cut(0.3*delta_thetta/abs(delta_thetta) + 0.5*delta_thetta);
    }else{
      spd.linear.x  = MAX_LINEAR_SPEED * tanh(distance * cos(delta_thetta));
      spd.angular.z = cut(0.5 * delta_thetta + MAX_LINEAR_SPEED*tanh(distance)*sin(2*delta_thetta) / (2*distance));
    }
  }else{
    arrival.data = true;
    driving = false;
    spd.angular.z = .0;
    spd.linear.x = .0;
  }
  ROS_INFO_STREAM("distance: "<< distance << "; " << "thetta: " << delta_thetta);
  pub.publish(spd);

}

void Driver::drive(){
  arv.publish(arrival);
  if (driving) define_speed();
}



int main(int argc, char **argv) {
  ros::init(argc, argv, "husky_target_driver");
  ros::NodeHandle nh;

  Driver Husky_driver = Driver(nh);

  ros::Rate rate(50);

  while(ros::ok()) {
    Husky_driver.drive();
    ros::spinOnce();
    rate.sleep();
  }
}
