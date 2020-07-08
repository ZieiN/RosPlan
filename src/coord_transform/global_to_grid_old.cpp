#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseArray.h>
#include <stdlib.h>

const double SIZE_CELL {1.5};
//This node transforms global coordinates from input "input_global_coord" to grid coordinates and publish in "output_grid_coord"
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
  void transform(const geometry_msgs::PoseArray::ConstPtr& globalCoordArray);
};

coordTransform::coordTransform(ros::NodeHandle &nh){
  sub = nh.subscribe<geometry_msgs::PoseArray>("input_global_coord", 50, &coordTransform::transform, this);
  pub = nh.advertise<geometry_msgs::PoseArray>("output_grid_coord", 50);//set_target_world
}

void coordTransform::transform(const geometry_msgs::PoseArray::ConstPtr& globalCoordArray){
  geometry_msgs::Pose outputGridCoord;
  geometry_msgs::PoseArray outputGridCoordArray;
  for (auto globalCoord : globalCoordArray->poses){
    outputGridCoord.position.x = (globalCoord.position.x+SIZE_CELL)/SIZE_CELL;
    outputGridCoord.position.y = (SIZE_CELL - globalCoord.position.y)/SIZE_CELL;
    outputGridCoord.position.z = 0;

    outputGridCoordArray.poses.push_back(outputGridCoord);
  }
  pub.publish(outputGridCoordArray);
}


int main(int argc, char **argv) {
  //Initializes ROS, and sets up a node
  ros::init(argc, argv, "global_to_grid");
  ros::NodeHandle nh;
  coordTransform Transformer = coordTransform(nh);
  //Sets the loop to publish at a rate of 50Hz
  ros::Rate rate(50);

  while(ros::ok()) {
    //Spins to call message callbacks
    ros::spinOnce();
    //Delays until it is time to send another message
    rate.sleep();
  }
}
