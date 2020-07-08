// Auto-generated. Do not edit!

// (in-package coord_transform.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let nav_msgs = _finder('nav_msgs');
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------


//-----------------------------------------------------------

class coordsRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.info = null;
      this.input = null;
    }
    else {
      if (initObj.hasOwnProperty('info')) {
        this.info = initObj.info
      }
      else {
        this.info = new nav_msgs.msg.MapMetaData();
      }
      if (initObj.hasOwnProperty('input')) {
        this.input = initObj.input
      }
      else {
        this.input = new geometry_msgs.msg.Pose();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type coordsRequest
    // Serialize message field [info]
    bufferOffset = nav_msgs.msg.MapMetaData.serialize(obj.info, buffer, bufferOffset);
    // Serialize message field [input]
    bufferOffset = geometry_msgs.msg.Pose.serialize(obj.input, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type coordsRequest
    let len;
    let data = new coordsRequest(null);
    // Deserialize message field [info]
    data.info = nav_msgs.msg.MapMetaData.deserialize(buffer, bufferOffset);
    // Deserialize message field [input]
    data.input = geometry_msgs.msg.Pose.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 132;
  }

  static datatype() {
    // Returns string type for a service object
    return 'coord_transform/coordsRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'f4a01d403d0029bb0629ed4ed897cf71';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    nav_msgs/MapMetaData info
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new coordsRequest(null);
    if (msg.info !== undefined) {
      resolved.info = nav_msgs.msg.MapMetaData.Resolve(msg.info)
    }
    else {
      resolved.info = new nav_msgs.msg.MapMetaData()
    }

    if (msg.input !== undefined) {
      resolved.input = geometry_msgs.msg.Pose.Resolve(msg.input)
    }
    else {
      resolved.input = new geometry_msgs.msg.Pose()
    }

    return resolved;
    }
};

class coordsResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.output = null;
    }
    else {
      if (initObj.hasOwnProperty('output')) {
        this.output = initObj.output
      }
      else {
        this.output = new geometry_msgs.msg.Pose();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type coordsResponse
    // Serialize message field [output]
    bufferOffset = geometry_msgs.msg.Pose.serialize(obj.output, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type coordsResponse
    let len;
    let data = new coordsResponse(null);
    // Deserialize message field [output]
    data.output = geometry_msgs.msg.Pose.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 56;
  }

  static datatype() {
    // Returns string type for a service object
    return 'coord_transform/coordsResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e5a4ac2a55e91a597647da3a0f20a3e1';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new coordsResponse(null);
    if (msg.output !== undefined) {
      resolved.output = geometry_msgs.msg.Pose.Resolve(msg.output)
    }
    else {
      resolved.output = new geometry_msgs.msg.Pose()
    }

    return resolved;
    }
};

module.exports = {
  Request: coordsRequest,
  Response: coordsResponse,
  md5sum() { return '5506dc073028d0e0a02766c42314c146'; },
  datatype() { return 'coord_transform/coords'; }
};
