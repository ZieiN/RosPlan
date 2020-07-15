#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <gazebo_msgs/ModelStates.h>
#include <stdlib.h>

class NexusVelocitySetter{
private:
    ros::Subscriber velSub;
    ros::Publisher  velPub;
public:
    NexusVelocitySetter(ros::NodeHandle &nh);
    void setVelocity(const geometry_msgs::Twist::ConstPtr& velocity);
};

NexusVelocitySetter::NexusVelocitySetter(ros::NodeHandle &nh){
  velSub = nh.subscribe<geometry_msgs::Twist>("set_model_velocity", 50, &NexusVelocitySetter::setVelocity, this);
  velPub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 10);
}

void NexusVelocitySetter::setVelocity(const geometry_msgs::Twist::ConstPtr& velocity){
    velPub.publish(*velocity);
}

int main(int argc, char **argv){
  ros::init(argc, argv, "nexus_velocity");
  ros::NodeHandle nh;

  NexusVelocitySetter setter = NexusVelocitySetter(nh);

  ros::Rate rate = ros::Rate(50);

  while(ros::ok()){
    ros::spinOnce();
    rate.sleep();
  }
}
