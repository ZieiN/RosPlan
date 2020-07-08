; Auto-generated. Do not edit!


(cl:in-package coord_transform-srv)


;//! \htmlinclude coords-request.msg.html

(cl:defclass <coords-request> (roslisp-msg-protocol:ros-message)
  ((info
    :reader info
    :initarg :info
    :type nav_msgs-msg:MapMetaData
    :initform (cl:make-instance 'nav_msgs-msg:MapMetaData))
   (input
    :reader input
    :initarg :input
    :type geometry_msgs-msg:Pose
    :initform (cl:make-instance 'geometry_msgs-msg:Pose)))
)

(cl:defclass coords-request (<coords-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <coords-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'coords-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name coord_transform-srv:<coords-request> is deprecated: use coord_transform-srv:coords-request instead.")))

(cl:ensure-generic-function 'info-val :lambda-list '(m))
(cl:defmethod info-val ((m <coords-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader coord_transform-srv:info-val is deprecated.  Use coord_transform-srv:info instead.")
  (info m))

(cl:ensure-generic-function 'input-val :lambda-list '(m))
(cl:defmethod input-val ((m <coords-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader coord_transform-srv:input-val is deprecated.  Use coord_transform-srv:input instead.")
  (input m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <coords-request>) ostream)
  "Serializes a message object of type '<coords-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'info) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'input) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <coords-request>) istream)
  "Deserializes a message object of type '<coords-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'info) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'input) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<coords-request>)))
  "Returns string type for a service object of type '<coords-request>"
  "coord_transform/coordsRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'coords-request)))
  "Returns string type for a service object of type 'coords-request"
  "coord_transform/coordsRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<coords-request>)))
  "Returns md5sum for a message object of type '<coords-request>"
  "5506dc073028d0e0a02766c42314c146")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'coords-request)))
  "Returns md5sum for a message object of type 'coords-request"
  "5506dc073028d0e0a02766c42314c146")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<coords-request>)))
  "Returns full string definition for message of type '<coords-request>"
  (cl:format cl:nil "nav_msgs/MapMetaData info~%geometry_msgs/Pose input~%~%================================================================================~%MSG: nav_msgs/MapMetaData~%# This hold basic information about the characterists of the OccupancyGrid~%~%# The time at which the map was loaded~%time map_load_time~%# The map resolution [m/cell]~%float32 resolution~%# Map width [cells]~%uint32 width~%# Map height [cells]~%uint32 height~%# The origin of the map [m, m, rad].  This is the real-world pose of the~%# cell (0,0) in the map.~%geometry_msgs/Pose origin~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'coords-request)))
  "Returns full string definition for message of type 'coords-request"
  (cl:format cl:nil "nav_msgs/MapMetaData info~%geometry_msgs/Pose input~%~%================================================================================~%MSG: nav_msgs/MapMetaData~%# This hold basic information about the characterists of the OccupancyGrid~%~%# The time at which the map was loaded~%time map_load_time~%# The map resolution [m/cell]~%float32 resolution~%# Map width [cells]~%uint32 width~%# Map height [cells]~%uint32 height~%# The origin of the map [m, m, rad].  This is the real-world pose of the~%# cell (0,0) in the map.~%geometry_msgs/Pose origin~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <coords-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'info))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'input))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <coords-request>))
  "Converts a ROS message object to a list"
  (cl:list 'coords-request
    (cl:cons ':info (info msg))
    (cl:cons ':input (input msg))
))
;//! \htmlinclude coords-response.msg.html

(cl:defclass <coords-response> (roslisp-msg-protocol:ros-message)
  ((output
    :reader output
    :initarg :output
    :type geometry_msgs-msg:Pose
    :initform (cl:make-instance 'geometry_msgs-msg:Pose)))
)

(cl:defclass coords-response (<coords-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <coords-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'coords-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name coord_transform-srv:<coords-response> is deprecated: use coord_transform-srv:coords-response instead.")))

(cl:ensure-generic-function 'output-val :lambda-list '(m))
(cl:defmethod output-val ((m <coords-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader coord_transform-srv:output-val is deprecated.  Use coord_transform-srv:output instead.")
  (output m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <coords-response>) ostream)
  "Serializes a message object of type '<coords-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'output) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <coords-response>) istream)
  "Deserializes a message object of type '<coords-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'output) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<coords-response>)))
  "Returns string type for a service object of type '<coords-response>"
  "coord_transform/coordsResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'coords-response)))
  "Returns string type for a service object of type 'coords-response"
  "coord_transform/coordsResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<coords-response>)))
  "Returns md5sum for a message object of type '<coords-response>"
  "5506dc073028d0e0a02766c42314c146")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'coords-response)))
  "Returns md5sum for a message object of type 'coords-response"
  "5506dc073028d0e0a02766c42314c146")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<coords-response>)))
  "Returns full string definition for message of type '<coords-response>"
  (cl:format cl:nil "geometry_msgs/Pose output~%~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'coords-response)))
  "Returns full string definition for message of type 'coords-response"
  (cl:format cl:nil "geometry_msgs/Pose output~%~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <coords-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'output))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <coords-response>))
  "Converts a ROS message object to a list"
  (cl:list 'coords-response
    (cl:cons ':output (output msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'coords)))
  'coords-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'coords)))
  'coords-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'coords)))
  "Returns string type for a service object of type '<coords>"
  "coord_transform/coords")