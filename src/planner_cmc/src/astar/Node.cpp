//
// Created by vlad on 18.06.2020.
//

#include "Node.h"

double Node::getG() const {
    return g;
}

void Node::setG(double g) {
    Node::g = g;
}

double Node::getH() const {
    return h;
}

void Node::setH(double h) {
    Node::h = h;
}

double Node::getF() const {
    return f;
}

void Node::setF(double f) {
    Node::f = f;
}

int Node::getId() const {
    return id;
}

void Node::setId(int id) {
    Node::id = id;
}

Node::Node() {
    g = 0;
}

Node::Node(int x, int y, int _id) {
    coordinates.first = x;
    coordinates.second = y;
    id = _id;
}

bool Node::operator==(const Node &rhs) const {
    return coordinates == rhs.coordinates;
}

bool Node::operator!=(const Node &rhs) const {
    return !(rhs == *this);
}

void Node::checkG(const double &newG) {
    g = fmin(g, newG);
}

const std::pair<int, int> &Node::getCoordinates() const {
    return coordinates;
}

