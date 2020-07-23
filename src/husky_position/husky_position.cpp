#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <gazebo_msgs/ModelStates.h>
#include <stdlib.h>

const std::string HuskyModelName = "husky";

class HuskyPoseGetter{
private:
    ros::Subscriber poseSub;
    ros::Publisher  posePub;
    geometry_msgs::Pose poseHusky;
public:
    HuskyPoseGetter(ros::NodeHandle &nh);
    void getPose(const gazebo_msgs::ModelStates::ConstPtr& statesMsg);
};

HuskyPoseGetter::HuskyPoseGetter(ros::NodeHandle &nh){
  poseSub = nh.subscribe<gazebo_msgs::ModelStates>("gazebo/model_states", 50, &HuskyPoseGetter::getPose, this);
  posePub = nh.advertise<geometry_msgs::Pose>("robot_pose", 50);
}

void HuskyPoseGetter::getPose(const gazebo_msgs::ModelStates::ConstPtr& statesMsg){
  int i = 0;
  for (auto modelName : statesMsg->name){
    if (modelName == HuskyModelName) break;
    ++i;
  }
  poseHusky = (statesMsg->pose)[i];
  posePub.publish(poseHusky);
}

int main(int argc, char **argv){
  ros::init(argc, argv, "husky_position");
  ros::NodeHandle nh;

  HuskyPoseGetter getter = HuskyPoseGetter(nh);

  ros::Rate rate = ros::Rate(50);

  while(ros::ok()){
    ros::spinOnce();
    rate.sleep();
  }
}
