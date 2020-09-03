//
// Created by vlad on 21.06.2020.
//

#include "A_search.h"
#define SQRT2 1.4142135623


A_search::A_search(double hWeight_, int metricType_) : hWeight(hWeight_), metricType(metricType_) {}

bool A_search::ok() {
    return (goal_is_not_reached && (open.size() != 0));
}

double A_search::computeCost(Node &one, Node& two, Map &occupancyMap) {
    int dx = one.getCoordinates().first - two.getCoordinates().first;
    int dy = one.getCoordinates().second - two.getCoordinates().second;
    double dist = std::abs(dx*dy)>0 ? SQRT2*occupancyMap.resolution : occupancyMap.resolution;
    double heightScale = occupancyMap.getHeightCost(one.getCoordinates(), two.getCoordinates(), dist);
    return dist * heightScale;
}

double A_search::hCalc(Node &cur, Node &goal) {
    switch (metricType){
        case 1://euclidean
            return hWeight * hypot(abs(cur.getCoordinates().first - goal.getCoordinates().first), abs(cur.getCoordinates().second - goal.getCoordinates().second));
        case 2://manhattan
            return hWeight* (abs(cur.getCoordinates().first - goal.getCoordinates().first) + abs(cur.getCoordinates().second - goal.getCoordinates().second));
        case 3://chebyshev
            return hWeight * fmax(abs(cur.getCoordinates().first - goal.getCoordinates().first), abs(cur.getCoordinates().second - goal.getCoordinates().second));
        case 4://diagonal
            return hWeight * (abs(cur.getCoordinates().first - goal.getCoordinates().first) + abs(cur.getCoordinates().second - goal.getCoordinates().second) + (sqrt(2) - 2) * fmin(abs(cur.getCoordinates().first - goal.getCoordinates().first), abs(cur.getCoordinates().second - goal.getCoordinates().second)));
        default://dijkstra
            return 0;
    }
}

double A_search::gCalc(Node &predecessor, Node &successor, Map &occupancyMap) {
    return  predecessor.getG() + computeCost(predecessor, successor, occupancyMap);
}

double A_search::fCalc(double const &g, double const &h) {
    return g+h;
}

std::list<Node> A_search::getSuccessors(Node *current, Node &goal, Map &occupancyMap) {
    int x = (*current).getCoordinates().first;
    int y = (*current).getCoordinates().second;

    std::list <Node> successors;

    for (int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if ((i+j)%2 == 1){ //for horizontal or vertical move
                if (!occupancyMap.getOccupancy(std::make_pair (x - 1 + i, y - 1 + j))){
                    Node tmp = Node(x-1+i, y-1+j, (y-1+j)*occupancyMap.sizeX + (x-1+i) );
                    if(!closed.isIn(tmp.getId())) {
                        tmp.setH(hCalc(tmp, goal));
                        tmp.setG(gCalc(*current,tmp, occupancyMap));
                        tmp.setF(fCalc(tmp.getG(), tmp.getH()));
                        tmp.Pred = current;
                        successors.push_back(tmp);
                    }
                }
            }else if ((i*j) != 1){//except node itself
                if(allowDiagonal){//if this flag is false there is no reason to check diagonal nodes
                    if (!occupancyMap.getOccupancy(std::make_pair(x - 1 + i, y - 1 + j))){
                        if(cutCorners){
                            if(allowSqueeze){
                                Node tmp = Node(x-1+i, y-1+j, (y-1+j)*occupancyMap.sizeX + (x-1+i) );
                                if(!closed.isIn(tmp.getId())) {
                                    tmp.setH(hCalc(tmp, goal));
                                    tmp.setG(gCalc(*current,tmp, occupancyMap));
                                    tmp.setF(fCalc(tmp.getG(), tmp.getH()));
                                    tmp.Pred = current;
                                    successors.push_back(tmp);
                                }
                            }else{ //if allowSqueeze = false
                                //remember, that 'i' and 'j' point to diagonal nodes
                                if (!occupancyMap.getOccupancy(std::make_pair(x - i, y-(j-(j-1)%2))) &&
                                    !occupancyMap.getOccupancy(std::make_pair(x - (i-(i-1)%2), y-j))){ //only if both side nodes are accessible we go
                                    Node tmp = Node(x-1+i, y-1+j, (y-1+j)*occupancyMap.sizeX + (x-1+i) );
                                    if(!closed.isIn(tmp.getId())) {
                                        tmp.setH(hCalc(tmp, goal));
                                        tmp.setG(gCalc(*current,tmp, occupancyMap));
                                        tmp.setF(fCalc(tmp.getG(), tmp.getH()));
                                        tmp.Pred = current;
                                        successors.push_back(tmp);
                                    }
                                }
                            }
                        }else{ //if cutCorners = false
                            if (!occupancyMap.getOccupancy(std::make_pair(x - i, y-(j-(j-1)%2))) ||
                                !occupancyMap.getOccupancy(std::make_pair(x - (i-(i-1)%2), y - j))){ //if one side node is accessible we go
                                Node tmp = Node(x-1+i, y-1+j, (y-1+j)*occupancyMap.sizeX + (x-1+i) );
                                if(!closed.isIn(tmp.getId())) {
                                    tmp.setH(hCalc(tmp, goal));
                                    tmp.setG(gCalc(*current,tmp, occupancyMap));
                                    tmp.setF(fCalc(tmp.getG(), tmp.getH()));
                                    tmp.Pred = current;
                                    successors.push_back(tmp);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return successors;

}

void A_search::updateOpen(Node &new_node, Node *Pred) {
    auto open_iterator = open.findNode(new_node);
    open.insertId(new_node.getId());//Возможно совместить с методом insertNode

    if (open_iterator != open.end()) {
        Node tmp = open.getNode(open_iterator);

        if (tmp.Pred->getG() > (*Pred).getG()) {
            tmp.Pred = Pred;
        }
        tmp.checkG(new_node.getG());
        open.insertNode(tmp);
    } else {
        //remove new
        new_node.Pred = new Node;
        new_node.Pred = Pred;
        open.insertNode(new_node);
    }
}


void A_search::search(Node &start, Node &goal, Map &occupancyMap) {
    iterations = 0;
    Node successor_node;
    std::list <Node> successors;
    Node *pred;
    open.insertNode(start);
    while (ok()) {
        successor_node = open.pop();
        if (successor_node == goal) {
            iterations++;
            goal_is_not_reached = false;
            closed.insertNode(successor_node);
            address_of_goal_node = closed.findNode(successor_node.getId());
            continue;
        }

        std::cout << "Currently working on :  " << successor_node.getCoordinates().first << "  "
                                                << successor_node.getCoordinates().second << std::endl;
        open.log("size");

        closed.insertNode(successor_node);
        pred = &closed.findNode(successor_node.getId())->second;                                                       //Maybe better return NODE or *NODE

        successors = getSuccessors(pred, goal, occupancyMap);

        for (auto & successor : successors){
            updateOpen(successor, pred);
        }

        iterations++;
    }
    //todo: return !goal_is_not_reached;
}

void A_search::create_path(Node &start) {
    std::cout << "started creating path" << std::endl;
    if(!goal_is_not_reached){
        Node path_node = (*address_of_goal_node).second;
        Node path_node_next;
        path.add_node(path_node);
        bool pathNotComplete = true;


        while(pathNotComplete){
            path_node_next = *(path_node.Pred);
            if (path_node_next ==  start){
                pathNotComplete = false;
                path.add_node(start);
                continue;
            }
            else{
                path.add_node(path_node_next);
                path_node = path_node_next;
            }
        }
    }
    else{
        std::cout << "ERROR: Goal was not reached during working" << std::endl;
    }

}


void A_search::extract_path(const std::string& path_file) {
    path.extract_path(path_file);
}

void A_search::clear() {
    open.clear();
    closed.clear();
    path.clear();
    goal_is_not_reached = true;
    iterations = 0;
}

A_search::A_search(double hWeight, int metricType, bool allowDiagonal, bool cutCorners, bool allowSqueeze,
                   bool breakingTies) : hWeight(hWeight), metricType(metricType), allowDiagonal(allowDiagonal),
                                        cutCorners(cutCorners), allowSqueeze(allowSqueeze),
                                        breakingTies(breakingTies){}
