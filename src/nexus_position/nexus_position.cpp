#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <gazebo_msgs/ModelStates.h>
#include <stdlib.h>

const std::string NexusModelName = "turtlebot3_waffle";

class NexusPoseGetter{
private:
    ros::Subscriber poseSub;
    ros::Publisher  posePub;
    geometry_msgs::Pose poseNexus;
public:
    NexusPoseGetter(ros::NodeHandle &nh);
    void getPose(const gazebo_msgs::ModelStates::ConstPtr& statesMsg);
};

NexusPoseGetter::NexusPoseGetter(ros::NodeHandle &nh){
  poseSub = nh.subscribe<gazebo_msgs::ModelStates>("gazebo/model_states", 50, &NexusPoseGetter::getPose, this);
  posePub = nh.advertise<geometry_msgs::Pose>("robot_pose", 50);
}

void NexusPoseGetter::getPose(const gazebo_msgs::ModelStates::ConstPtr& statesMsg){
  int i = 0;
  for (auto modelName : statesMsg->name){
    if (modelName == NexusModelName) break;
    ++i;
  }
  poseNexus = (statesMsg->pose)[i];
  posePub.publish(poseNexus);
}

int main(int argc, char **argv){
  ros::init(argc, argv, "nexus_position");
  ros::NodeHandle nh;

  NexusPoseGetter getter = NexusPoseGetter(nh);

  ros::Rate rate = ros::Rate(50);

  while(ros::ok()){
    ros::spinOnce();
    rate.sleep();
  }
}
