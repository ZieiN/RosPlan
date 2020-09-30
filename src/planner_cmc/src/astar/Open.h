//
// Created by vlad on 18.06.2020.
//

#ifndef HEURISTIC_PLANNER_OPEN_H
#define HEURISTIC_PLANNER_OPEN_H

#include "set"
#include "unordered_set"
#include "Node.h"
#include <iostream>

struct comparator{
    using is_transparent = int;

    bool operator()(const Node& m, const Node& n) const{
        if (m.getF() < n.getF()){
            return true;
        }else if(m.getF() > n.getF()){
            return false;
        }else if(m.getG() < n.getG()){
            return true;
        }else if(m.getG() > n.getG()){
            return false;
        }else if(m.getCoordinates().first < n.getCoordinates().second){
            return true;
        }else if(m.getCoordinates().first > n.getCoordinates().second){
            return false;
        }else return m.getCoordinates().second < n.getCoordinates().second;
    }
};

class Open {
private:
    std::set <Node, comparator> openContainer;
    std::unordered_set <int> openID;
public:
    void insertNode(Node &node);
    void insertId(int id);
    void erase_node(std::set <Node>::iterator it);
    std::set<Node>::iterator findNode(Node &node);
    Node getNode(std::set<Node>::iterator it);
    Node pop();

    void log(std::string typeLog);
    int size();
    std::set<Node>::iterator end();
    void clear();
};


#endif //HEURISTIC_PLANNER_OPEN_H
