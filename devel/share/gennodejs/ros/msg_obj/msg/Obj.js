// Auto-generated. Do not edit!

// (in-package msg_obj.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let msg_common = _finder('msg_common');

//-----------------------------------------------------------

class Obj {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.x = null;
      this.y = null;
      this.z = null;
      this.vx = null;
      this.vy = null;
      this.vz = null;
      this.width = null;
      this.length = null;
      this.height = null;
      this.track_state = null;
      this.predict_length = null;
      this.type = null;
      this.type_age = null;
      this.orientation = null;
      this.bbox_yaw = null;
      this.bbox_pitch = null;
      this.bbox_roll = null;
      this.ax = null;
      this.ay = null;
      this.az = null;
      this.cov = null;
      this.type_certainty = null;
      this.obj_certainty = null;
      this.source = null;
      this.contour_point = null;
      this.id = null;
      this.absolute_motion = null;
      this.relative_motion = null;
      this.orientation_rate = null;
    }
    else {
      if (initObj.hasOwnProperty('x')) {
        this.x = initObj.x
      }
      else {
        this.x = 0.0;
      }
      if (initObj.hasOwnProperty('y')) {
        this.y = initObj.y
      }
      else {
        this.y = 0.0;
      }
      if (initObj.hasOwnProperty('z')) {
        this.z = initObj.z
      }
      else {
        this.z = 0.0;
      }
      if (initObj.hasOwnProperty('vx')) {
        this.vx = initObj.vx
      }
      else {
        this.vx = 0.0;
      }
      if (initObj.hasOwnProperty('vy')) {
        this.vy = initObj.vy
      }
      else {
        this.vy = 0.0;
      }
      if (initObj.hasOwnProperty('vz')) {
        this.vz = initObj.vz
      }
      else {
        this.vz = 0.0;
      }
      if (initObj.hasOwnProperty('width')) {
        this.width = initObj.width
      }
      else {
        this.width = 0.0;
      }
      if (initObj.hasOwnProperty('length')) {
        this.length = initObj.length
      }
      else {
        this.length = 0.0;
      }
      if (initObj.hasOwnProperty('height')) {
        this.height = initObj.height
      }
      else {
        this.height = 0.0;
      }
      if (initObj.hasOwnProperty('track_state')) {
        this.track_state = initObj.track_state
      }
      else {
        this.track_state = 0;
      }
      if (initObj.hasOwnProperty('predict_length')) {
        this.predict_length = initObj.predict_length
      }
      else {
        this.predict_length = 0;
      }
      if (initObj.hasOwnProperty('type')) {
        this.type = initObj.type
      }
      else {
        this.type = 0;
      }
      if (initObj.hasOwnProperty('type_age')) {
        this.type_age = initObj.type_age
      }
      else {
        this.type_age = 0;
      }
      if (initObj.hasOwnProperty('orientation')) {
        this.orientation = initObj.orientation
      }
      else {
        this.orientation = 0.0;
      }
      if (initObj.hasOwnProperty('bbox_yaw')) {
        this.bbox_yaw = initObj.bbox_yaw
      }
      else {
        this.bbox_yaw = 0.0;
      }
      if (initObj.hasOwnProperty('bbox_pitch')) {
        this.bbox_pitch = initObj.bbox_pitch
      }
      else {
        this.bbox_pitch = 0.0;
      }
      if (initObj.hasOwnProperty('bbox_roll')) {
        this.bbox_roll = initObj.bbox_roll
      }
      else {
        this.bbox_roll = 0.0;
      }
      if (initObj.hasOwnProperty('ax')) {
        this.ax = initObj.ax
      }
      else {
        this.ax = 0.0;
      }
      if (initObj.hasOwnProperty('ay')) {
        this.ay = initObj.ay
      }
      else {
        this.ay = 0.0;
      }
      if (initObj.hasOwnProperty('az')) {
        this.az = initObj.az
      }
      else {
        this.az = 0.0;
      }
      if (initObj.hasOwnProperty('cov')) {
        this.cov = initObj.cov
      }
      else {
        this.cov = new msg_common.msg.Covariance();
      }
      if (initObj.hasOwnProperty('type_certainty')) {
        this.type_certainty = initObj.type_certainty
      }
      else {
        this.type_certainty = 0;
      }
      if (initObj.hasOwnProperty('obj_certainty')) {
        this.obj_certainty = initObj.obj_certainty
      }
      else {
        this.obj_certainty = 0;
      }
      if (initObj.hasOwnProperty('source')) {
        this.source = initObj.source
      }
      else {
        this.source = 0;
      }
      if (initObj.hasOwnProperty('contour_point')) {
        this.contour_point = initObj.contour_point
      }
      else {
        this.contour_point = [];
      }
      if (initObj.hasOwnProperty('id')) {
        this.id = initObj.id
      }
      else {
        this.id = 0;
      }
      if (initObj.hasOwnProperty('absolute_motion')) {
        this.absolute_motion = initObj.absolute_motion
      }
      else {
        this.absolute_motion = 0;
      }
      if (initObj.hasOwnProperty('relative_motion')) {
        this.relative_motion = initObj.relative_motion
      }
      else {
        this.relative_motion = 0;
      }
      if (initObj.hasOwnProperty('orientation_rate')) {
        this.orientation_rate = initObj.orientation_rate
      }
      else {
        this.orientation_rate = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Obj
    // Serialize message field [x]
    bufferOffset = _serializer.float64(obj.x, buffer, bufferOffset);
    // Serialize message field [y]
    bufferOffset = _serializer.float64(obj.y, buffer, bufferOffset);
    // Serialize message field [z]
    bufferOffset = _serializer.float64(obj.z, buffer, bufferOffset);
    // Serialize message field [vx]
    bufferOffset = _serializer.float32(obj.vx, buffer, bufferOffset);
    // Serialize message field [vy]
    bufferOffset = _serializer.float32(obj.vy, buffer, bufferOffset);
    // Serialize message field [vz]
    bufferOffset = _serializer.float32(obj.vz, buffer, bufferOffset);
    // Serialize message field [width]
    bufferOffset = _serializer.float32(obj.width, buffer, bufferOffset);
    // Serialize message field [length]
    bufferOffset = _serializer.float32(obj.length, buffer, bufferOffset);
    // Serialize message field [height]
    bufferOffset = _serializer.float32(obj.height, buffer, bufferOffset);
    // Serialize message field [track_state]
    bufferOffset = _serializer.uint8(obj.track_state, buffer, bufferOffset);
    // Serialize message field [predict_length]
    bufferOffset = _serializer.uint8(obj.predict_length, buffer, bufferOffset);
    // Serialize message field [type]
    bufferOffset = _serializer.int32(obj.type, buffer, bufferOffset);
    // Serialize message field [type_age]
    bufferOffset = _serializer.uint32(obj.type_age, buffer, bufferOffset);
    // Serialize message field [orientation]
    bufferOffset = _serializer.float32(obj.orientation, buffer, bufferOffset);
    // Serialize message field [bbox_yaw]
    bufferOffset = _serializer.float32(obj.bbox_yaw, buffer, bufferOffset);
    // Serialize message field [bbox_pitch]
    bufferOffset = _serializer.float32(obj.bbox_pitch, buffer, bufferOffset);
    // Serialize message field [bbox_roll]
    bufferOffset = _serializer.float32(obj.bbox_roll, buffer, bufferOffset);
    // Serialize message field [ax]
    bufferOffset = _serializer.float32(obj.ax, buffer, bufferOffset);
    // Serialize message field [ay]
    bufferOffset = _serializer.float32(obj.ay, buffer, bufferOffset);
    // Serialize message field [az]
    bufferOffset = _serializer.float32(obj.az, buffer, bufferOffset);
    // Serialize message field [cov]
    bufferOffset = msg_common.msg.Covariance.serialize(obj.cov, buffer, bufferOffset);
    // Serialize message field [type_certainty]
    bufferOffset = _serializer.uint8(obj.type_certainty, buffer, bufferOffset);
    // Serialize message field [obj_certainty]
    bufferOffset = _serializer.uint8(obj.obj_certainty, buffer, bufferOffset);
    // Serialize message field [source]
    bufferOffset = _serializer.int8(obj.source, buffer, bufferOffset);
    // Serialize message field [contour_point]
    // Serialize the length for message field [contour_point]
    bufferOffset = _serializer.uint32(obj.contour_point.length, buffer, bufferOffset);
    obj.contour_point.forEach((val) => {
      bufferOffset = msg_common.msg.GridPoint.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [id]
    bufferOffset = _serializer.uint32(obj.id, buffer, bufferOffset);
    // Serialize message field [absolute_motion]
    bufferOffset = _serializer.uint8(obj.absolute_motion, buffer, bufferOffset);
    // Serialize message field [relative_motion]
    bufferOffset = _serializer.uint8(obj.relative_motion, buffer, bufferOffset);
    // Serialize message field [orientation_rate]
    bufferOffset = _serializer.float32(obj.orientation_rate, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Obj
    let len;
    let data = new Obj(null);
    // Deserialize message field [x]
    data.x = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [y]
    data.y = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [z]
    data.z = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [vx]
    data.vx = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [vy]
    data.vy = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [vz]
    data.vz = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [width]
    data.width = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [length]
    data.length = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [height]
    data.height = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [track_state]
    data.track_state = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [predict_length]
    data.predict_length = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [type]
    data.type = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [type_age]
    data.type_age = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [orientation]
    data.orientation = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [bbox_yaw]
    data.bbox_yaw = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [bbox_pitch]
    data.bbox_pitch = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [bbox_roll]
    data.bbox_roll = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [ax]
    data.ax = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [ay]
    data.ay = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [az]
    data.az = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [cov]
    data.cov = msg_common.msg.Covariance.deserialize(buffer, bufferOffset);
    // Deserialize message field [type_certainty]
    data.type_certainty = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [obj_certainty]
    data.obj_certainty = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [source]
    data.source = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [contour_point]
    // Deserialize array length for message field [contour_point]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.contour_point = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.contour_point[i] = msg_common.msg.GridPoint.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [id]
    data.id = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [absolute_motion]
    data.absolute_motion = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [relative_motion]
    data.relative_motion = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [orientation_rate]
    data.orientation_rate = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += msg_common.msg.Covariance.getMessageSize(object.cov);
    length += 36 * object.contour_point.length;
    return length + 103;
  }

  static datatype() {
    // Returns string type for a message object
    return 'msg_obj/Obj';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'eaf612e7800921f7863714bc6541d95c';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Obj(null);
    if (msg.x !== undefined) {
      resolved.x = msg.x;
    }
    else {
      resolved.x = 0.0
    }

    if (msg.y !== undefined) {
      resolved.y = msg.y;
    }
    else {
      resolved.y = 0.0
    }

    if (msg.z !== undefined) {
      resolved.z = msg.z;
    }
    else {
      resolved.z = 0.0
    }

    if (msg.vx !== undefined) {
      resolved.vx = msg.vx;
    }
    else {
      resolved.vx = 0.0
    }

    if (msg.vy !== undefined) {
      resolved.vy = msg.vy;
    }
    else {
      resolved.vy = 0.0
    }

    if (msg.vz !== undefined) {
      resolved.vz = msg.vz;
    }
    else {
      resolved.vz = 0.0
    }

    if (msg.width !== undefined) {
      resolved.width = msg.width;
    }
    else {
      resolved.width = 0.0
    }

    if (msg.length !== undefined) {
      resolved.length = msg.length;
    }
    else {
      resolved.length = 0.0
    }

    if (msg.height !== undefined) {
      resolved.height = msg.height;
    }
    else {
      resolved.height = 0.0
    }

    if (msg.track_state !== undefined) {
      resolved.track_state = msg.track_state;
    }
    else {
      resolved.track_state = 0
    }

    if (msg.predict_length !== undefined) {
      resolved.predict_length = msg.predict_length;
    }
    else {
      resolved.predict_length = 0
    }

    if (msg.type !== undefined) {
      resolved.type = msg.type;
    }
    else {
      resolved.type = 0
    }

    if (msg.type_age !== undefined) {
      resolved.type_age = msg.type_age;
    }
    else {
      resolved.type_age = 0
    }

    if (msg.orientation !== undefined) {
      resolved.orientation = msg.orientation;
    }
    else {
      resolved.orientation = 0.0
    }

    if (msg.bbox_yaw !== undefined) {
      resolved.bbox_yaw = msg.bbox_yaw;
    }
    else {
      resolved.bbox_yaw = 0.0
    }

    if (msg.bbox_pitch !== undefined) {
      resolved.bbox_pitch = msg.bbox_pitch;
    }
    else {
      resolved.bbox_pitch = 0.0
    }

    if (msg.bbox_roll !== undefined) {
      resolved.bbox_roll = msg.bbox_roll;
    }
    else {
      resolved.bbox_roll = 0.0
    }

    if (msg.ax !== undefined) {
      resolved.ax = msg.ax;
    }
    else {
      resolved.ax = 0.0
    }

    if (msg.ay !== undefined) {
      resolved.ay = msg.ay;
    }
    else {
      resolved.ay = 0.0
    }

    if (msg.az !== undefined) {
      resolved.az = msg.az;
    }
    else {
      resolved.az = 0.0
    }

    if (msg.cov !== undefined) {
      resolved.cov = msg_common.msg.Covariance.Resolve(msg.cov)
    }
    else {
      resolved.cov = new msg_common.msg.Covariance()
    }

    if (msg.type_certainty !== undefined) {
      resolved.type_certainty = msg.type_certainty;
    }
    else {
      resolved.type_certainty = 0
    }

    if (msg.obj_certainty !== undefined) {
      resolved.obj_certainty = msg.obj_certainty;
    }
    else {
      resolved.obj_certainty = 0
    }

    if (msg.source !== undefined) {
      resolved.source = msg.source;
    }
    else {
      resolved.source = 0
    }

    if (msg.contour_point !== undefined) {
      resolved.contour_point = new Array(msg.contour_point.length);
      for (let i = 0; i < resolved.contour_point.length; ++i) {
        resolved.contour_point[i] = msg_common.msg.GridPoint.Resolve(msg.contour_point[i]);
      }
    }
    else {
      resolved.contour_point = []
    }

    if (msg.id !== undefined) {
      resolved.id = msg.id;
    }
    else {
      resolved.id = 0
    }

    if (msg.absolute_motion !== undefined) {
      resolved.absolute_motion = msg.absolute_motion;
    }
    else {
      resolved.absolute_motion = 0
    }

    if (msg.relative_motion !== undefined) {
      resolved.relative_motion = msg.relative_motion;
    }
    else {
      resolved.relative_motion = 0
    }

    if (msg.orientation_rate !== undefined) {
      resolved.orientation_rate = msg.orientation_rate;
    }
    else {
      resolved.orientation_rate = 0.0
    }

    return resolved;
    }
};

module.exports = Obj;
