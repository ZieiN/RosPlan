Header header
# 
float64 roll
# 
float64 pitch
# 
float64 heading

# СКО ориентации
geometry_msgs/Vector3 orientation_dev

# 
float64 latitude
# 
float64 longitude
# 
float64 altitude

# Путевая скорость
float64 speed

# Северная, восточная и вертикальная составляющие путевой скорости
geometry_msgs/Vector3 linear_velocity
# СКО для определения состовляющих путевой скорости
geometry_msgs/Vector3 linear_vel_dev

#
geometry_msgs/Vector3 linear_acceleration

#
geometry_msgs/Vector3 angular_velocity
