#!/usr/bin/env python
# coding: utf-8

# In[4]:


from PIL import Image
import numpy as np
import rospy


def generateGrid(data_folder, name):
    #open image and convert it to numpy array
    im = Image.open(data_folder + name + '.pgm')
    p = np.array(im)
    m = p[::, ::, 1]
    m = m / 255
    m = abs(m - 1)
    m = m.astype(int)
    #and then write it to txt file
    f = open(data_folder + 'grid.txt', 'w')
    f.write(str(m.shape[0]) + ' ' + str(m.shape[1]) + '\n')
    f.write('150 425 \n325 100 \n')
    for i in range(m.shape[0]):
        for j in range(m.shape[1]):
            f.write(str(j + 1) + ' ' + str(i + 1) + ' ' + str(m[i][j]) + '\n')

    f.close()


if __name__ == '__main__':
    data_folder = rospy.get_param("data_folder")
    name = rospy.get_param("occupancy_grid_name")
    generateGrid(data_folder, name)