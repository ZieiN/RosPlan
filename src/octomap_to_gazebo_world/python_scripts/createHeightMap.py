#!/usr/bin/env python
import rospy
import numpy as np
import yaml
import random
import sys
import scipy

np.set_printoptions(threshold=sys.maxsize)

if __name__ == '__main__':
    data_folder = rospy.get_param("data_folder")
    occupancy_grid_name = rospy.get_param("occupancy_grid_name")
    occupancy_grid_yaml = occupancy_grid_name + '.yaml'

    with open(occupancy_grid_yaml, 'r') as f:
        configs = yaml.load(f)
    size = configs["size"]
    random.seed()
    N = random.randint(1, 5)
    height_map = np.zeros((size[0], size[1]))
    for i in range(N):
        origin_x = random.randint(1, size[0])
        origin_y = random.randint(1, size[1])
        sigma_x = random.random() * random.randint(size[0] / 2, size[0])
        sigma_y = random.random() * random.randint(size[1] / 2, size[1])
        x = np.arange(0, size[0], 1)
        y = np.arange(0, size[1], 1)
        x_rand = np.exp(-((x - origin_x) ** 2) / (2 * sigma_x ** 2))
        y_rand = np.exp(-((y - origin_y) ** 2) / (2 * sigma_y ** 2))
        x_rand_rescaled = np.zeros((size[0], size[1]))
        y_rand_rescaled = np.zeros((size[0], size[1]))
        x_rand_rescaled[0, ::] = x_rand
        y_rand_rescaled[::, 0] = y_rand
        gauss = x_rand_rescaled.T.dot(y_rand_rescaled.T)

        scale = random.randint(100, 1000) * random.random()
        gauss *= scale
        gauss = np.where(gauss < 0.01, 0, gauss)
        gauss = gauss / gauss.max() * 100
        print("gauss number " + str(i) + "is")
        print(gauss)
        height_map += gauss
    height_map = height_map / height_map.max() * 100
    height_map = np.around(height_map)
    height_map = height_map.astype(int)
    print("final result: ")
    print(height_map)
    with open(data_folder + "/heightMap.txt", "w+") as f:
        for line in height_map:
            for el in line:
                f.write(str(el) + "\n")
