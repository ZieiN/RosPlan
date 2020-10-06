//
// Created by vlad on 17.09.2020.
//
#include <ros/ros.h>
#include <ros/console.h>
#include <vector>
#include <queue>
using namespace std;


class Node{
public:
    int x, y, father;
    double gcost, hcost;
    Node(){
        x=y=father=gcost=hcost=0;
    }
    Node(int x, int y, int father, double gcost, double hcost):x(x), y(y), father(father), gcost(gcost), hcost(hcost){}
};

vector< vector<bool> > Map(nav_msgs::OccupancyGrid &grid){
    int height = 600, width = 600;
    vector<vector<bool>>v;
    v.resize(height);
    for(int i=0; i<height; ++i){
        for(int j=0; j<width; ++j){
            v[i].push_back(grid.data[i*height + j] > 40);
        }
    }
    return v;
}

bool operator < (Node a, Node b){
    if (a.gcost + a.hcost == b.gcost + b.hcost)
        return a.hcost > b.hcost;
    return a.gcost + a.hcost > b.gcost + b.hcost;
}

void Asearch(nav_msgs::OccupancyGrid &grid, geometry_msgs::Point& startPoint, geometry_msgs::Point& goalPoint, rtp_msgs::PathStamped& path){
    auto mp = Map(grid);
    int stx = startPoint.x;
    int sty = startPoint.y;
    int ndx = goalPoint.x;
    int ndy = goalPoint.y;
    priority_queue<Node> q;
    int x, y, father;
    double gcost, hcost;
    vector<vector<bool>> vis(mp.size(), vector<bool>(mp[0].size(), false));
    vector<Node> closed;
    int dx[8] = {0, 0, 1, 1, 1, -1, -1, -1}, dy[8] = {1, -1, 0, 1, -1, 0, 1, -1};
    q.push(Node(stx, sty, -1, 0, hypot(stx-ndx, sty-ndy)));
    if(mp[stx][sty] || mp[ndx][ndy]){
        return;
    }
    while(!q.empty()){
        auto top = q.top();
        q.pop();
        x = top.x; y = top.y; gcost = top.gcost; hcost = top.hcost, father = top.father;
        if(x == ndx && y == ndy){
            rtp_msgs::PathPointWithMetadata path_point;
            while(x != stx || y != sty){
                path_point.pose.position.x = x;
                path_point.pose.position.y = y;
                path.path_points_with_metadata.push_back(path_point);
                x = closed[father].x;
                y = closed[father].y;
                father = closed[father].father;
            }
            path_point.pose.position.x = x;
            path_point.pose.position.y = y;
            path.path_points_with_metadata.push_back(path_point);
            break;
        }
        if(vis[x][y])
            continue;
        vis[x][y]=true;
        closed.push_back(top);
        father = (int)(closed.size())-1;
        for(int i=0; i<8; ++i){
            auto x_tmp = x + dx[i];
            auto y_tmp = y + dy[i];
            if(x_tmp < 0 || x_tmp >= mp.size() || y_tmp < 0 || y_tmp >= mp[0].size())
                continue;
            if(mp[x_tmp][y_tmp]){
                continue;
            }
            auto gcost_tmp = gcost + hypot(x-x_tmp, y-y_tmp);
            auto hcost_tmp = hypot(x_tmp-ndx, y_tmp-ndy);
            q.push(Node(x_tmp, y_tmp, father, gcost_tmp, hcost_tmp));
        }
    }
}

void fill_path(rtp_msgs::PathStamped& path){
    for(int i=0; i<path.path_points_with_metadata.size(); ++i){
        path.path_points_with_metadata[i].metadata.linear_velocity = 2.0;
        path.path_points_with_metadata[i].metadata.key_point = true;
        path.path_points_with_metadata[i].metadata.return_point = true;
        path.path_points_with_metadata[i].metadata.confirmation_point = true;
        path.path_points_with_metadata[i].pose.orientation.w = 1;
    }
}

void search(nav_msgs::OccupancyGrid &grid, geometry_msgs::Point& startPoint, geometry_msgs::Point& goalPoint, rtp_msgs::PathStamped& path){
    path.path_points_with_metadata.clear();
    Asearch(grid, startPoint, goalPoint, path);
    fill_path(path);
}









