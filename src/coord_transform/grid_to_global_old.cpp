#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseArray.h>
#include <stdlib.h>
#include <cmath>

const double SIZE_CELL {1.5};

//This node transforms global coordinates from input "input_grid_coord" to grid coordinates and publish in "output_global_coord"
class coordTransform{
private:
  ros::Subscriber sub;
  ros::Publisher pub;

public:
  coordTransform(ros::NodeHandle &nh);
  /*
  TODO:
  pathTransform
  */
  void transform(const geometry_msgs::PoseArray::ConstPtr& gridCoordArray);
};

coordTransform::coordTransform(ros::NodeHandle &nh){
    sub = nh.subscribe<geometry_msgs::PoseArray>("input_grid_coord", 50, &coordTransform::transform, this);
    pub = nh.advertise<geometry_msgs::PoseArray>("output_global_coord", 50);
}

void coordTransform::transform(const geometry_msgs::PoseArray::ConstPtr& gridCoordArray){
  geometry_msgs::Pose outputGlobalCoord;
  geometry_msgs::PoseArray outputGlobalCoordArray;
  for (auto gridCoord : gridCoordArray->poses){
    outputGlobalCoord.position.x = std::round(SIZE_CELL*(gridCoord.position.x) - SIZE_CELL);
    outputGlobalCoord.position.y = std::round(SIZE_CELL - SIZE_CELL*(gridCoord.position.y));
    outputGlobalCoord.position.z = 0;
    outputGlobalCoordArray.poses.push_back(outputGlobalCoord);
  }
  pub.publish(outputGlobalCoordArray);
}


int main(int argc, char **argv) {
  //Initializes ROS, and sets up a node
  ros::init(argc, argv, "grid_to_global");
  ros::NodeHandle nh;
  //ros::NodeHandle nh_g_to_gr;
  coordTransform Transformer_to_Global = coordTransform(nh);
  //Sets the loop to publish at a rate of 50Hz
  ros::Rate rate(50);

  while(ros::ok()) {
    //Spins to call message callbacks
    ros::spinOnce();
    //Delays until it is time to send another message
    rate.sleep();
  }
}
