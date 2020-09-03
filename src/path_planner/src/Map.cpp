//
// Created by vlad on 21.06.2020.
//

#include "Map.h"


Map::Map(const std::string &address) {

    std::ifstream maze;                                                                                                 //Text file with map
    maze.open(address + "/grid.txt");
    maze >> sizeX >> sizeY;
    maze >> resolution;
    maze >> origin[0] >> origin[1] >> origin[2];
    occupancyGrid = std::vector <std::vector <bool> > (sizeX, std::vector <bool> (sizeY));
    int b;
    for (int i = 0; i < sizeX; ++i){                                                                                   //coordinates and states of nodes
        for(int j = 0; j < sizeY; ++j){
            maze >> b;
            occupancyGrid[i][j] = b == 100;
        };
    };
    maze.close();

    maze.open(address + "/heightMap.txt");
    heightMap = std::vector <std::vector <int> > (sizeX, std::vector <int> (sizeY));
    for (int i = 0; i < sizeX; ++i){                                                                                   //coordinates and states of nodes
        for(int j = 0; j < sizeY; ++j){
            maze >> b;
            heightMap[i][j] = int(b);
        };
    };
    maze.close();
}

bool Map::getOccupancy(std::pair<int, int> const &coordinates) {
    return occupancyGrid[coordinates.first][coordinates.second];
}

double Map::getHeightCost(const std::pair<int, int> &one, const std::pair<int, int> &two, double &dist) {
    int heightDifference = heightMap[two.first][two.second] - heightMap[one.first][one.second];
    if (heightDifference < 0) return 1;
    else return 1 + 0.3 * (heightDifference * dist / 10);
}


