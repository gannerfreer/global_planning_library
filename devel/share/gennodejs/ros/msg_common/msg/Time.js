// Auto-generated. Do not edit!

// (in-package msg_common.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class Time {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.sec = null;
      this.msec = null;
    }
    else {
      if (initObj.hasOwnProperty('sec')) {
        this.sec = initObj.sec
      }
      else {
        this.sec = 0;
      }
      if (initObj.hasOwnProperty('msec')) {
        this.msec = initObj.msec
      }
      else {
        this.msec = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Time
    // Serialize message field [sec]
    bufferOffset = _serializer.int32(obj.sec, buffer, bufferOffset);
    // Serialize message field [msec]
    bufferOffset = _serializer.int32(obj.msec, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Time
    let len;
    let data = new Time(null);
    // Deserialize message field [sec]
    data.sec = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [msec]
    data.msec = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'msg_common/Time';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '88168c0d4ea41e2694b150b06dd17988';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 sec #秒
    int32 msec #毫秒
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Time(null);
    if (msg.sec !== undefined) {
      resolved.sec = msg.sec;
    }
    else {
      resolved.sec = 0
    }

    if (msg.msec !== undefined) {
      resolved.msec = msg.msec;
    }
    else {
      resolved.msec = 0
    }

    return resolved;
    }
};

module.exports = Time;
