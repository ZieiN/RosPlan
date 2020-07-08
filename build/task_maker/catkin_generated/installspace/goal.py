#!/usr/bin/env python2
import rospy
from std_msgs.msg import String
from geometry_msgs.msg import Pose
import numpy as np

path = "/home/vlad/test/1/goal.txt"
pub = rospy.Publisher('set_goal', Pose, queue_size = 1)
goalPose = Pose()

def setGoal():
    rospy.init_node('goal', anonymous = False)
    sub = rospy.Subscriber('action', String, callback)

    rospy.spin()
def callback(action):
    if action.data == "read-goal" or action.data == 'load data':
        read_goal()
        rospy.loginfo_once("reading goal")
    elif action.data == "set-goal" or action.data == 'set data':
        pub.publish(goalPose)
        rospy.loginfo_once("publishing goal")

def read_goal():
    with open(path) as goalData:
        goalPose.position.x = np.float64(goalData.readline())
        goalPose.position.y = np.float64(goalData.readline())
        goalPose.position.z = np.float64(goalData.readline())

if __name__ == "__main__":
    setGoal()
