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

class Covariance {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.value = null;
      this.row = null;
      this.col = null;
    }
    else {
      if (initObj.hasOwnProperty('value')) {
        this.value = initObj.value
      }
      else {
        this.value = [];
      }
      if (initObj.hasOwnProperty('row')) {
        this.row = initObj.row
      }
      else {
        this.row = 0;
      }
      if (initObj.hasOwnProperty('col')) {
        this.col = initObj.col
      }
      else {
        this.col = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Covariance
    // Serialize message field [value]
    bufferOffset = _arraySerializer.float32(obj.value, buffer, bufferOffset, null);
    // Serialize message field [row]
    bufferOffset = _serializer.int8(obj.row, buffer, bufferOffset);
    // Serialize message field [col]
    bufferOffset = _serializer.int8(obj.col, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Covariance
    let len;
    let data = new Covariance(null);
    // Deserialize message field [value]
    data.value = _arrayDeserializer.float32(buffer, bufferOffset, null)
    // Deserialize message field [row]
    data.row = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [col]
    data.col = _deserializer.int8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 4 * object.value.length;
    return length + 6;
  }

  static datatype() {
    // Returns string type for a message object
    return 'msg_common/Covariance';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '44d99f5dfbfdb9bd3d5ab1ee2f4b0fcd';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32[] value #矩阵值
    int8 row #协方差行
    int8 col #协方差列
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Covariance(null);
    if (msg.value !== undefined) {
      resolved.value = msg.value;
    }
    else {
      resolved.value = []
    }

    if (msg.row !== undefined) {
      resolved.row = msg.row;
    }
    else {
      resolved.row = 0
    }

    if (msg.col !== undefined) {
      resolved.col = msg.col;
    }
    else {
      resolved.col = 0
    }

    return resolved;
    }
};

module.exports = Covariance;
