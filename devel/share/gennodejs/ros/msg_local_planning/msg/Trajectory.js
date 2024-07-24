// Auto-generated. Do not edit!

// (in-package msg_local_planning.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class Trajectory {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.x = null;
      this.y = null;
      this.z = null;
      this.yaw = null;
      this.curvature = null;
      this.limiting_speed = null;
      this.protection_level = null;
      this.speed = null;
      this.distance = null;
      this.left_distance = null;
      this.right_distance = null;
      this.slope = null;
      this.attribute = null;
    }
    else {
      if (initObj.hasOwnProperty('x')) {
        this.x = initObj.x
      }
      else {
        this.x = 0.0;
      }
      if (initObj.hasOwnProperty('y')) {
        this.y = initObj.y
      }
      else {
        this.y = 0.0;
      }
      if (initObj.hasOwnProperty('z')) {
        this.z = initObj.z
      }
      else {
        this.z = 0.0;
      }
      if (initObj.hasOwnProperty('yaw')) {
        this.yaw = initObj.yaw
      }
      else {
        this.yaw = 0.0;
      }
      if (initObj.hasOwnProperty('curvature')) {
        this.curvature = initObj.curvature
      }
      else {
        this.curvature = 0.0;
      }
      if (initObj.hasOwnProperty('limiting_speed')) {
        this.limiting_speed = initObj.limiting_speed
      }
      else {
        this.limiting_speed = 0.0;
      }
      if (initObj.hasOwnProperty('protection_level')) {
        this.protection_level = initObj.protection_level
      }
      else {
        this.protection_level = 0;
      }
      if (initObj.hasOwnProperty('speed')) {
        this.speed = initObj.speed
      }
      else {
        this.speed = 0.0;
      }
      if (initObj.hasOwnProperty('distance')) {
        this.distance = initObj.distance
      }
      else {
        this.distance = 0.0;
      }
      if (initObj.hasOwnProperty('left_distance')) {
        this.left_distance = initObj.left_distance
      }
      else {
        this.left_distance = 0.0;
      }
      if (initObj.hasOwnProperty('right_distance')) {
        this.right_distance = initObj.right_distance
      }
      else {
        this.right_distance = 0.0;
      }
      if (initObj.hasOwnProperty('slope')) {
        this.slope = initObj.slope
      }
      else {
        this.slope = 0.0;
      }
      if (initObj.hasOwnProperty('attribute')) {
        this.attribute = initObj.attribute
      }
      else {
        this.attribute = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Trajectory
    // Serialize message field [x]
    bufferOffset = _serializer.float64(obj.x, buffer, bufferOffset);
    // Serialize message field [y]
    bufferOffset = _serializer.float64(obj.y, buffer, bufferOffset);
    // Serialize message field [z]
    bufferOffset = _serializer.float64(obj.z, buffer, bufferOffset);
    // Serialize message field [yaw]
    bufferOffset = _serializer.float32(obj.yaw, buffer, bufferOffset);
    // Serialize message field [curvature]
    bufferOffset = _serializer.float32(obj.curvature, buffer, bufferOffset);
    // Serialize message field [limiting_speed]
    bufferOffset = _serializer.float32(obj.limiting_speed, buffer, bufferOffset);
    // Serialize message field [protection_level]
    bufferOffset = _serializer.uint8(obj.protection_level, buffer, bufferOffset);
    // Serialize message field [speed]
    bufferOffset = _serializer.float32(obj.speed, buffer, bufferOffset);
    // Serialize message field [distance]
    bufferOffset = _serializer.float32(obj.distance, buffer, bufferOffset);
    // Serialize message field [left_distance]
    bufferOffset = _serializer.float32(obj.left_distance, buffer, bufferOffset);
    // Serialize message field [right_distance]
    bufferOffset = _serializer.float32(obj.right_distance, buffer, bufferOffset);
    // Serialize message field [slope]
    bufferOffset = _serializer.float32(obj.slope, buffer, bufferOffset);
    // Serialize message field [attribute]
    bufferOffset = _serializer.uint16(obj.attribute, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Trajectory
    let len;
    let data = new Trajectory(null);
    // Deserialize message field [x]
    data.x = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [y]
    data.y = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [z]
    data.z = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [yaw]
    data.yaw = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [curvature]
    data.curvature = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [limiting_speed]
    data.limiting_speed = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [protection_level]
    data.protection_level = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [speed]
    data.speed = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [distance]
    data.distance = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [left_distance]
    data.left_distance = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [right_distance]
    data.right_distance = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [slope]
    data.slope = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [attribute]
    data.attribute = _deserializer.uint16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 59;
  }

  static datatype() {
    // Returns string type for a message object
    return 'msg_local_planning/Trajectory';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '8ea21636fe9505811bcbecfba008fdf6';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    const resolved = new Trajectory(null);
    if (msg.x !== undefined) {
      resolved.x = msg.x;
    }
    else {
      resolved.x = 0.0
    }

    if (msg.y !== undefined) {
      resolved.y = msg.y;
    }
    else {
      resolved.y = 0.0
    }

    if (msg.z !== undefined) {
      resolved.z = msg.z;
    }
    else {
      resolved.z = 0.0
    }

    if (msg.yaw !== undefined) {
      resolved.yaw = msg.yaw;
    }
    else {
      resolved.yaw = 0.0
    }

    if (msg.curvature !== undefined) {
      resolved.curvature = msg.curvature;
    }
    else {
      resolved.curvature = 0.0
    }

    if (msg.limiting_speed !== undefined) {
      resolved.limiting_speed = msg.limiting_speed;
    }
    else {
      resolved.limiting_speed = 0.0
    }

    if (msg.protection_level !== undefined) {
      resolved.protection_level = msg.protection_level;
    }
    else {
      resolved.protection_level = 0
    }

    if (msg.speed !== undefined) {
      resolved.speed = msg.speed;
    }
    else {
      resolved.speed = 0.0
    }

    if (msg.distance !== undefined) {
      resolved.distance = msg.distance;
    }
    else {
      resolved.distance = 0.0
    }

    if (msg.left_distance !== undefined) {
      resolved.left_distance = msg.left_distance;
    }
    else {
      resolved.left_distance = 0.0
    }

    if (msg.right_distance !== undefined) {
      resolved.right_distance = msg.right_distance;
    }
    else {
      resolved.right_distance = 0.0
    }

    if (msg.slope !== undefined) {
      resolved.slope = msg.slope;
    }
    else {
      resolved.slope = 0.0
    }

    if (msg.attribute !== undefined) {
      resolved.attribute = msg.attribute;
    }
    else {
      resolved.attribute = 0
    }

    return resolved;
    }
};

module.exports = Trajectory;
