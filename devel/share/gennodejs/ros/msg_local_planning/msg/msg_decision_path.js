// Auto-generated. Do not edit!

// (in-package msg_local_planning.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let Trajectory = require('./Trajectory.js');

//-----------------------------------------------------------

class msg_decision_path {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.driving_mode = null;
      this.control_mode = null;
      this.gear_num = null;
      this.turn_light = null;
      this.dipped_light = null;
      this.marker_light = null;
      this.illumination_light = null;
      this.brake_light = null;
      this.backup_light = null;
      this.position_light = null;
      this.carrire_warm_light = null;
      this.trumpet = null;
      this.carrier_control = null;
      this.park_brk = null;
      this.way_point = null;
      this.remote_spd = null;
      this.remote_steering = null;
      this.remote_parking = null;
      this.brim_control = null;
      this.carrire_enable = null;
      this.is_clean = null;
    }
    else {
      if (initObj.hasOwnProperty('driving_mode')) {
        this.driving_mode = initObj.driving_mode
      }
      else {
        this.driving_mode = 0;
      }
      if (initObj.hasOwnProperty('control_mode')) {
        this.control_mode = initObj.control_mode
      }
      else {
        this.control_mode = 0;
      }
      if (initObj.hasOwnProperty('gear_num')) {
        this.gear_num = initObj.gear_num
      }
      else {
        this.gear_num = 0;
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
      if (initObj.hasOwnProperty('illumination_light')) {
        this.illumination_light = initObj.illumination_light
      }
      else {
        this.illumination_light = 0;
      }
      if (initObj.hasOwnProperty('brake_light')) {
        this.brake_light = initObj.brake_light
      }
      else {
        this.brake_light = 0;
      }
      if (initObj.hasOwnProperty('backup_light')) {
        this.backup_light = initObj.backup_light
      }
      else {
        this.backup_light = 0;
      }
      if (initObj.hasOwnProperty('position_light')) {
        this.position_light = initObj.position_light
      }
      else {
        this.position_light = 0;
      }
      if (initObj.hasOwnProperty('carrire_warm_light')) {
        this.carrire_warm_light = initObj.carrire_warm_light
      }
      else {
        this.carrire_warm_light = 0;
      }
      if (initObj.hasOwnProperty('trumpet')) {
        this.trumpet = initObj.trumpet
      }
      else {
        this.trumpet = 0;
      }
      if (initObj.hasOwnProperty('carrier_control')) {
        this.carrier_control = initObj.carrier_control
      }
      else {
        this.carrier_control = 0;
      }
      if (initObj.hasOwnProperty('park_brk')) {
        this.park_brk = initObj.park_brk
      }
      else {
        this.park_brk = 0;
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
      if (initObj.hasOwnProperty('brim_control')) {
        this.brim_control = initObj.brim_control
      }
      else {
        this.brim_control = 0;
      }
      if (initObj.hasOwnProperty('carrire_enable')) {
        this.carrire_enable = initObj.carrire_enable
      }
      else {
        this.carrire_enable = 0;
      }
      if (initObj.hasOwnProperty('is_clean')) {
        this.is_clean = initObj.is_clean
      }
      else {
        this.is_clean = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type msg_decision_path
    // Serialize message field [driving_mode]
    bufferOffset = _serializer.uint8(obj.driving_mode, buffer, bufferOffset);
    // Serialize message field [control_mode]
    bufferOffset = _serializer.uint8(obj.control_mode, buffer, bufferOffset);
    // Serialize message field [gear_num]
    bufferOffset = _serializer.uint8(obj.gear_num, buffer, bufferOffset);
    // Serialize message field [turn_light]
    bufferOffset = _serializer.uint8(obj.turn_light, buffer, bufferOffset);
    // Serialize message field [dipped_light]
    bufferOffset = _serializer.uint8(obj.dipped_light, buffer, bufferOffset);
    // Serialize message field [marker_light]
    bufferOffset = _serializer.uint8(obj.marker_light, buffer, bufferOffset);
    // Serialize message field [illumination_light]
    bufferOffset = _serializer.uint8(obj.illumination_light, buffer, bufferOffset);
    // Serialize message field [brake_light]
    bufferOffset = _serializer.uint8(obj.brake_light, buffer, bufferOffset);
    // Serialize message field [backup_light]
    bufferOffset = _serializer.uint8(obj.backup_light, buffer, bufferOffset);
    // Serialize message field [position_light]
    bufferOffset = _serializer.uint8(obj.position_light, buffer, bufferOffset);
    // Serialize message field [carrire_warm_light]
    bufferOffset = _serializer.uint8(obj.carrire_warm_light, buffer, bufferOffset);
    // Serialize message field [trumpet]
    bufferOffset = _serializer.uint8(obj.trumpet, buffer, bufferOffset);
    // Serialize message field [carrier_control]
    bufferOffset = _serializer.uint8(obj.carrier_control, buffer, bufferOffset);
    // Serialize message field [park_brk]
    bufferOffset = _serializer.uint8(obj.park_brk, buffer, bufferOffset);
    // Serialize message field [way_point]
    // Serialize the length for message field [way_point]
    bufferOffset = _serializer.uint32(obj.way_point.length, buffer, bufferOffset);
    obj.way_point.forEach((val) => {
      bufferOffset = Trajectory.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [remote_spd]
    bufferOffset = _serializer.float32(obj.remote_spd, buffer, bufferOffset);
    // Serialize message field [remote_steering]
    bufferOffset = _serializer.float32(obj.remote_steering, buffer, bufferOffset);
    // Serialize message field [remote_parking]
    bufferOffset = _serializer.float32(obj.remote_parking, buffer, bufferOffset);
    // Serialize message field [brim_control]
    bufferOffset = _serializer.uint8(obj.brim_control, buffer, bufferOffset);
    // Serialize message field [carrire_enable]
    bufferOffset = _serializer.uint8(obj.carrire_enable, buffer, bufferOffset);
    // Serialize message field [is_clean]
    bufferOffset = _arraySerializer.bool(obj.is_clean, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type msg_decision_path
    let len;
    let data = new msg_decision_path(null);
    // Deserialize message field [driving_mode]
    data.driving_mode = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [control_mode]
    data.control_mode = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [gear_num]
    data.gear_num = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [turn_light]
    data.turn_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [dipped_light]
    data.dipped_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [marker_light]
    data.marker_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [illumination_light]
    data.illumination_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [brake_light]
    data.brake_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [backup_light]
    data.backup_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [position_light]
    data.position_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [carrire_warm_light]
    data.carrire_warm_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [trumpet]
    data.trumpet = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [carrier_control]
    data.carrier_control = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [park_brk]
    data.park_brk = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [way_point]
    // Deserialize array length for message field [way_point]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.way_point = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.way_point[i] = Trajectory.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [remote_spd]
    data.remote_spd = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [remote_steering]
    data.remote_steering = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [remote_parking]
    data.remote_parking = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [brim_control]
    data.brim_control = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [carrire_enable]
    data.carrire_enable = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [is_clean]
    data.is_clean = _arrayDeserializer.bool(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 59 * object.way_point.length;
    length += object.is_clean.length;
    return length + 36;
  }

  static datatype() {
    // Returns string type for a message object
    return 'msg_local_planning/msg_decision_path';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '54b308deafb0ce6e10e7a93bbd478773';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 driving_mode                # 0：人工驾驶；1：自动驾驶
    uint8 control_mode                # 控制模式
    uint8 gear_num			          # 期望档位
    uint8 turn_light		          # 转向灯信号
    uint8 dipped_light		          # 远、近光灯信号
    uint8 marker_light		          # 示廓灯信号/前雾灯
    uint8 illumination_light	      # 照明灯信号
    uint8 brake_light                 # 刹车灯信号
    uint8 backup_light		          # 倒车灯信号
    uint8 position_light		      # 位置灯信号
    uint8 carrire_warm_light	      # 举升警告灯信号
    uint8 trumpet			          # 喇叭信号
    uint8 carrier_control	          # 货舱控制信号
    uint8 park_brk			          # 驻车制动信号
    Trajectory[] way_point
    float32 remote_spd
    float32 remote_steering
    float32 remote_parking
    uint8 brim_control	   # 帽沿控制信号
    uint8 carrire_enable	   # 举升系统控制使能信号
    bool[] is_clean
    
    ================================================================================
    MSG: msg_local_planning/Trajectory
    float64 x
    float64 y
    float64 z
    float32 yaw
    float32 curvature
    float32 limiting_speed
    uint8 protection_level
    float32 speed
    float32 distance
    float32 left_distance
    float32 right_distance
    float32 slope
    uint16 attribute
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new msg_decision_path(null);
    if (msg.driving_mode !== undefined) {
      resolved.driving_mode = msg.driving_mode;
    }
    else {
      resolved.driving_mode = 0
    }

    if (msg.control_mode !== undefined) {
      resolved.control_mode = msg.control_mode;
    }
    else {
      resolved.control_mode = 0
    }

    if (msg.gear_num !== undefined) {
      resolved.gear_num = msg.gear_num;
    }
    else {
      resolved.gear_num = 0
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

    if (msg.illumination_light !== undefined) {
      resolved.illumination_light = msg.illumination_light;
    }
    else {
      resolved.illumination_light = 0
    }

    if (msg.brake_light !== undefined) {
      resolved.brake_light = msg.brake_light;
    }
    else {
      resolved.brake_light = 0
    }

    if (msg.backup_light !== undefined) {
      resolved.backup_light = msg.backup_light;
    }
    else {
      resolved.backup_light = 0
    }

    if (msg.position_light !== undefined) {
      resolved.position_light = msg.position_light;
    }
    else {
      resolved.position_light = 0
    }

    if (msg.carrire_warm_light !== undefined) {
      resolved.carrire_warm_light = msg.carrire_warm_light;
    }
    else {
      resolved.carrire_warm_light = 0
    }

    if (msg.trumpet !== undefined) {
      resolved.trumpet = msg.trumpet;
    }
    else {
      resolved.trumpet = 0
    }

    if (msg.carrier_control !== undefined) {
      resolved.carrier_control = msg.carrier_control;
    }
    else {
      resolved.carrier_control = 0
    }

    if (msg.park_brk !== undefined) {
      resolved.park_brk = msg.park_brk;
    }
    else {
      resolved.park_brk = 0
    }

    if (msg.way_point !== undefined) {
      resolved.way_point = new Array(msg.way_point.length);
      for (let i = 0; i < resolved.way_point.length; ++i) {
        resolved.way_point[i] = Trajectory.Resolve(msg.way_point[i]);
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

    if (msg.brim_control !== undefined) {
      resolved.brim_control = msg.brim_control;
    }
    else {
      resolved.brim_control = 0
    }

    if (msg.carrire_enable !== undefined) {
      resolved.carrire_enable = msg.carrire_enable;
    }
    else {
      resolved.carrire_enable = 0
    }

    if (msg.is_clean !== undefined) {
      resolved.is_clean = msg.is_clean;
    }
    else {
      resolved.is_clean = []
    }

    return resolved;
    }
};

module.exports = msg_decision_path;
