//
// Created by vlad on 18.06.2020.
//

#include "Closed.h"

void Closed::insertNode(Node &node) {
    Closed.insert(std::make_pair(node.getId(), node));
}

std::unordered_map <int, Node>::iterator  Closed::findNode(int id) {
    return Closed.find(id);
}

void Closed::output(){
    std::cout << "CLOSED is: ";
    if (Closed.empty()) std::cout << "EMPTY" << std::endl;
    for (auto it : Closed)
    {
        std::cout << "(" << it.second.getCoordinates().first << ", "
                         << it.second.getCoordinates().second << ") ";
    }
    std::cout << std::endl;
}

bool Closed::isIn(int id) {
    return findNode(id) != Closed.end();
}

void Closed::clear() {
    Closed.clear();
}
