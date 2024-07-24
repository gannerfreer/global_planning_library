// Auto-generated. Do not edit!

// (in-package msg_lidar_prep.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let LidarPoints = require('./LidarPoints.js');
let msg_common = _finder('msg_common');

//-----------------------------------------------------------

class msg_lidar_prepare {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.lidar_prep = null;
      this.time = null;
    }
    else {
      if (initObj.hasOwnProperty('lidar_prep')) {
        this.lidar_prep = initObj.lidar_prep
      }
      else {
        this.lidar_prep = [];
      }
      if (initObj.hasOwnProperty('time')) {
        this.time = initObj.time
      }
      else {
        this.time = new msg_common.msg.Time();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type msg_lidar_prepare
    // Serialize message field [lidar_prep]
    // Serialize the length for message field [lidar_prep]
    bufferOffset = _serializer.uint32(obj.lidar_prep.length, buffer, bufferOffset);
    obj.lidar_prep.forEach((val) => {
      bufferOffset = LidarPoints.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [time]
    bufferOffset = msg_common.msg.Time.serialize(obj.time, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type msg_lidar_prepare
    let len;
    let data = new msg_lidar_prepare(null);
    // Deserialize message field [lidar_prep]
    // Deserialize array length for message field [lidar_prep]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.lidar_prep = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.lidar_prep[i] = LidarPoints.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [time]
    data.time = msg_common.msg.Time.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 27 * object.lidar_prep.length;
    return length + 12;
  }

  static datatype() {
    // Returns string type for a message object
    return 'msg_lidar_prep/msg_lidar_prepare';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e8cb5446e41407a745c186bd5b1f159a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    LidarPoints[] lidar_prep
    msg_common/Time time
    ================================================================================
    MSG: msg_lidar_prep/LidarPoints
    float32 x #点云x轴坐标，单位m 
    float32 y #点云y轴坐标， 单位m
    float32 z #点云z轴坐标， 单为m
    float32 intensity #激光反射强度信息，数值越大，强度越强
    float32 angle #射线角度单位为度（角度）
    int8 ring #射线编号
    int8 flag  #雷达编号
    float32 distance #点到激光雷达径向距离，单位m
    int8 type #点所属类型，1：透过点（transparent poi）；2：大气；4：地面；8：灰层雨雾
    
    
    ================================================================================
    MSG: msg_common/Time
    int32 sec #秒
    int32 msec #毫秒
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new msg_lidar_prepare(null);
    if (msg.lidar_prep !== undefined) {
      resolved.lidar_prep = new Array(msg.lidar_prep.length);
      for (let i = 0; i < resolved.lidar_prep.length; ++i) {
        resolved.lidar_prep[i] = LidarPoints.Resolve(msg.lidar_prep[i]);
      }
    }
    else {
      resolved.lidar_prep = []
    }

    if (msg.time !== undefined) {
      resolved.time = msg_common.msg.Time.Resolve(msg.time)
    }
    else {
      resolved.time = new msg_common.msg.Time()
    }

    return resolved;
    }
};

module.exports = msg_lidar_prepare;
