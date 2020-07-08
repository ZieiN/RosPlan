#include <ros/ros.h>
#include <coord_transform/coords.h>
#include <stdlib.h>
#include <cmath>

/*
req.input.position  - coordinates in global system
req.info            - grid info (resolution, origin)

res.output          - coordinates in grid system
*/
bool transform(coord_transform::coords::Request  &req,
              coord_transform::coords::Response &res){
  res.output.position.x = std::round((req.input.position.x - req.info.origin.position.x)/req.info.resolution);
  res.output.position.y = std::round((req.info.origin.position.y - req.input.position.y)/req.info.resolution);
  res.output.position.z = 0;
  return true;
}




int main(int argc, char **argv) {
  //Initializes ROS, and sets up a node
  ros::init(argc, argv, "global_to_grid_server");
  ros::NodeHandle nh;
  ros::ServiceServer service = nh.advertiseService("global_to_grid", transform);
  ros::spin();
}
