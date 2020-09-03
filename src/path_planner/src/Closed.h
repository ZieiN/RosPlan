//
// Created by vlad on 18.06.2020.
//

#ifndef HEURISTIC_PLANNER_CLOSED_H
#define HEURISTIC_PLANNER_CLOSED_H

#include <unordered_map>
#include "Node.h"
#include <iostream>

class Closed {
private:
    std::unordered_map <int, Node> Closed;
public:
    void insertNode(Node &node);
    std::unordered_map <int, Node>::iterator findNode(int id);
    bool isIn(int id);
    void output();
    void clear();
};


#endif //HEURISTIC_PLANNER_CLOSED_H
