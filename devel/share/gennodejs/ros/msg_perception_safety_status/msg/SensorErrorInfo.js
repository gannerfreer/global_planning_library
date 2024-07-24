// Auto-generated. Do not edit!

// (in-package msg_perception_safety_status.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class SensorErrorInfo {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.sensor_type = null;
      this.sensor_id = null;
      this.sensor_name = null;
      this.sensor_position = null;
      this.sensor_main = null;
      this.sensor_error_status = null;
      this.sensor_error_code = null;
    }
    else {
      if (initObj.hasOwnProperty('sensor_type')) {
        this.sensor_type = initObj.sensor_type
      }
      else {
        this.sensor_type = 0;
      }
      if (initObj.hasOwnProperty('sensor_id')) {
        this.sensor_id = initObj.sensor_id
      }
      else {
        this.sensor_id = 0;
      }
      if (initObj.hasOwnProperty('sensor_name')) {
        this.sensor_name = initObj.sensor_name
      }
      else {
        this.sensor_name = '';
      }
      if (initObj.hasOwnProperty('sensor_position')) {
        this.sensor_position = initObj.sensor_position
      }
      else {
        this.sensor_position = 0;
      }
      if (initObj.hasOwnProperty('sensor_main')) {
        this.sensor_main = initObj.sensor_main
      }
      else {
        this.sensor_main = 0;
      }
      if (initObj.hasOwnProperty('sensor_error_status')) {
        this.sensor_error_status = initObj.sensor_error_status
      }
      else {
        this.sensor_error_status = 0;
      }
      if (initObj.hasOwnProperty('sensor_error_code')) {
        this.sensor_error_code = initObj.sensor_error_code
      }
      else {
        this.sensor_error_code = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SensorErrorInfo
    // Serialize message field [sensor_type]
    bufferOffset = _serializer.int32(obj.sensor_type, buffer, bufferOffset);
    // Serialize message field [sensor_id]
    bufferOffset = _serializer.int32(obj.sensor_id, buffer, bufferOffset);
    // Serialize message field [sensor_name]
    bufferOffset = _serializer.string(obj.sensor_name, buffer, bufferOffset);
    // Serialize message field [sensor_position]
    bufferOffset = _serializer.int32(obj.sensor_position, buffer, bufferOffset);
    // Serialize message field [sensor_main]
    bufferOffset = _serializer.int32(obj.sensor_main, buffer, bufferOffset);
    // Serialize message field [sensor_error_status]
    bufferOffset = _serializer.uint8(obj.sensor_error_status, buffer, bufferOffset);
    // Serialize message field [sensor_error_code]
    bufferOffset = _serializer.int32(obj.sensor_error_code, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SensorErrorInfo
    let len;
    let data = new SensorErrorInfo(null);
    // Deserialize message field [sensor_type]
    data.sensor_type = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [sensor_id]
    data.sensor_id = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [sensor_name]
    data.sensor_name = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [sensor_position]
    data.sensor_position = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [sensor_main]
    data.sensor_main = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [sensor_error_status]
    data.sensor_error_status = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [sensor_error_code]
    data.sensor_error_code = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.sensor_name.length;
    return length + 25;
  }

  static datatype() {
    // Returns string type for a message object
    return 'msg_perception_safety_status/SensorErrorInfo';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd982ad46e4ba93bdfb185ecf31af296c';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    const resolved = new SensorErrorInfo(null);
    if (msg.sensor_type !== undefined) {
      resolved.sensor_type = msg.sensor_type;
    }
    else {
      resolved.sensor_type = 0
    }

    if (msg.sensor_id !== undefined) {
      resolved.sensor_id = msg.sensor_id;
    }
    else {
      resolved.sensor_id = 0
    }

    if (msg.sensor_name !== undefined) {
      resolved.sensor_name = msg.sensor_name;
    }
    else {
      resolved.sensor_name = ''
    }

    if (msg.sensor_position !== undefined) {
      resolved.sensor_position = msg.sensor_position;
    }
    else {
      resolved.sensor_position = 0
    }

    if (msg.sensor_main !== undefined) {
      resolved.sensor_main = msg.sensor_main;
    }
    else {
      resolved.sensor_main = 0
    }

    if (msg.sensor_error_status !== undefined) {
      resolved.sensor_error_status = msg.sensor_error_status;
    }
    else {
      resolved.sensor_error_status = 0
    }

    if (msg.sensor_error_code !== undefined) {
      resolved.sensor_error_code = msg.sensor_error_code;
    }
    else {
      resolved.sensor_error_code = 0
    }

    return resolved;
    }
};

module.exports = SensorErrorInfo;
