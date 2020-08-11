#!/usr/bin/env python

import rospy
import yaml
import os.path
import numpy as np
from createGazeboWorld import writeSvnHeaders
from createGazeboWorld import writeWallToWorld, closeWorldFile

def get_walls(name) :
    """input:
    text file to occupancy grid: 2 dimensional np.array
    """
    
    """ output:
    list_origin_walls: (list of tuples) : list of origins of walls
    list_final_walls: (list of tuples) : list of ends of walls
    """
    origin = []
    array = []
    with open(name) as file:
        w = int(next(file).strip()) # read first line
        h = int(next(file).strip())
        #тут нужно передать и поменять
        scale = float(next(file).strip())
        #origin_x, origin_y, origin_z
        origin_x = float(next(file).strip())
        origin_y = float(next(file).strip())
        origin_z = float(next(file).strip())

        for line in file:
            array.append(int(line.strip()))
    
    file.close()
    
    occupancy_grid = np.zeros((h, w), dtype=np.int8)
    
    for i in range(h):
        for j in range(w):
            occupancy_grid[i, j] = array[i * w + j]  
        
    list_origin_walls = []
    list_final_walls = []
    init = False
    for i in range(occupancy_grid.shape[0]):
        for j in range(occupancy_grid.shape[1]): 
            if (occupancy_grid[i, j] == 100 and not init):
                wall_init = (float(i), float(j))
                #print("origin: i: ", i,"j:", j)
                list_origin_walls.append(wall_init)
                init = True
            if (init and occupancy_grid[i, j] == 0):
                wall_final = (float(i), float(j-1))
                #print("final: i: ", i,"j:", j)
                list_final_walls.append(wall_final)
                init = False
            elif (init and occupancy_grid[i, j] == 100 and j == occupancy_grid.shape[1] - 1):
                wall_final = (float(i), float(j))
                #print("final: i: ", i,"j:", j)
                list_final_walls.append(wall_final)
                init = False
    return list_origin_walls, list_final_walls, scale,    

def writeGazeboAndDatFiles(list_origin_walls, list_final_walls, scale, gazebo_file):
    writeSvnHeaders(gazebo_file)
    wall_num = 0
    wall_num = writeWallToWorld(list_origin_walls, list_final_walls, scale, gazebo_file, wall_num)
    #print("type(wall_num): ", type(wall_num))
    #print("wall_num", wall_num)



if __name__ == '__main__':
    occupancy_grid_name = rospy.get_param("occupancy_grid_name")
    occupancy_grid_yaml = occupancy_grid_name + '.yaml'
    occupancy_grid_txt = occupancy_grid_name + '.txt'

    #print occupancy_grid_yaml
    with open(occupancy_grid_yaml, 'r') as f:
        configs = yaml.load(f)

    #scale = configs["resolution"]
    map_name = configs["image"]
    occupancy_grid_file = os.path.dirname(occupancy_grid_yaml) + '/' + map_name

    #output_contour_filename = rospy.get_param("contour_file")
    output_gazebo_filename = rospy.get_param("gazebo_world_file")

    list_origin_walls, list_final_walls, scale = get_walls(occupancy_grid_txt)

    gazebo_file = open(output_gazebo_filename, 'w+')

    writeGazeboAndDatFiles(list_origin_walls, list_final_walls, scale, gazebo_file)
    closeWorldFile(gazebo_file)


print("Reading was successful")
