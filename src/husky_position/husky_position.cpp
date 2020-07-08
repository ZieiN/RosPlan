#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <gazebo_msgs/ModelStates.h>
#include <stdlib.h>

const std::string HuskyModelName = "husky";

class HuskyPathGetter{
private:
    ros::Subscriber poseSub;
    ros::Publisher  posePub;
    geometry_msgs::Pose poseHusky;
public:
    HuskyPathGetter(ros::NodeHandle &nh);
    void getPath(const gazebo_msgs::ModelStates::ConstPtr& statesMsg);
};

HuskyPathGetter::HuskyPathGetter(ros::NodeHandle &nh){
  poseSub = nh.subscribe<gazebo_msgs::ModelStates>("gazebo/model_states", 50, &HuskyPathGetter::getPath, this);
  posePub = nh.advertise<geometry_msgs::Pose>("husky_pose", 50);
}

void HuskyPathGetter::getPath(const gazebo_msgs::ModelStates::ConstPtr& statesMsg){
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

  HuskyPathGetter getter = HuskyPathGetter(nh);

  ros::Rate rate = ros::Rate(50);

  while(ros::ok()){
    ros::spinOnce();
    rate.sleep();
  }
}
