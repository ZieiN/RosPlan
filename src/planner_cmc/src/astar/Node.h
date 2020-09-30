//
// Created by vlad on 18.06.2020.
//

#ifndef HEURISTIC_PLANNER_NODE_H
#define HEURISTIC_PLANNER_NODE_H

#include <cmath>
#include <list>

class Node {
private:
    int id{};

    //distance to the start node
    double g{};
    //heuristic distance to the goal node
    double h{};
    //sum of g and h
    double f{};
    std::pair<int, int> coordinates;
public:
    const std::pair<int, int> &getCoordinates() const;

    Node *Pred{};

    double getG() const;

    void setG(double g);

    double getH() const;

    void setH(double h);

    double getF() const;

    void setF(double f);

    int getId() const;

    void setId(int id);

    Node();
    Node(int x, int y, int _id);

    bool operator==(const Node &rhs) const;

    bool operator!=(const Node &rhs) const;

    void checkG (double const &newG);
};


#endif //HEURISTIC_PLANNER_NODE_H
