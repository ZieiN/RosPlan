#!/usr/bin/env python
import rospy
from std_msgs.msg import String
from nav_msgs.msg import OccupancyGrid
import numpy as np

grid = OccupancyGrid()
pub = rospy.Publisher('set_occupancy_grid', OccupancyGrid, queue_size=5)


def MapCreator():
    rospy.init_node('occupancy_grid', anonymous=False)
    sub = rospy.Subscriber('action', String, callback)
    # TODO: mission action

    rospy.spin()


def callback(action):
    if action.data == 'read-grid' or action.data == 'read-data':
        rospy.loginfo_once("reading grid")
        read_grid()
        transform_grid()
    elif action.data == 'set-grid' or action.data == 'set-data':
        pub.publish(grid)
        rospy.loginfo_once("publishing grid")
    elif action.data == 'load-data':
        rospy.loginfo_once("Reading and publishing grid")
        read_grid()
        pub.publish(grid)
    elif action.data == 'test':
        transform_grid()
        print(grid.data)


def read_grid():
    with open(path) as mapData:
        grid.info.height = np.uint32(mapData.readline())
        grid.info.width = np.uint32(mapData.readline())
        grid.info.resolution = np.float32(mapData.readline())
        grid.info.origin.position.x = np.float64(mapData.readline())
        grid.info.origin.position.y = np.float64(mapData.readline())
        grid.info.origin.position.z = np.float64(mapData.readline())
        data = []
        while True:
            c = mapData.readline()
            if not c:
                break
            data.append(np.int8(c))
        grid.data = data


def transform_grid():
    grid.info.height += 2
    grid.info.width += 2
    grid.info.origin.position.x -= grid.info.resolution
    grid.info.origin.position.y -= grid.info.resolution
    new_data = []
    for i in range(grid.info.width):
        for j in range(grid.info.height):
            if i == 0 or j == 0 or i == grid.info.height-1 or j == grid.info.width-1:
                new_data.append(100)
            else:
                #print(grid.data[(j-1)*(grid.info.height-2)+(i-1)])
                new_data.append(grid.data[(i-1)*(grid.info.height-2)+(j-1)])
    grid.data = new_data



if __name__ == '__main__':
    path = rospy.get_param("data_folder")
    path = path + '/grid.txt'
    MapCreator()
