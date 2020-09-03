#include <ros/ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseArray.h>
#include <gazebo_msgs/ModelStates.h>
#include <nav_msgs/OccupancyGrid.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <stack>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <iostream>
#include <ros/console.h>
#include <coord_transform/coords.h>

//#include "A_search.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



class NODE {                                                                    //Main class
private:
	/* data */

public:
 int x_coordinate;                                                              //X position of NODE
 int y_coordinate;                                                              //Y position of NODE
 bool is_blocked;                                                               //1 if NODE is blocked - probably useless
 double g;                                                                      //distance to the start NODE
 double h;                                                                      //heuristic distance to the goal NODE
 double f;                                                                      //summ of g and h
 int id;
 NODE();                                                                        //constructors
 NODE(int x, int y);
 NODE *PRED;                                                                    //link to the predecessor




 void id_c(int h){
   id = y_coordinate*h + x_coordinate;
 }
//compute cost
 double compute_cost(NODE &predecessor){                                                   //distance between two nodes
	int dx = x_coordinate - predecessor.x_coordinate;
	int dy = y_coordinate - predecessor.y_coordinate;
	int dd = fabs(dx*dy);
	if (dd > 0) return sqrt(2);                                                   //sqrt(2) in case of diagonal transition
	else return 1;                                                                //1 in case of horizontal/vertical transition
 }

 void g_calc(NODE &predecessor){
	g = predecessor.g + compute_cost(predecessor);
 }

 void h_calc(NODE &goal, double e, int chosen_one){
   switch (chosen_one){
      case 1:
        h = e * hypot(abs(x_coordinate - goal.x_coordinate), abs(y_coordinate - goal.y_coordinate));
        break;
      case 2:
        h = abs(x_coordinate - goal.x_coordinate) + abs(y_coordinate - goal.y_coordinate) + (sqrt(2) - 2)*fmin(abs(x_coordinate - goal.x_coordinate),abs(y_coordinate - goal.y_coordinate));
        h *= e;
        break;
      case 3:
        h = e * fmax(abs(x_coordinate - goal.x_coordinate), abs(y_coordinate - goal.y_coordinate));
        break;
      default:
        h = 0;
        break;
   }
 }


 void f_calc(){
	 f = g+h;
 }

 void check_g (double new_g){
	 g = fmin(g, new_g);
 }

};

NODE::NODE(void){                                                               //NODE constructor
  is_blocked = 0;
  g = 0;
  //PRED = nullptr;
}

NODE::NODE(int x, int y){                                                       //NODE constructor
  is_blocked = 0;
  x_coordinate = x;
  y_coordinate = y;
  //PRED = nullptr;
}

NODE n_start, n_goal;

struct comparator{
  using is_transparent = int;

  bool operator()(const NODE& m, const NODE& n) const{
     if (m.f < n.f){
       return true;
     }else if(m.f > n.f){
       return false;
     }else if(m.g < n.g){
       return true;
     }else if(m.g > n.g){
       return false;
     }else if(m.x_coordinate < n.x_coordinate){
       return true;
     }else if(m.x_coordinate > n.x_coordinate){
       return false;
     }else if(m.y_coordinate < n.y_coordinate){
       return true;
     }else return false;
 }
};

class AStarPlanner{
private:
  double e = 1.0;
  int chosen_one = 1;
  // EUCLID == 1
  // DIAG   == 2
  // CHEB   == 3
  bool equivalent(NODE &one, NODE &two) {                                         //Test for two nodes being same (used for goal and start)
    if ((one.x_coordinate == two.x_coordinate)&&(one.y_coordinate == two.y_coordinate)) return true;
    else return false;
  }
  std::list <NODE> get_successors (NODE *current, std::vector <std::vector <bool> > &map, std::unordered_map <int, class NODE> &CLOSED, int height){
    int x = (*current).x_coordinate;
    int y = (*current).y_coordinate;

    std::list <NODE> successors;
    NODE tmp;

    for (int i = 0; i < 3; ++i){
      for(int j = 0; j < 3; ++j){
        if (!(map[x+i-1][y+j-1])){
          tmp.x_coordinate = x+i-1;
          tmp.y_coordinate = y+j-1;
          tmp.id_c(height);
          //add parent
          if(CLOSED.find(tmp.id) == CLOSED.end()) {
            tmp.h_calc(n_goal, e, chosen_one);
            tmp.g_calc(*current);
            tmp.f_calc();
            successors.push_back(tmp);
          }
        }
      }
    }
    return successors;
  }
  void update_open(std::set <class NODE, comparator> &st_open, std::unordered_set<int> &open_id, NODE &new_node, NODE* pred){
    auto open_iterator = st_open.begin();

    auto is_inside_open = open_id.find(new_node.id);
    if (is_inside_open != open_id.end()){
      while (((*open_iterator).id != new_node.id) && (open_iterator != st_open.end())){
        ++open_iterator;
      }
    }else open_iterator = st_open.end();


    if(open_iterator != st_open.end()){
      NODE tmp = *open_iterator;
      st_open.erase(open_iterator);

      if(tmp.PRED->g > (*pred).g){
        tmp.PRED = pred;
      }
      tmp.check_g(new_node.g);
      st_open.insert(tmp);
    }else{
      //remove new
      new_node.PRED = new NODE;
      new_node.PRED = pred;
      st_open.insert(new_node);
    }
  }


public:
  //TODO: add constructor w/ 'e' and 'chosen_one' variables:
  AStarPlanner(double _e, int _chosen_one){
    e = _e;
    chosen_one = _chosen_one;
  }
  AStarPlanner(){
    e = 1.0;
    chosen_one = 1;
  };
  geometry_msgs::PoseArray getPath(geometry_msgs::Pose start, geometry_msgs::Pose goal, nav_msgs::OccupancyGrid grid);
};

geometry_msgs::PoseArray AStarPlanner::getPath(geometry_msgs::Pose start, geometry_msgs::Pose goal, nav_msgs::OccupancyGrid grid){
  ::n_start.x_coordinate = start.position.x;
  ::n_start.y_coordinate = start.position.y;
  ::n_goal.x_coordinate  =  goal.position.x;
  ::n_goal.y_coordinate  =  goal.position.y;
  ::n_start.id_c(grid.info.height); ::n_start.g = 0;
  ::n_goal.id_c(grid.info.height); ::n_goal.h = 0;

  std::vector <std::vector <bool> > map (grid.info.height, std::vector <bool> (grid.info.width));
  int b;
  for (int i = 0; i < grid.info.height; ++i){
    for(int j = 0; j < grid.info.width; ++j){
      b = grid.data[i*grid.info.height + j];
      map[i][j] = bool(b == 100 ? 1: 0);
    }
  }

  //ROS_INFO_STREAM("Successfully loaded data!");

  std::set <class NODE, comparator> OPEN;
  std::set <class NODE>::iterator open_start;
  std::unordered_set <int> OPEN_ID;
  std::unordered_map <int, class NODE> CLOSED;
  std::unordered_map <int, class NODE>::iterator address_of_goal_node;
  NODE* pred;
  std::stack  <NODE> PATH;

  OPEN.insert(n_start);

  NODE successor_node, cur_node;
  std::list <NODE> successors;
  bool goal_is_not_reached = 1;

  ROS_INFO_STREAM("Successfully started planning!");

  while (goal_is_not_reached) {

    if (equivalent(successor_node, n_goal) || (OPEN.size() == 0)) {
      goal_is_not_reached = 0;
      CLOSED.insert(std::make_pair(successor_node.id, successor_node));
      address_of_goal_node = CLOSED.find(successor_node.id);
      continue;
    }

    open_start = OPEN.begin();
    successor_node = *open_start;
    OPEN.erase(open_start);
    //std::cout << "Curently woking on :  " << successor_node.x_coordinate << "  " << successor_node.y_coordinate << std::endl;
    CLOSED.insert(std::make_pair(successor_node.id, successor_node));
    pred = &(CLOSED.find(successor_node.id)->second);

    //PROBLEM IS HERE
    successors = get_successors(pred, map, CLOSED, grid.info.height);
    for (auto suc_it = successors.begin(); suc_it != successors.end(); ++suc_it){
      cur_node = *suc_it;
      OPEN_ID.insert(cur_node.id);
      update_open(OPEN, OPEN_ID, cur_node, pred);

    }
  }
  ROS_INFO_STREAM("Successfully ended planning!");
  NODE path_node = (*address_of_goal_node).second;
  NODE path_node_next;
  PATH.push(path_node);
  bool path_not_complite = 1;
  //ROS_INFO_STREAM("Successfully started path constructing!");
  while(path_not_complite){
    path_node_next = *(path_node.PRED);
    if (equivalent(path_node_next, n_start)){
      path_not_complite = 0;
      PATH.push(n_start);
      continue;
    }
    else{
      PATH.push(path_node_next);
      path_node = path_node_next;
    }
  }
  //ROS_INFO_STREAM("Successfully ended path constructing!");
  geometry_msgs::PoseArray path;
  geometry_msgs::Pose point;
  int range = PATH.size();
  //ROS_INFO_STREAM("Successfully started path extracting");
  ROS_INFO_STREAM("Current path is:");
  for (int i = 0; i < range; ++i){
    point.position.x = PATH.top().x_coordinate;
    point.position.y = PATH.top().y_coordinate;
    PATH.pop();
    ROS_INFO_STREAM(point.position.x << "  " << point.position.y);
    path.poses.push_back(point);
  }
  return path;
  ROS_INFO_STREAM("Successfully ended path extracting");
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class Planner{
private:
  ros::Subscriber goalSub;
  ros::Subscriber gridSub;
  ros::Subscriber poseSub;
  ros::Subscriber actionSub;
  ros::Publisher pub;
  ros::Rate rate = ros::Rate(50);
  ros::ServiceClient globalToGridClient;
  ros::ServiceClient gridToGlobalClient;
  geometry_msgs::Pose goal;
  nav_msgs::OccupancyGrid grid;
  geometry_msgs::Pose start;
  geometry_msgs::PoseArray path;
  bool goalIsSet = false;
  bool gridIsSet = false;
  bool planned = false;
  AStarPlanner BetterPlanner;

  void setGoal(const geometry_msgs::Pose::ConstPtr& goalMsg);
  void setGrid(const nav_msgs::OccupancyGrid::ConstPtr& gridMsg);
  void setStart(const geometry_msgs::Pose::ConstPtr& HuskyPoseMsg);
  void action(const std_msgs::String::ConstPtr& actionMsg);
  bool checkTask();
public:
  Planner(ros::NodeHandle &nh);


  //These two functions allow user to get either hardcoded pre-written path, or path via A* planner
  geometry_msgs::PoseArray getHardcodedPath();
  geometry_msgs::PoseArray getAStarPath();

  //This function publish created path to the publisher
  void publish();
};
////////////////////////////////////////////////////////////////////////////////
Planner::Planner(ros::NodeHandle &nh){
  globalToGridClient = nh.serviceClient<coord_transform::coords>("global_to_grid");
  gridToGlobalClient = nh.serviceClient<coord_transform::coords>("grid_to_global");
  goalSub = nh.subscribe<geometry_msgs::Pose>("set_goal", 50, &Planner::setGoal, this);
  gridSub = nh.subscribe<nav_msgs::OccupancyGrid>("set_occupancy_grid", 50, &Planner::setGrid, this);
  poseSub = nh.subscribe<geometry_msgs::Pose>("robot_pose", 50, &Planner::setStart, this);
  actionSub = nh.subscribe<std_msgs::String>("action", 50, &Planner::action, this);
  pub = nh.advertise<geometry_msgs::PoseArray>("set_path", 50);
  double e;
  int chosen_one;
  nh.param<double>("hweight", e, 1.0);
  nh.param<int>("metricType", chosen_one, 1);
  BetterPlanner = AStarPlanner(e, chosen_one);
}

void Planner::setGoal(const geometry_msgs::Pose::ConstPtr& goalMsg){
  goal = *goalMsg;
  if (gridIsSet){
    coord_transform::coords crd;
    crd.request.info = grid.info;
    crd.request.input = goal;
    globalToGridClient.call(crd);
    goal = crd.response.output;
    goalIsSet = true;
    ROS_INFO_STREAM("Goal was received by path_planner");
    ROS_INFO_STREAM("Goal in grid coordinates: " << goal.position.x << " " << goal.position.y);
  }else ROS_WARN_STREAM("Cannot transform goal point coordinates into grid system. Send grid info first");
}

void Planner::setGrid(const nav_msgs::OccupancyGrid::ConstPtr& gridMsg){
  grid = *gridMsg;
  gridIsSet = true;
  ROS_INFO_STREAM("Grid was received by path_planner");
}

bool Planner::checkTask(){
  if (grid.info.width * grid.info.height != grid.data.size()){
    ROS_ERROR_STREAM("Grid error. Input data incorrect. Number of grid elements does not match width and height.");
    return false;
  }
  if (isnan(grid.info.origin.position.x)){
    ROS_ERROR_STREAM("Grid error. Input data incorrect. Grid origin position x is NaN.");
    return false;
  }
  if (isnan(grid.info.origin.position.y)){
    ROS_ERROR_STREAM("Grid error. Input data incorrect. Grid origin position y is NaN.");
    return false;
  }
  if (isnan(grid.info.resolution)){
    ROS_ERROR_STREAM("Grid error. Input data incorrect. Grid resolution is NaN.");
    return false;
  }
  if (grid.info.resolution <= 0){
    ROS_ERROR_STREAM("Grid error. Input data incorrect. Grid resolution is less or equal zero.");
    return false;
  }
  if ((goal.position.x > grid.info.width) || (goal.position.y > grid.info.height)){
    ROS_ERROR_STREAM("Goal is anacceptable: point is out of occupancy grid");
    return false;
  }
  //проверка current position
  return true;
}
void Planner::setStart(const geometry_msgs::Pose::ConstPtr& HuskyPoseMsg){
  start = *HuskyPoseMsg;
  coord_transform::coords crd;
  crd.request.info = grid.info;
  crd.request.input = start;
  //ROS_INFO_STREAM("before transformation: "<< start.position.x << " " << start.position.y << " " << start.position.z);
  globalToGridClient.call(crd);
  start = crd.response.output;
  //ROS_INFO_STREAM("after transformation: "<< start.position.x << " " << start.position.y << " " << start.position.z);
}

void Planner::action(const std_msgs::String::ConstPtr& actionMsg){
  if (actionMsg->data == "find-path-hc"){
    path = getHardcodedPath();
  }else if (actionMsg->data == "find-path-astar"){
    if (checkTask()) path = getAStarPath();
    else ROS_ERROR_STREAM("Path planning error. Stopping");
  }else if (actionMsg->data == "get-path"){
    publish();
  }else if (actionMsg->data == "status-planner"){
    ROS_INFO_STREAM("Current status:");
    if (planned) {
      ROS_INFO_STREAM("Planning completed");
      ROS_INFO_STREAM("Path is:");
      for (auto point : path.poses){
        ROS_INFO_STREAM(point.position.x << "  " << point.position.y);
      }
    } else ROS_INFO_STREAM("No path has been planned yet");
    if (goalIsSet){
      ROS_INFO_STREAM("Goal is " << goal.position.x << " " << goal.position.y << " in grid coordinates");
      //ROS_INFO_STREAM("Goal is " << SIZE_CELL*goal.position.x  - SIZE_CELL << " " << SIZE_CELL - SIZE_CELL*goal.position.y << " in global coordinates");
    } else ROS_INFO_STREAM("No goal has been choosed yet");
  }
}

geometry_msgs::PoseArray Planner::getHardcodedPath(){
  geometry_msgs::PoseArray path;
  geometry_msgs::Pose point;

  point.position.x = 3.0;
  point.position.y = 1.0;
  path.poses.push_back(point);
  point.position.x = 3.0;
  point.position.y = 2.0;
  path.poses.push_back(point);
  point.position.x = 3.0;
  point.position.y = 3.0;
  path.poses.push_back(point);


  planned = true;
  return path;
}

geometry_msgs::PoseArray Planner::getAStarPath(){
  planned = true;//но это может быть не так!
  return BetterPlanner.getPath(start, goal, grid);
}

void Planner::publish(){
  while(pub.getNumSubscribers() == 0)
    rate.sleep();
  coord_transform::coords crd;
  geometry_msgs::PoseArray pub_path;
  for(auto point : path.poses){
    crd.request.info = grid.info;
    crd.request.input = point;
    gridToGlobalClient.call(crd);
    point = crd.response.output;
    pub_path.poses.push_back(point);
  }
  pub.publish(pub_path);
}
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv) {
  ros::init(argc, argv, "path_planner");
  ros::NodeHandle nh;
  Planner planner = Planner(nh);
  ros::spin();
}
