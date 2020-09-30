#include "A_search.h"
const int numTasks(100);

std::vector <std::pair<std::pair<int,int>, std::pair<int,int>>> generateTasks(int num, Map occupancyMap){
    int x(0),y(0);
    std::pair <int, int> start;
    std::pair <int, int> goal;
    std::vector <std::pair<std::pair<int,int>, std::pair<int,int> > > tasks;
    srand(432312);
    for (int i = 0; i < num; ++i) {
        do{
            x = rand() % occupancyMap.sizeX;
            y = rand() % occupancyMap.sizeY;
        }while(occupancyMap.getOccupancy(std::make_pair(x, y)));
        start = std::make_pair(x, y);
        do{
            x = rand() % occupancyMap.sizeX;
            y = rand() % occupancyMap.sizeY;
        }while(occupancyMap.getOccupancy(std::make_pair(x, y)));
        goal = std::make_pair(x, y);
        tasks.emplace_back(start, goal);
    }
    return tasks;
}
#define euclidean 1
#define manhattan 2
#define chebyshev 3
#define diagonal 4

int main() {
    A_search seeker = A_search(1.0, euclidean, true, true, true, true);
    Map occupancyMap = Map("/home/vlad/CLionProjects/Heuristic-planner/maps/1");
    auto tasks = generateTasks(numTasks, occupancyMap);
    int i = 0;
    std::string pathToPathFolder = "/home/vlad/CLionProjects/Heuristic-planner/maps/1/res/";
    for (auto task : tasks) {
        ++i;
        Node start(task.first.first, task.first.second, task.first.second*occupancyMap.sizeX + task.first.first);
        Node goal(task.second.first, task.second.second, task.second.second*occupancyMap.sizeX + task.second.first);
        seeker.search(start, goal, occupancyMap);
        seeker.create_path(start);
        std::string tmp = pathToPathFolder + std::to_string(i) + ".txt";
        seeker.extract_path(tmp);
        seeker.clear();
    }
    return 0;
}
