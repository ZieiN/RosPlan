//
// Created by vlad on 21.06.2020.
//

#ifndef HEURISTIC_PLANNER_PATH_H
#define HEURISTIC_PLANNER_PATH_H

#include "Node.h"
#include <stack>
#include <fstream>
#include <string>

#include <rtp_msgs/PathStamped.h>
class Path {
private:
    std::stack <Node> Path;
public:

    void add_node(Node &node);
    void extract_path(const std::string& path_file);

    void clear();
};


#endif //HEURISTIC_PLANNER_PATH_H
