#include <ros/ros.h>
#include <coord_transform/coords.h>
#include <stdlib.h>


/*
req.input.position  - coordinates in grid system
req.info            - grid info (resolution, origin)

res.output          - coordinates in global system
*/
bool transform(coord_transform::coords::Request  &req,
              coord_transform::coords::Response &res){
  res.output.position.x = req.info.resolution*req.input.position.x + req.info.origin.position.x;
  res.output.position.y = req.info.origin.position.y - req.info.resolution*req.input.position.y;
  res.output.position.z = 0;
  return true;
}




int main(int argc, char **argv) {
  //Initializes ROS, and sets up a node
  ros::init(argc, argv, "grid_to_global_server");
  ros::NodeHandle nh;
  ros::ServiceServer service = nh.advertiseService("grid_to_global", transform);
  ros::spin();
}
