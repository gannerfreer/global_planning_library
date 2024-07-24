// Auto-generated. Do not edit!

// (in-package msg_imu_prep.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class msg_imu_prep {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.acce_x = null;
      this.acce_y = null;
      this.acce_z = null;
      this.pals_x = null;
      this.pals_y = null;
      this.pals_z = null;
    }
    else {
      if (initObj.hasOwnProperty('acce_x')) {
        this.acce_x = initObj.acce_x
      }
      else {
        this.acce_x = 0.0;
      }
      if (initObj.hasOwnProperty('acce_y')) {
        this.acce_y = initObj.acce_y
      }
      else {
        this.acce_y = 0.0;
      }
      if (initObj.hasOwnProperty('acce_z')) {
        this.acce_z = initObj.acce_z
      }
      else {
        this.acce_z = 0.0;
      }
      if (initObj.hasOwnProperty('pals_x')) {
        this.pals_x = initObj.pals_x
      }
      else {
        this.pals_x = 0.0;
      }
      if (initObj.hasOwnProperty('pals_y')) {
        this.pals_y = initObj.pals_y
      }
      else {
        this.pals_y = 0.0;
      }
      if (initObj.hasOwnProperty('pals_z')) {
        this.pals_z = initObj.pals_z
      }
      else {
        this.pals_z = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type msg_imu_prep
    // Serialize message field [acce_x]
    bufferOffset = _serializer.float32(obj.acce_x, buffer, bufferOffset);
    // Serialize message field [acce_y]
    bufferOffset = _serializer.float32(obj.acce_y, buffer, bufferOffset);
    // Serialize message field [acce_z]
    bufferOffset = _serializer.float32(obj.acce_z, buffer, bufferOffset);
    // Serialize message field [pals_x]
    bufferOffset = _serializer.float32(obj.pals_x, buffer, bufferOffset);
    // Serialize message field [pals_y]
    bufferOffset = _serializer.float32(obj.pals_y, buffer, bufferOffset);
    // Serialize message field [pals_z]
    bufferOffset = _serializer.float32(obj.pals_z, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type msg_imu_prep
    let len;
    let data = new msg_imu_prep(null);
    // Deserialize message field [acce_x]
    data.acce_x = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [acce_y]
    data.acce_y = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [acce_z]
    data.acce_z = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [pals_x]
    data.pals_x = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [pals_y]
    data.pals_y = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [pals_z]
    data.pals_z = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 24;
  }

  static datatype() {
    // Returns string type for a message object
    return 'msg_imu_prep/msg_imu_prep';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '0fea41e4b55f2b301664a8d463d24fcb';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 acce_x		#惯性系下沿x轴加速度 
    float32 acce_y		#惯性系下沿y轴加速度 
    float32 acce_z		#惯性系下沿z轴加速度 
    float32 pals_x		#惯性系下绕x轴角速度 
    float32 pals_y		#惯性系下绕y轴角速度 
    float32 pals_z		#惯性系下绕z轴角速度 
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new msg_imu_prep(null);
    if (msg.acce_x !== undefined) {
      resolved.acce_x = msg.acce_x;
    }
    else {
      resolved.acce_x = 0.0
    }

    if (msg.acce_y !== undefined) {
      resolved.acce_y = msg.acce_y;
    }
    else {
      resolved.acce_y = 0.0
    }

    if (msg.acce_z !== undefined) {
      resolved.acce_z = msg.acce_z;
    }
    else {
      resolved.acce_z = 0.0
    }

    if (msg.pals_x !== undefined) {
      resolved.pals_x = msg.pals_x;
    }
    else {
      resolved.pals_x = 0.0
    }

    if (msg.pals_y !== undefined) {
      resolved.pals_y = msg.pals_y;
    }
    else {
      resolved.pals_y = 0.0
    }

    if (msg.pals_z !== undefined) {
      resolved.pals_z = msg.pals_z;
    }
    else {
      resolved.pals_z = 0.0
    }

    return resolved;
    }
};

module.exports = msg_imu_prep;
