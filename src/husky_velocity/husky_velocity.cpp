#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <gazebo_msgs/ModelStates.h>
#include <stdlib.h>

class HuskyVelocitySetter{
private:
    ros::Subscriber velSub;
    ros::Publisher  velPub;
public:
    HuskyVelocitySetter(ros::NodeHandle &nh);
    void setVelocity(const geometry_msgs::Twist::ConstPtr& velocity);
};

HuskyVelocitySetter::HuskyVelocitySetter(ros::NodeHandle &nh){
  velSub = nh.subscribe<geometry_msgs::Twist>("set_model_velocity", 50, &HuskyVelocitySetter::setVelocity, this);
  velPub = nh.advertise<geometry_msgs::Twist>("husky_velocity_controller/cmd_vel", 50);
}

void HuskyVelocitySetter::setVelocity(const geometry_msgs::Twist::ConstPtr& velocity){
    velPub.publish(*velocity);
}

int main(int argc, char **argv){
  ros::init(argc, argv, "husky_velocity");
  ros::NodeHandle nh;

  HuskyVelocitySetter setter = HuskyVelocitySetter(nh);

  ros::Rate rate = ros::Rate(50);

  while(ros::ok()){
    ros::spinOnce();
    rate.sleep();
  }
}
