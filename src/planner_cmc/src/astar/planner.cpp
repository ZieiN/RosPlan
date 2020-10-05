//
// Created by vlad on 17.09.2020.
//
#include <ros/ros.h>
#include <ros/console.h>
#include "A_search.h"


#define euclidean 1
#define manhattan 2
#define chebyshev 3
#define diagonal 4

/*Parameters
 * hWeight - coefficient
 * metricType - chosen type of heuristic
 *      1:euclidean
 *      2:manhattan
 *      3:chebyshev
 *      4:diagonal
 * allowDiagonal - allows or permits moving to diagonal nodes
 * cutCorners - allows or permits moving to diagonal node if one of the side node is blocked
 * allowSqueeze - allows or permits moving to diagonal node if both of the side node is blocked
 * breakingTies - defines order of opening the nodes when f-value is equal: g-min(false) or g-max(true)
 */


//todo: you may override this func to implement your algorithm
void search(nav_msgs::OccupancyGrid &grid, geometry_msgs::Point& startPoint, geometry_msgs::Point& goalPoint, rtp_msgs::PathStamped& path){
    ROS_INFO_STREAM("starting");
    A_search seeker = A_search(1.0, euclidean, true, true, true, true);
    Map occupancyMap = Map(grid);
    Node start(startPoint.x, startPoint.y, grid.info.height*startPoint.y + startPoint.x);
    Node goal(goalPoint.x, goalPoint.y, grid.info.height*goalPoint.y + goalPoint.x);
    seeker.search(start, goal, occupancyMap);
    seeker.create_path(startPoint, path);
    seeker.clear();
    ROS_INFO_STREAM("end of planning");
    ROS_INFO_STREAM(path);
}









