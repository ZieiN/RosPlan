;; Auto-generated. Do not edit!


(when (boundp 'coord_transform::coords)
  (if (not (find-package "COORD_TRANSFORM"))
    (make-package "COORD_TRANSFORM"))
  (shadow 'coords (find-package "COORD_TRANSFORM")))
(unless (find-package "COORD_TRANSFORM::COORDS")
  (make-package "COORD_TRANSFORM::COORDS"))
(unless (find-package "COORD_TRANSFORM::COORDSREQUEST")
  (make-package "COORD_TRANSFORM::COORDSREQUEST"))
(unless (find-package "COORD_TRANSFORM::COORDSRESPONSE")
  (make-package "COORD_TRANSFORM::COORDSRESPONSE"))

(in-package "ROS")

(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "NAV_MSGS"))
  (ros::roseus-add-msgs "nav_msgs"))


(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass coord_transform::coordsRequest
  :super ros::object
  :slots (_info _input ))

(defmethod coord_transform::coordsRequest
  (:init
   (&key
    ((:info __info) (instance nav_msgs::MapMetaData :init))
    ((:input __input) (instance geometry_msgs::Pose :init))
    )
   (send-super :init)
   (setq _info __info)
   (setq _input __input)
   self)
  (:info
   (&rest __info)
   (if (keywordp (car __info))
       (send* _info __info)
     (progn
       (if __info (setq _info (car __info)))
       _info)))
  (:input
   (&rest __input)
   (if (keywordp (car __input))
       (send* _input __input)
     (progn
       (if __input (setq _input (car __input)))
       _input)))
  (:serialization-length
   ()
   (+
    ;; nav_msgs/MapMetaData _info
    (send _info :serialization-length)
    ;; geometry_msgs/Pose _input
    (send _input :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; nav_msgs/MapMetaData _info
       (send _info :serialize s)
     ;; geometry_msgs/Pose _input
       (send _input :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; nav_msgs/MapMetaData _info
     (send _info :deserialize buf ptr-) (incf ptr- (send _info :serialization-length))
   ;; geometry_msgs/Pose _input
     (send _input :deserialize buf ptr-) (incf ptr- (send _input :serialization-length))
   ;;
   self)
  )

(defclass coord_transform::coordsResponse
  :super ros::object
  :slots (_output ))

(defmethod coord_transform::coordsResponse
  (:init
   (&key
    ((:output __output) (instance geometry_msgs::Pose :init))
    )
   (send-super :init)
   (setq _output __output)
   self)
  (:output
   (&rest __output)
   (if (keywordp (car __output))
       (send* _output __output)
     (progn
       (if __output (setq _output (car __output)))
       _output)))
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Pose _output
    (send _output :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Pose _output
       (send _output :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Pose _output
     (send _output :deserialize buf ptr-) (incf ptr- (send _output :serialization-length))
   ;;
   self)
  )

(defclass coord_transform::coords
  :super ros::object
  :slots ())

(setf (get coord_transform::coords :md5sum-) "5506dc073028d0e0a02766c42314c146")
(setf (get coord_transform::coords :datatype-) "coord_transform/coords")
(setf (get coord_transform::coords :request) coord_transform::coordsRequest)
(setf (get coord_transform::coords :response) coord_transform::coordsResponse)

(defmethod coord_transform::coordsRequest
  (:response () (instance coord_transform::coordsResponse :init)))

(setf (get coord_transform::coordsRequest :md5sum-) "5506dc073028d0e0a02766c42314c146")
(setf (get coord_transform::coordsRequest :datatype-) "coord_transform/coordsRequest")
(setf (get coord_transform::coordsRequest :definition-)
      "nav_msgs/MapMetaData info
geometry_msgs/Pose input

================================================================================
MSG: nav_msgs/MapMetaData
# This hold basic information about the characterists of the OccupancyGrid

# The time at which the map was loaded
time map_load_time
# The map resolution [m/cell]
float32 resolution
# Map width [cells]
uint32 width
# Map height [cells]
uint32 height
# The origin of the map [m, m, rad].  This is the real-world pose of the
# cell (0,0) in the map.
geometry_msgs/Pose origin
================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w
---
geometry_msgs/Pose output


================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w
")

(setf (get coord_transform::coordsResponse :md5sum-) "5506dc073028d0e0a02766c42314c146")
(setf (get coord_transform::coordsResponse :datatype-) "coord_transform/coordsResponse")
(setf (get coord_transform::coordsResponse :definition-)
      "nav_msgs/MapMetaData info
geometry_msgs/Pose input

================================================================================
MSG: nav_msgs/MapMetaData
# This hold basic information about the characterists of the OccupancyGrid

# The time at which the map was loaded
time map_load_time
# The map resolution [m/cell]
float32 resolution
# Map width [cells]
uint32 width
# Map height [cells]
uint32 height
# The origin of the map [m, m, rad].  This is the real-world pose of the
# cell (0,0) in the map.
geometry_msgs/Pose origin
================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w
---
geometry_msgs/Pose output


================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w
")



(provide :coord_transform/coords "5506dc073028d0e0a02766c42314c146")


