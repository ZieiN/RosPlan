#!/usr/bin/env python
# coding: utf-8

# In[4]:


from PIL import Image
import numpy as np
import rospy
import yaml
import sys

np.set_printoptions(threshold=sys.maxsize)

def generateGrid(data_folder, name):
    #open image and convert it to numpy array
    im = Image.open(data_folder + '/' + name + '.png')
    yaml_file = data_folder + '/' + name + '.yaml'
    with open(yaml_file, 'r') as f:
        configs = yaml.load(f)
    scale = configs["resolution"]
    origin = configs["origin"]
    m = np.array(im)
    print(m)
    m = m / 229
    print(m)
    m = abs(m - 1)
    print(m)
    m = m / 255
    print(m)
    m = m * 100
    print(m[::, ::, 1])
    #and then write it to txt file
    f = open(data_folder + '/' + name + '.txt', 'w')
    f.write(str(m.shape[0]) + '\n' + str(m.shape[1]) + '\n')
    f.write(str(scale) + '\n')
    for i in origin:
        f.write(str(i) + '\n')
    for i in range(m.shape[0]):
        for j in range(m.shape[1]):
            f.write(str(m[i][j][2]) + '\n')

    f.close()


if __name__ == '__main__':
    data_folder = rospy.get_param("data_folder")
    name = rospy.get_param("occupancy_grid_name")
    generateGrid(data_folder, name)