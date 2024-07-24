// Auto-generated. Do not edit!

// (in-package msg_perception_safety_status.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let SensorErrorInfo = require('./SensorErrorInfo.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class msg_perception_safety_status {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.error_status = null;
      this.sensor_error_info = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('error_status')) {
        this.error_status = initObj.error_status
      }
      else {
        this.error_status = 0;
      }
      if (initObj.hasOwnProperty('sensor_error_info')) {
        this.sensor_error_info = initObj.sensor_error_info
      }
      else {
        this.sensor_error_info = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type msg_perception_safety_status
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [error_status]
    bufferOffset = _serializer.uint8(obj.error_status, buffer, bufferOffset);
    // Serialize message field [sensor_error_info]
    // Serialize the length for message field [sensor_error_info]
    bufferOffset = _serializer.uint32(obj.sensor_error_info.length, buffer, bufferOffset);
    obj.sensor_error_info.forEach((val) => {
      bufferOffset = SensorErrorInfo.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type msg_perception_safety_status
    let len;
    let data = new msg_perception_safety_status(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [error_status]
    data.error_status = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [sensor_error_info]
    // Deserialize array length for message field [sensor_error_info]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.sensor_error_info = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.sensor_error_info[i] = SensorErrorInfo.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    object.sensor_error_info.forEach((val) => {
      length += SensorErrorInfo.getMessageSize(val);
    });
    return length + 5;
  }

  static datatype() {
    // Returns string type for a message object
    return 'msg_perception_safety_status/msg_perception_safety_status';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e0734a6e0d665e44932d6c5009065586';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header              #frame_id为节点名称
    uint8 error_status         #0：正常(心跳信号) n：故障信息个数
    SensorErrorInfo[] sensor_error_info
    
    ================================================================================
    MSG: std_msgs/Header
    # Standard metadata for higher-level stamped data types.
    # This is generally used to communicate timestamped data 
    # in a particular coordinate frame.
    # 
    # sequence ID: consecutively increasing ID 
    uint32 seq
    #Two-integer timestamp that is expressed as:
    # * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
    # * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
    # time-handling sugar is provided by the client library
    time stamp
    #Frame this data is associated with
    string frame_id
    
    ================================================================================
    MSG: msg_perception_safety_status/SensorErrorInfo
    int32   sensor_type  # 1:激光 2:相机 3:毫米波 4:感知融合节点【只有程序故障】
    int32   sensor_id    # 激光雷达按100/101/102 相机按200/201 毫米波按300/301/302 
    string  sensor_name  # 传感器名称，按品牌或厂家；如激光雷达按 "ouster" "leishen"
    int32   sensor_position  # 安装位置 1:front 2:back 3:left 4:right 5:front_left 6:front_right 7:back_left 8:back_right
    int32   sensor_main    # 0: 非主传感器  1: 主传感器
    uint8   sensor_error_status   # 0：正常(心跳信号) 1：异常
    int32   sensor_error_code     # 故障编码如下:
    # 101:  传感器硬件故障，没有原始数据输出
    # 102:  传感器程序故障，没有目标数据输出
    # 103:  传感器表面存在异物遮挡（灰尘泥沙等） --需要清洗 
    # 104:  传感器表面存在水渍 --需要吹风
    # 105:  传感器数据存在损坏现象 --指的是摄像头画面存在异常情况
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new msg_perception_safety_status(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.error_status !== undefined) {
      resolved.error_status = msg.error_status;
    }
    else {
      resolved.error_status = 0
    }

    if (msg.sensor_error_info !== undefined) {
      resolved.sensor_error_info = new Array(msg.sensor_error_info.length);
      for (let i = 0; i < resolved.sensor_error_info.length; ++i) {
        resolved.sensor_error_info[i] = SensorErrorInfo.Resolve(msg.sensor_error_info[i]);
      }
    }
    else {
      resolved.sensor_error_info = []
    }

    return resolved;
    }
};

module.exports = msg_perception_safety_status;
