// Auto-generated. Do not edit!

// (in-package msg_radar_obj.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let msg_obj = _finder('msg_obj');
let msg_common = _finder('msg_common');

//-----------------------------------------------------------

class msg_radar_obj {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.radar_obj = null;
      this.time = null;
    }
    else {
      if (initObj.hasOwnProperty('radar_obj')) {
        this.radar_obj = initObj.radar_obj
      }
      else {
        this.radar_obj = [];
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
    // Serializes a message object of type msg_radar_obj
    // Serialize message field [radar_obj]
    // Serialize the length for message field [radar_obj]
    bufferOffset = _serializer.uint32(obj.radar_obj.length, buffer, bufferOffset);
    obj.radar_obj.forEach((val) => {
      bufferOffset = msg_obj.msg.Obj.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [time]
    bufferOffset = msg_common.msg.Time.serialize(obj.time, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type msg_radar_obj
    let len;
    let data = new msg_radar_obj(null);
    // Deserialize message field [radar_obj]
    // Deserialize array length for message field [radar_obj]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.radar_obj = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.radar_obj[i] = msg_obj.msg.Obj.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [time]
    data.time = msg_common.msg.Time.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    object.radar_obj.forEach((val) => {
      length += msg_obj.msg.Obj.getMessageSize(val);
    });
    return length + 12;
  }

  static datatype() {
    // Returns string type for a message object
    return 'msg_radar_obj/msg_radar_obj';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '1d70470ad8182acb80bb470a7dca33aa';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    msg_obj/Obj[] radar_obj
    msg_common/Time time
    
    ================================================================================
    MSG: msg_obj/Obj
    float64 x #单位m
    float64 y #单位m
    float64 z #单位m
    float32 vx #单位m/s
    float32 vy #单位m/s
    float32 vz #单位m/s
    float32 width #宽度，单位m
    float32 length #长度，单位m
    float32 height #高度，单位m
    #float64 yaw_angle #横摆脚，角度信息，单位为度
    uint8 track_state #跟踪状态,0：删除或无效；1：新的；2：测量的；3：预测的；4：待删除；5：待跟踪
    uint8 predict_length #预测时长， 单位s
    int32 type #障碍物类型, 0:未知；1：汽车；2：卡车；3：行人；4：摩托车；5自行车；6：大障碍物；7：小障碍物； 8：矿坑； 9：灰尘
    uint32 type_age #障碍物类型时间长度，单位s
    float32 orientation #障碍物形状方位角，单位度，
    float32 bbox_yaw
    float32 bbox_pitch
    float32 bbox_roll
    float32 ax #x轴加速度，单位m/s^2
    float32 ay #y轴加速度，单位m/s^2
    float32 az #z轴加速度，单位m/s^2
    msg_common/Covariance cov     #协方差
    uint8 type_certainty #障碍物类型确信度 0-100
    uint8 obj_certainty #障碍物存在确信度, 0:无效；1：小于0.25；2：小于0.5;3：小于0.75;4：小于0.9;5：小于0.99;6：小于0.999
    int8 source #数据来源编号，预设的传感器编号
    msg_common/GridPoint[] contour_point #obj对象包含的点信息
    uint32 id #跟踪之后给出的最终obj的id
    uint8 absolute_motion #绝对的运动状态，0：未知; 1：静止；2：运动
    uint8 relative_motion #相对车辆的运动状态，0：静止；1:迎面而来；2：远去；3：横越；4:未知
    float32 orientation_rate #方向角速度
    
    ================================================================================
    MSG: msg_common/Covariance
    float32[] value #矩阵值
    int8 row #协方差行
    int8 col #协方差列
    ================================================================================
    MSG: msg_common/GridPoint
    float64 x
    float64 y
    float64 z
    float32 length
    float32 width
    float32 height
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
    const resolved = new msg_radar_obj(null);
    if (msg.radar_obj !== undefined) {
      resolved.radar_obj = new Array(msg.radar_obj.length);
      for (let i = 0; i < resolved.radar_obj.length; ++i) {
        resolved.radar_obj[i] = msg_obj.msg.Obj.Resolve(msg.radar_obj[i]);
      }
    }
    else {
      resolved.radar_obj = []
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

module.exports = msg_radar_obj;
