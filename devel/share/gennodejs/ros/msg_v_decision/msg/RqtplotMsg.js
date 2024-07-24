// Auto-generated. Do not edit!

// (in-package msg_v_decision.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class RqtplotMsg {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.selfspeed = null;
      this.frontspeed = null;
      this.dis2front = null;
      this.desiredspeed = null;
      this.global_speed = null;
      this.dis2vehicle = null;
      this.dis2obstacle = null;
    }
    else {
      if (initObj.hasOwnProperty('selfspeed')) {
        this.selfspeed = initObj.selfspeed
      }
      else {
        this.selfspeed = 0.0;
      }
      if (initObj.hasOwnProperty('frontspeed')) {
        this.frontspeed = initObj.frontspeed
      }
      else {
        this.frontspeed = 0.0;
      }
      if (initObj.hasOwnProperty('dis2front')) {
        this.dis2front = initObj.dis2front
      }
      else {
        this.dis2front = 0.0;
      }
      if (initObj.hasOwnProperty('desiredspeed')) {
        this.desiredspeed = initObj.desiredspeed
      }
      else {
        this.desiredspeed = 0.0;
      }
      if (initObj.hasOwnProperty('global_speed')) {
        this.global_speed = initObj.global_speed
      }
      else {
        this.global_speed = 0.0;
      }
      if (initObj.hasOwnProperty('dis2vehicle')) {
        this.dis2vehicle = initObj.dis2vehicle
      }
      else {
        this.dis2vehicle = 0.0;
      }
      if (initObj.hasOwnProperty('dis2obstacle')) {
        this.dis2obstacle = initObj.dis2obstacle
      }
      else {
        this.dis2obstacle = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type RqtplotMsg
    // Serialize message field [selfspeed]
    bufferOffset = _serializer.float32(obj.selfspeed, buffer, bufferOffset);
    // Serialize message field [frontspeed]
    bufferOffset = _serializer.float32(obj.frontspeed, buffer, bufferOffset);
    // Serialize message field [dis2front]
    bufferOffset = _serializer.float32(obj.dis2front, buffer, bufferOffset);
    // Serialize message field [desiredspeed]
    bufferOffset = _serializer.float32(obj.desiredspeed, buffer, bufferOffset);
    // Serialize message field [global_speed]
    bufferOffset = _serializer.float32(obj.global_speed, buffer, bufferOffset);
    // Serialize message field [dis2vehicle]
    bufferOffset = _serializer.float32(obj.dis2vehicle, buffer, bufferOffset);
    // Serialize message field [dis2obstacle]
    bufferOffset = _serializer.float32(obj.dis2obstacle, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type RqtplotMsg
    let len;
    let data = new RqtplotMsg(null);
    // Deserialize message field [selfspeed]
    data.selfspeed = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [frontspeed]
    data.frontspeed = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [dis2front]
    data.dis2front = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [desiredspeed]
    data.desiredspeed = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [global_speed]
    data.global_speed = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [dis2vehicle]
    data.dis2vehicle = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [dis2obstacle]
    data.dis2obstacle = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 28;
  }

  static datatype() {
    // Returns string type for a message object
    return 'msg_v_decision/RqtplotMsg';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '74b462951a3217bd8dcef08e73ccad53';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 selfspeed    #自车速度 km/h
    float32 frontspeed   #前车速度 km/h
    float32 dis2front    #自车与前车距离 m
    float32 desiredspeed #期望速度 km/h
    float32 global_speed #全局速度 km/h
    float32 dis2vehicle  #车辆与全局路径的最小横向距离差值
    float32 dis2obstacle #目标障碍物最近点最小横向距离差值
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new RqtplotMsg(null);
    if (msg.selfspeed !== undefined) {
      resolved.selfspeed = msg.selfspeed;
    }
    else {
      resolved.selfspeed = 0.0
    }

    if (msg.frontspeed !== undefined) {
      resolved.frontspeed = msg.frontspeed;
    }
    else {
      resolved.frontspeed = 0.0
    }

    if (msg.dis2front !== undefined) {
      resolved.dis2front = msg.dis2front;
    }
    else {
      resolved.dis2front = 0.0
    }

    if (msg.desiredspeed !== undefined) {
      resolved.desiredspeed = msg.desiredspeed;
    }
    else {
      resolved.desiredspeed = 0.0
    }

    if (msg.global_speed !== undefined) {
      resolved.global_speed = msg.global_speed;
    }
    else {
      resolved.global_speed = 0.0
    }

    if (msg.dis2vehicle !== undefined) {
      resolved.dis2vehicle = msg.dis2vehicle;
    }
    else {
      resolved.dis2vehicle = 0.0
    }

    if (msg.dis2obstacle !== undefined) {
      resolved.dis2obstacle = msg.dis2obstacle;
    }
    else {
      resolved.dis2obstacle = 0.0
    }

    return resolved;
    }
};

module.exports = RqtplotMsg;
