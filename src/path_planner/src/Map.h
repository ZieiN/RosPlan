//
// Created by vlad on 21.06.2020.
//

#ifndef HEURISTIC_PLANNER_MAP_H
#define HEURISTIC_PLANNER_MAP_H

#include <string>
#include <vector>
#include <fstream>
#include "Node.h"

class Map {
private:
    std::vector <std::vector <bool> > occupancyGrid;
    std::vector <std::vector <int> > heightMap;
    std::vector <float>  origin = {0,0,0};

public:
    float resolution;
    //Map(ros::nav_msgs::OccupancyGrid::ConstPtr& grid);
    Map(const std::string &address);
    int sizeX, sizeY; //add getters
    bool getOccupancy(std::pair<int, int> const &coordinates);
    double getHeightCost(std::pair<int, int> const &one, std::pair<int, int> const &two, double &dist);
};


#endif //HEURISTIC_PLANNER_MAP_H
