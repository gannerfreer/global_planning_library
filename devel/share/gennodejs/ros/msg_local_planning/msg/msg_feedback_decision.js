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

class msg_feedback_decision {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.around_obs_fail = null;
      this.map_update_mode = null;
    }
    else {
      if (initObj.hasOwnProperty('around_obs_fail')) {
        this.around_obs_fail = initObj.around_obs_fail
      }
      else {
        this.around_obs_fail = false;
      }
      if (initObj.hasOwnProperty('map_update_mode')) {
        this.map_update_mode = initObj.map_update_mode
      }
      else {
        this.map_update_mode = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type msg_feedback_decision
    // Serialize message field [around_obs_fail]
    bufferOffset = _serializer.bool(obj.around_obs_fail, buffer, bufferOffset);
    // Serialize message field [map_update_mode]
    bufferOffset = _serializer.uint8(obj.map_update_mode, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type msg_feedback_decision
    let len;
    let data = new msg_feedback_decision(null);
    // Deserialize message field [around_obs_fail]
    data.around_obs_fail = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [map_update_mode]
    data.map_update_mode = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 2;
  }

  static datatype() {
    // Returns string type for a message object
    return 'msg_local_planning/msg_feedback_decision';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '12b29d096902091247ffe8601bfa4f61';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool around_obs_fail #若连续两帧局部轨迹规划自主绕障轨迹是否失败标志位(true:规划失败,false:未规划失败)
    uint8 map_update_mode   #地图更新是否完成(0:未更新 1:更新成功 2:拒绝更新)
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new msg_feedback_decision(null);
    if (msg.around_obs_fail !== undefined) {
      resolved.around_obs_fail = msg.around_obs_fail;
    }
    else {
      resolved.around_obs_fail = false
    }

    if (msg.map_update_mode !== undefined) {
      resolved.map_update_mode = msg.map_update_mode;
    }
    else {
      resolved.map_update_mode = 0
    }

    return resolved;
    }
};

module.exports = msg_feedback_decision;
