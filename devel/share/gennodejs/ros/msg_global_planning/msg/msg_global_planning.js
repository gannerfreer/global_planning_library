// Auto-generated. Do not edit!

// (in-package msg_global_planning.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let msg_common = _finder('msg_common');

//-----------------------------------------------------------

class msg_global_planning {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.target_id = null;
      this.way_point = null;
      this.remote_spd = null;
      this.remote_steering = null;
      this.remote_parking = null;
      this.traj_id = null;
      this.gear_num = null;
      this.carrier_control = null;
      this.turn_light = null;
      this.dipped_light = null;
      this.marker_light = null;
      this.emer_light = null;
      this.trumpet = null;
      this.path_array = null;
    }
    else {
      if (initObj.hasOwnProperty('target_id')) {
        this.target_id = initObj.target_id
      }
      else {
        this.target_id = 0;
      }
      if (initObj.hasOwnProperty('way_point')) {
        this.way_point = initObj.way_point
      }
      else {
        this.way_point = [];
      }
      if (initObj.hasOwnProperty('remote_spd')) {
        this.remote_spd = initObj.remote_spd
      }
      else {
        this.remote_spd = 0.0;
      }
      if (initObj.hasOwnProperty('remote_steering')) {
        this.remote_steering = initObj.remote_steering
      }
      else {
        this.remote_steering = 0.0;
      }
      if (initObj.hasOwnProperty('remote_parking')) {
        this.remote_parking = initObj.remote_parking
      }
      else {
        this.remote_parking = 0.0;
      }
      if (initObj.hasOwnProperty('traj_id')) {
        this.traj_id = initObj.traj_id
      }
      else {
        this.traj_id = 0;
      }
      if (initObj.hasOwnProperty('gear_num')) {
        this.gear_num = initObj.gear_num
      }
      else {
        this.gear_num = 0;
      }
      if (initObj.hasOwnProperty('carrier_control')) {
        this.carrier_control = initObj.carrier_control
      }
      else {
        this.carrier_control = 0;
      }
      if (initObj.hasOwnProperty('turn_light')) {
        this.turn_light = initObj.turn_light
      }
      else {
        this.turn_light = 0;
      }
      if (initObj.hasOwnProperty('dipped_light')) {
        this.dipped_light = initObj.dipped_light
      }
      else {
        this.dipped_light = 0;
      }
      if (initObj.hasOwnProperty('marker_light')) {
        this.marker_light = initObj.marker_light
      }
      else {
        this.marker_light = 0;
      }
      if (initObj.hasOwnProperty('emer_light')) {
        this.emer_light = initObj.emer_light
      }
      else {
        this.emer_light = 0;
      }
      if (initObj.hasOwnProperty('trumpet')) {
        this.trumpet = initObj.trumpet
      }
      else {
        this.trumpet = 0;
      }
      if (initObj.hasOwnProperty('path_array')) {
        this.path_array = initObj.path_array
      }
      else {
        this.path_array = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type msg_global_planning
    // Serialize message field [target_id]
    bufferOffset = _serializer.int32(obj.target_id, buffer, bufferOffset);
    // Serialize message field [way_point]
    // Serialize the length for message field [way_point]
    bufferOffset = _serializer.uint32(obj.way_point.length, buffer, bufferOffset);
    obj.way_point.forEach((val) => {
      bufferOffset = msg_common.msg.WayPoint.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [remote_spd]
    bufferOffset = _serializer.float32(obj.remote_spd, buffer, bufferOffset);
    // Serialize message field [remote_steering]
    bufferOffset = _serializer.float32(obj.remote_steering, buffer, bufferOffset);
    // Serialize message field [remote_parking]
    bufferOffset = _serializer.float32(obj.remote_parking, buffer, bufferOffset);
    // Serialize message field [traj_id]
    bufferOffset = _serializer.uint32(obj.traj_id, buffer, bufferOffset);
    // Serialize message field [gear_num]
    bufferOffset = _serializer.uint8(obj.gear_num, buffer, bufferOffset);
    // Serialize message field [carrier_control]
    bufferOffset = _serializer.uint8(obj.carrier_control, buffer, bufferOffset);
    // Serialize message field [turn_light]
    bufferOffset = _serializer.uint8(obj.turn_light, buffer, bufferOffset);
    // Serialize message field [dipped_light]
    bufferOffset = _serializer.uint8(obj.dipped_light, buffer, bufferOffset);
    // Serialize message field [marker_light]
    bufferOffset = _serializer.uint8(obj.marker_light, buffer, bufferOffset);
    // Serialize message field [emer_light]
    bufferOffset = _serializer.uint8(obj.emer_light, buffer, bufferOffset);
    // Serialize message field [trumpet]
    bufferOffset = _serializer.uint8(obj.trumpet, buffer, bufferOffset);
    // Serialize message field [path_array]
    bufferOffset = _arraySerializer.string(obj.path_array, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type msg_global_planning
    let len;
    let data = new msg_global_planning(null);
    // Deserialize message field [target_id]
    data.target_id = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [way_point]
    // Deserialize array length for message field [way_point]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.way_point = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.way_point[i] = msg_common.msg.WayPoint.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [remote_spd]
    data.remote_spd = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [remote_steering]
    data.remote_steering = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [remote_parking]
    data.remote_parking = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [traj_id]
    data.traj_id = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [gear_num]
    data.gear_num = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [carrier_control]
    data.carrier_control = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [turn_light]
    data.turn_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [dipped_light]
    data.dipped_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [marker_light]
    data.marker_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [emer_light]
    data.emer_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [trumpet]
    data.trumpet = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [path_array]
    data.path_array = _arrayDeserializer.string(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    object.way_point.forEach((val) => {
      length += msg_common.msg.WayPoint.getMessageSize(val);
    });
    object.path_array.forEach((val) => {
      length += 4 + val.length;
    });
    return length + 35;
  }

  static datatype() {
    // Returns string type for a message object
    return 'msg_global_planning/msg_global_planning';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '795e276f86cc7924b4ca1a4fae9f02fc';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 target_id	        #target_id
    msg_common/WayPoint[] way_point		#路径
    float32 remote_spd
    float32 remote_steering
    float32 remote_parking
    uint32 traj_id
    uint8 gear_num 			#档位
    uint8 carrier_control		#货舱控制信号
    uint8 turn_light		#转向灯信号
    uint8 dipped_light		#近光灯信号
    uint8 marker_light		#示廓灯信号
    uint8 emer_light		#紧急信号灯信号
    uint8 trumpet			#喇叭信号
    string[] path_array		#路由路径，成员为区域名 
    
    
    ================================================================================
    MSG: msg_common/WayPoint
    float64 x			#路径x坐标
    float64 y			#路径y坐标
    float64 z			#路径z坐标
    float64 left			#距左边界值
    float64 right			#距右边界值
    float32 heading_angle		#路径的方向
    float32 curvature		#曲率
    float32 speed			#路径的速度
    float32 distance		#路点与路径起点沿路径的距离
    float32 slope			#坡度信息
    uint32  attribute		#属性(0: 进站路段 1: 出站路段 2: 路口路段(圆弧) 3:常规路段)
    float32 speed_limit	        #速度上限
    uint8 direction			#0表示前进，1表示后退
    uint8 waypointattr		#路点属性，1代表是参考路径上的点，2代表混合AStar搜出来的点
    float64 t			#时间
    string area_name		#区域名称	
    string onareaid			#混合AStar搜出来的点为区域名，参考路径上的点为参考路径所在的区域(与点所在的区域无关)	
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new msg_global_planning(null);
    if (msg.target_id !== undefined) {
      resolved.target_id = msg.target_id;
    }
    else {
      resolved.target_id = 0
    }

    if (msg.way_point !== undefined) {
      resolved.way_point = new Array(msg.way_point.length);
      for (let i = 0; i < resolved.way_point.length; ++i) {
        resolved.way_point[i] = msg_common.msg.WayPoint.Resolve(msg.way_point[i]);
      }
    }
    else {
      resolved.way_point = []
    }

    if (msg.remote_spd !== undefined) {
      resolved.remote_spd = msg.remote_spd;
    }
    else {
      resolved.remote_spd = 0.0
    }

    if (msg.remote_steering !== undefined) {
      resolved.remote_steering = msg.remote_steering;
    }
    else {
      resolved.remote_steering = 0.0
    }

    if (msg.remote_parking !== undefined) {
      resolved.remote_parking = msg.remote_parking;
    }
    else {
      resolved.remote_parking = 0.0
    }

    if (msg.traj_id !== undefined) {
      resolved.traj_id = msg.traj_id;
    }
    else {
      resolved.traj_id = 0
    }

    if (msg.gear_num !== undefined) {
      resolved.gear_num = msg.gear_num;
    }
    else {
      resolved.gear_num = 0
    }

    if (msg.carrier_control !== undefined) {
      resolved.carrier_control = msg.carrier_control;
    }
    else {
      resolved.carrier_control = 0
    }

    if (msg.turn_light !== undefined) {
      resolved.turn_light = msg.turn_light;
    }
    else {
      resolved.turn_light = 0
    }

    if (msg.dipped_light !== undefined) {
      resolved.dipped_light = msg.dipped_light;
    }
    else {
      resolved.dipped_light = 0
    }

    if (msg.marker_light !== undefined) {
      resolved.marker_light = msg.marker_light;
    }
    else {
      resolved.marker_light = 0
    }

    if (msg.emer_light !== undefined) {
      resolved.emer_light = msg.emer_light;
    }
    else {
      resolved.emer_light = 0
    }

    if (msg.trumpet !== undefined) {
      resolved.trumpet = msg.trumpet;
    }
    else {
      resolved.trumpet = 0
    }

    if (msg.path_array !== undefined) {
      resolved.path_array = msg.path_array;
    }
    else {
      resolved.path_array = []
    }

    return resolved;
    }
};

module.exports = msg_global_planning;
