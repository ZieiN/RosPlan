//
// Created by vlad on 21.06.2020.
//

#include "Path.h"

void Path::add_node(Node &node) {
    Path.push(node);
}

void Path::extract_path(const std::string& path_file) {
    std::ofstream path;
    path.open(path_file);
    int x_path, y_path;
    int range = Path.size();
    for (int i = 0; i < range; ++i){
        x_path = Path.top().getCoordinates().first;
        y_path = Path.top().getCoordinates().second;
        Path.pop();
        path <<  x_path << " " << y_path << "\n";
    }
    path.close();

}

void Path::clear() {
    Path = std::stack <Node> ();
}

