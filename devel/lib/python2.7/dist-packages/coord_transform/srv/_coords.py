# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from coord_transform/coordsRequest.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import geometry_msgs.msg
import nav_msgs.msg
import genpy

class coordsRequest(genpy.Message):
  _md5sum = "f4a01d403d0029bb0629ed4ed897cf71"
  _type = "coord_transform/coordsRequest"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """nav_msgs/MapMetaData info
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
"""
  __slots__ = ['info','input']
  _slot_types = ['nav_msgs/MapMetaData','geometry_msgs/Pose']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       info,input

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(coordsRequest, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.info is None:
        self.info = nav_msgs.msg.MapMetaData()
      if self.input is None:
        self.input = geometry_msgs.msg.Pose()
    else:
      self.info = nav_msgs.msg.MapMetaData()
      self.input = geometry_msgs.msg.Pose()

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_get_struct_2If2I14d().pack(_x.info.map_load_time.secs, _x.info.map_load_time.nsecs, _x.info.resolution, _x.info.width, _x.info.height, _x.info.origin.position.x, _x.info.origin.position.y, _x.info.origin.position.z, _x.info.origin.orientation.x, _x.info.origin.orientation.y, _x.info.origin.orientation.z, _x.info.origin.orientation.w, _x.input.position.x, _x.input.position.y, _x.input.position.z, _x.input.orientation.x, _x.input.orientation.y, _x.input.orientation.z, _x.input.orientation.w))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.info is None:
        self.info = nav_msgs.msg.MapMetaData()
      if self.input is None:
        self.input = geometry_msgs.msg.Pose()
      end = 0
      _x = self
      start = end
      end += 132
      (_x.info.map_load_time.secs, _x.info.map_load_time.nsecs, _x.info.resolution, _x.info.width, _x.info.height, _x.info.origin.position.x, _x.info.origin.position.y, _x.info.origin.position.z, _x.info.origin.orientation.x, _x.info.origin.orientation.y, _x.info.origin.orientation.z, _x.info.origin.orientation.w, _x.input.position.x, _x.input.position.y, _x.input.position.z, _x.input.orientation.x, _x.input.orientation.y, _x.input.orientation.z, _x.input.orientation.w,) = _get_struct_2If2I14d().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_get_struct_2If2I14d().pack(_x.info.map_load_time.secs, _x.info.map_load_time.nsecs, _x.info.resolution, _x.info.width, _x.info.height, _x.info.origin.position.x, _x.info.origin.position.y, _x.info.origin.position.z, _x.info.origin.orientation.x, _x.info.origin.orientation.y, _x.info.origin.orientation.z, _x.info.origin.orientation.w, _x.input.position.x, _x.input.position.y, _x.input.position.z, _x.input.orientation.x, _x.input.orientation.y, _x.input.orientation.z, _x.input.orientation.w))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.info is None:
        self.info = nav_msgs.msg.MapMetaData()
      if self.input is None:
        self.input = geometry_msgs.msg.Pose()
      end = 0
      _x = self
      start = end
      end += 132
      (_x.info.map_load_time.secs, _x.info.map_load_time.nsecs, _x.info.resolution, _x.info.width, _x.info.height, _x.info.origin.position.x, _x.info.origin.position.y, _x.info.origin.position.z, _x.info.origin.orientation.x, _x.info.origin.orientation.y, _x.info.origin.orientation.z, _x.info.origin.orientation.w, _x.input.position.x, _x.input.position.y, _x.input.position.z, _x.input.orientation.x, _x.input.orientation.y, _x.input.orientation.z, _x.input.orientation.w,) = _get_struct_2If2I14d().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_2If2I14d = None
def _get_struct_2If2I14d():
    global _struct_2If2I14d
    if _struct_2If2I14d is None:
        _struct_2If2I14d = struct.Struct("<2If2I14d")
    return _struct_2If2I14d
# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from coord_transform/coordsResponse.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import geometry_msgs.msg

class coordsResponse(genpy.Message):
  _md5sum = "e5a4ac2a55e91a597647da3a0f20a3e1"
  _type = "coord_transform/coordsResponse"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """geometry_msgs/Pose output


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
"""
  __slots__ = ['output']
  _slot_types = ['geometry_msgs/Pose']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       output

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(coordsResponse, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.output is None:
        self.output = geometry_msgs.msg.Pose()
    else:
      self.output = geometry_msgs.msg.Pose()

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_get_struct_7d().pack(_x.output.position.x, _x.output.position.y, _x.output.position.z, _x.output.orientation.x, _x.output.orientation.y, _x.output.orientation.z, _x.output.orientation.w))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.output is None:
        self.output = geometry_msgs.msg.Pose()
      end = 0
      _x = self
      start = end
      end += 56
      (_x.output.position.x, _x.output.position.y, _x.output.position.z, _x.output.orientation.x, _x.output.orientation.y, _x.output.orientation.z, _x.output.orientation.w,) = _get_struct_7d().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_get_struct_7d().pack(_x.output.position.x, _x.output.position.y, _x.output.position.z, _x.output.orientation.x, _x.output.orientation.y, _x.output.orientation.z, _x.output.orientation.w))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.output is None:
        self.output = geometry_msgs.msg.Pose()
      end = 0
      _x = self
      start = end
      end += 56
      (_x.output.position.x, _x.output.position.y, _x.output.position.z, _x.output.orientation.x, _x.output.orientation.y, _x.output.orientation.z, _x.output.orientation.w,) = _get_struct_7d().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_7d = None
def _get_struct_7d():
    global _struct_7d
    if _struct_7d is None:
        _struct_7d = struct.Struct("<7d")
    return _struct_7d
class coords(object):
  _type          = 'coord_transform/coords'
  _md5sum = '5506dc073028d0e0a02766c42314c146'
  _request_class  = coordsRequest
  _response_class = coordsResponse
