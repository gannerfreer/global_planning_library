// Auto-generated. Do not edit!

// (in-package msg_global_planning.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class msg_report_version {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.str_version = null;
    }
    else {
      if (initObj.hasOwnProperty('str_version')) {
        this.str_version = initObj.str_version
      }
      else {
        this.str_version = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type msg_report_version
    // Serialize message field [str_version]
    bufferOffset = _serializer.string(obj.str_version, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type msg_report_version
    let len;
    let data = new msg_report_version(null);
    // Deserialize message field [str_version]
    data.str_version = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.str_version.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'msg_global_planning/msg_report_version';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '9772dfc007d61d46df9ffce2fef4d876';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string   str_version 	#地图版本
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new msg_report_version(null);
    if (msg.str_version !== undefined) {
      resolved.str_version = msg.str_version;
    }
    else {
      resolved.str_version = ''
    }

    return resolved;
    }
};

module.exports = msg_report_version;
