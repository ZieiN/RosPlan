#!/usr/bin/env python
import rospy
from std_msgs.msg import String
from nav_msgs.msg import OccupancyGrid
import numpy as np

path = rospy.get_param('~path', '/home/vlad/test/1')
path += '/grid.txt'

grid = OccupancyGrid()
pub = rospy.Publisher('set_occupancy_grid', OccupancyGrid, queue_size = 5)

def MapCreator():
    rospy.init_node('occupancy_grid', anonymous = False)
    sub = rospy.Subscriber('action', String, callback)
    #TODO: mission action

    rospy.spin()

def callback(action):
    if action.data == 'read-grid' or action.data == 'load data':
        rospy.loginfo_once("reading grid")
        read_grid()
    elif action.data == 'set-grid' or action.data == 'set data':
        pub.publish(grid)
        rospy.loginfo_once("publishing grid")

def read_grid():
    with open(path) as mapData:
        grid.info.width = np.uint32(mapData.readline())
        grid.info.height = np.uint32(mapData.readline())
        grid.info.resolution = np.float32(mapData.readline());
        grid.info.origin.position.x = np.float64(mapData.readline());
        grid.info.origin.position.y = np.float64(mapData.readline());
        grid.info.origin.position.z = np.float64(mapData.readline());
        data = []
        while True:
            c = mapData.readline()
            if not c:
                break
            data.append(np.int8(c))
        grid.data = data

if __name__ == '__main__':
    MapCreator()
