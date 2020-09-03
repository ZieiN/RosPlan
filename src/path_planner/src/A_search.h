//
// Created by vlad on 21.06.2020.
//

#ifndef HEURISTIC_PLANNER_A_SEARCH_H
#define HEURISTIC_PLANNER_A_SEARCH_H

#include "Node.h"
#include "Open.h"
#include "Closed.h"
#include "Map.h"
#include "Path.h"

class A_search {
private:
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
    double hWeight;
    int metricType;
    bool allowDiagonal = true;
    bool cutCorners = true;
    bool allowSqueeze = true;
    bool breakingTies = true; // check if it works by default
    Closed closed;
    Open open;
    bool goal_is_not_reached = true;
    Path path;
    //logs
    int iterations = 0;
    std::unordered_map <int, class Node>::iterator address_of_goal_node;
public:
    A_search(double hWeight_, int metricType_);

    A_search(double hWeight, int metricType, bool allowDiagonal, bool cutCorners, bool allowSqueeze, bool breakingTies);

    bool ok();

    double computeCost(Node &one, Node &two, Map &occupancyMap);
    double hCalc(Node &cur, Node &goal);
    double gCalc(Node &predecessor, Node &successor, Map &occupancyMap);
    double fCalc(double const &g, double const &h);

    std::list<Node> getSuccessors(Node* current, Node &goal, Map &occupancyMap);
    void updateOpen(Node &new_node, Node *Pred);
    void search(Node &start, Node &goal, Map &occupancyMap);
    void clear();
    void create_path(Node &start);
    void extract_path(const std::string &path_file);



};


#endif //HEURISTIC_PLANNER_A_SEARCH_H
