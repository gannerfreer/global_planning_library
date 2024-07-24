// Auto-generated. Do not edit!

// (in-package msg_v_prep.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class msg_v_prep {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.auto_status_mode = null;
      this.auto_status_ready = null;
      this.auto_status_intervene = null;
      this.speed = null;
      this.steering_angle_left = null;
      this.steering_angle_right = null;
      this.steer_control_status = null;
      this.thr_angle = null;
      this.gear_num = null;
      this.emerg_state = null;
      this.braking_dece = null;
      this.fuel_num = null;
      this.park_brk = null;
      this.carrier_angle = null;
      this.turn_light = null;
      this.dipped_light = null;
      this.marker_light = null;
      this.brake_light = null;
      this.emer_light = null;
      this.backup_light = null;
      this.position_light = null;
      this.carrire_warm_light = null;
      this.illumination_light = null;
      this.trumpet = null;
    }
    else {
      if (initObj.hasOwnProperty('auto_status_mode')) {
        this.auto_status_mode = initObj.auto_status_mode
      }
      else {
        this.auto_status_mode = 0;
      }
      if (initObj.hasOwnProperty('auto_status_ready')) {
        this.auto_status_ready = initObj.auto_status_ready
      }
      else {
        this.auto_status_ready = 0;
      }
      if (initObj.hasOwnProperty('auto_status_intervene')) {
        this.auto_status_intervene = initObj.auto_status_intervene
      }
      else {
        this.auto_status_intervene = 0;
      }
      if (initObj.hasOwnProperty('speed')) {
        this.speed = initObj.speed
      }
      else {
        this.speed = 0.0;
      }
      if (initObj.hasOwnProperty('steering_angle_left')) {
        this.steering_angle_left = initObj.steering_angle_left
      }
      else {
        this.steering_angle_left = 0.0;
      }
      if (initObj.hasOwnProperty('steering_angle_right')) {
        this.steering_angle_right = initObj.steering_angle_right
      }
      else {
        this.steering_angle_right = 0.0;
      }
      if (initObj.hasOwnProperty('steer_control_status')) {
        this.steer_control_status = initObj.steer_control_status
      }
      else {
        this.steer_control_status = 0;
      }
      if (initObj.hasOwnProperty('thr_angle')) {
        this.thr_angle = initObj.thr_angle
      }
      else {
        this.thr_angle = 0.0;
      }
      if (initObj.hasOwnProperty('gear_num')) {
        this.gear_num = initObj.gear_num
      }
      else {
        this.gear_num = 0;
      }
      if (initObj.hasOwnProperty('emerg_state')) {
        this.emerg_state = initObj.emerg_state
      }
      else {
        this.emerg_state = 0;
      }
      if (initObj.hasOwnProperty('braking_dece')) {
        this.braking_dece = initObj.braking_dece
      }
      else {
        this.braking_dece = 0.0;
      }
      if (initObj.hasOwnProperty('fuel_num')) {
        this.fuel_num = initObj.fuel_num
      }
      else {
        this.fuel_num = 0.0;
      }
      if (initObj.hasOwnProperty('park_brk')) {
        this.park_brk = initObj.park_brk
      }
      else {
        this.park_brk = 0;
      }
      if (initObj.hasOwnProperty('carrier_angle')) {
        this.carrier_angle = initObj.carrier_angle
      }
      else {
        this.carrier_angle = 0.0;
      }
      if (initObj.hasOwnProperty('turn_light')) {
        this.turn_light = initObj.turn_light
      }
      else {
        this.turn_light = 0;
      }
      if (initObj.hasOwnProperty('dipped_light')) {
        this.dipped_light = initObj.dipped_light
      }
      else {
        this.dipped_light = 0;
      }
      if (initObj.hasOwnProperty('marker_light')) {
        this.marker_light = initObj.marker_light
      }
      else {
        this.marker_light = 0;
      }
      if (initObj.hasOwnProperty('brake_light')) {
        this.brake_light = initObj.brake_light
      }
      else {
        this.brake_light = 0;
      }
      if (initObj.hasOwnProperty('emer_light')) {
        this.emer_light = initObj.emer_light
      }
      else {
        this.emer_light = 0;
      }
      if (initObj.hasOwnProperty('backup_light')) {
        this.backup_light = initObj.backup_light
      }
      else {
        this.backup_light = 0;
      }
      if (initObj.hasOwnProperty('position_light')) {
        this.position_light = initObj.position_light
      }
      else {
        this.position_light = 0;
      }
      if (initObj.hasOwnProperty('carrire_warm_light')) {
        this.carrire_warm_light = initObj.carrire_warm_light
      }
      else {
        this.carrire_warm_light = 0;
      }
      if (initObj.hasOwnProperty('illumination_light')) {
        this.illumination_light = initObj.illumination_light
      }
      else {
        this.illumination_light = 0;
      }
      if (initObj.hasOwnProperty('trumpet')) {
        this.trumpet = initObj.trumpet
      }
      else {
        this.trumpet = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type msg_v_prep
    // Serialize message field [auto_status_mode]
    bufferOffset = _serializer.uint8(obj.auto_status_mode, buffer, bufferOffset);
    // Serialize message field [auto_status_ready]
    bufferOffset = _serializer.uint8(obj.auto_status_ready, buffer, bufferOffset);
    // Serialize message field [auto_status_intervene]
    bufferOffset = _serializer.uint8(obj.auto_status_intervene, buffer, bufferOffset);
    // Serialize message field [speed]
    bufferOffset = _serializer.float32(obj.speed, buffer, bufferOffset);
    // Serialize message field [steering_angle_left]
    bufferOffset = _serializer.float64(obj.steering_angle_left, buffer, bufferOffset);
    // Serialize message field [steering_angle_right]
    bufferOffset = _serializer.float64(obj.steering_angle_right, buffer, bufferOffset);
    // Serialize message field [steer_control_status]
    bufferOffset = _serializer.uint8(obj.steer_control_status, buffer, bufferOffset);
    // Serialize message field [thr_angle]
    bufferOffset = _serializer.float32(obj.thr_angle, buffer, bufferOffset);
    // Serialize message field [gear_num]
    bufferOffset = _serializer.uint8(obj.gear_num, buffer, bufferOffset);
    // Serialize message field [emerg_state]
    bufferOffset = _serializer.uint8(obj.emerg_state, buffer, bufferOffset);
    // Serialize message field [braking_dece]
    bufferOffset = _serializer.float32(obj.braking_dece, buffer, bufferOffset);
    // Serialize message field [fuel_num]
    bufferOffset = _serializer.float64(obj.fuel_num, buffer, bufferOffset);
    // Serialize message field [park_brk]
    bufferOffset = _serializer.uint8(obj.park_brk, buffer, bufferOffset);
    // Serialize message field [carrier_angle]
    bufferOffset = _serializer.float32(obj.carrier_angle, buffer, bufferOffset);
    // Serialize message field [turn_light]
    bufferOffset = _serializer.uint8(obj.turn_light, buffer, bufferOffset);
    // Serialize message field [dipped_light]
    bufferOffset = _serializer.uint8(obj.dipped_light, buffer, bufferOffset);
    // Serialize message field [marker_light]
    bufferOffset = _serializer.uint8(obj.marker_light, buffer, bufferOffset);
    // Serialize message field [brake_light]
    bufferOffset = _serializer.uint8(obj.brake_light, buffer, bufferOffset);
    // Serialize message field [emer_light]
    bufferOffset = _serializer.uint8(obj.emer_light, buffer, bufferOffset);
    // Serialize message field [backup_light]
    bufferOffset = _serializer.uint8(obj.backup_light, buffer, bufferOffset);
    // Serialize message field [position_light]
    bufferOffset = _serializer.uint8(obj.position_light, buffer, bufferOffset);
    // Serialize message field [carrire_warm_light]
    bufferOffset = _serializer.uint8(obj.carrire_warm_light, buffer, bufferOffset);
    // Serialize message field [illumination_light]
    bufferOffset = _serializer.uint8(obj.illumination_light, buffer, bufferOffset);
    // Serialize message field [trumpet]
    bufferOffset = _serializer.uint8(obj.trumpet, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type msg_v_prep
    let len;
    let data = new msg_v_prep(null);
    // Deserialize message field [auto_status_mode]
    data.auto_status_mode = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [auto_status_ready]
    data.auto_status_ready = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [auto_status_intervene]
    data.auto_status_intervene = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [speed]
    data.speed = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [steering_angle_left]
    data.steering_angle_left = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [steering_angle_right]
    data.steering_angle_right = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [steer_control_status]
    data.steer_control_status = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [thr_angle]
    data.thr_angle = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [gear_num]
    data.gear_num = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [emerg_state]
    data.emerg_state = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [braking_dece]
    data.braking_dece = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [fuel_num]
    data.fuel_num = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [park_brk]
    data.park_brk = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [carrier_angle]
    data.carrier_angle = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [turn_light]
    data.turn_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [dipped_light]
    data.dipped_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [marker_light]
    data.marker_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [brake_light]
    data.brake_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [emer_light]
    data.emer_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [backup_light]
    data.backup_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [position_light]
    data.position_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [carrire_warm_light]
    data.carrire_warm_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [illumination_light]
    data.illumination_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [trumpet]
    data.trumpet = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 57;
  }

  static datatype() {
    // Returns string type for a message object
    return 'msg_v_prep/msg_v_prep';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '7290758742e9103ad10d343f24df155c';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 auto_status_mode		   	   # 自动驾驶模式: 0,手动;1,自动
    uint8 auto_status_ready		   # 自动驾驶状态准备：0,未就绪;1,就绪
    uint8 auto_status_intervene		   # 自动驾驶状态下有刹车介入：0,无介入;1,有介入
    float32 speed			           # 底层提供的车速
    float64 steering_angle_left		   # 实际车轮转角
    float64 steering_angle_right	           # 实际车轮转角
    uint8 steer_control_status	           # 转向控制器状态：0, 待机； 1,自动驾驶模式; 2~3保留;4,手动模式;5,驾驶员介入模式;6,警告模式；警告系统还在工作，有电助力，自动驾驶不执行; 7, 错误模式；错误模式，故障比较严重，系统停止工作；
    float32 thr_angle			   # 实际油门开度
    uint8 gear_num			           # 实际档位：0,P;1,R;2,D;3,N
    uint8 emerg_state			   # 紧急制动状态
    float32 braking_dece		           # 制动减速度
    float64 fuel_num			   # 燃油状态（剩余油量）
    uint8 park_brk			           # 驻车制动状态： 0, 无驻车制动;1, 在驻车制动中
    float32 carrier_angle		           # 货舱举升角度
    uint8 turn_light			   # 转向灯状态
    uint8 dipped_light			   # 远、近光灯状态
    uint8 marker_light			   # 示廓灯/前雾灯状态
    uint8 brake_light			   # 刹车灯状态
    uint8 emer_light			   # 紧急信号灯状态
    uint8 backup_light 		           # 倒车灯信号
    uint8 position_light		           # 位置灯信号
    uint8 carrire_warm_light		   # 举升警告灯信号
    uint8 illumination_light		   # 照明灯信号
    uint8 trumpet			           # 喇叭信号
    
    
    
    
    
    
    
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new msg_v_prep(null);
    if (msg.auto_status_mode !== undefined) {
      resolved.auto_status_mode = msg.auto_status_mode;
    }
    else {
      resolved.auto_status_mode = 0
    }

    if (msg.auto_status_ready !== undefined) {
      resolved.auto_status_ready = msg.auto_status_ready;
    }
    else {
      resolved.auto_status_ready = 0
    }

    if (msg.auto_status_intervene !== undefined) {
      resolved.auto_status_intervene = msg.auto_status_intervene;
    }
    else {
      resolved.auto_status_intervene = 0
    }

    if (msg.speed !== undefined) {
      resolved.speed = msg.speed;
    }
    else {
      resolved.speed = 0.0
    }

    if (msg.steering_angle_left !== undefined) {
      resolved.steering_angle_left = msg.steering_angle_left;
    }
    else {
      resolved.steering_angle_left = 0.0
    }

    if (msg.steering_angle_right !== undefined) {
      resolved.steering_angle_right = msg.steering_angle_right;
    }
    else {
      resolved.steering_angle_right = 0.0
    }

    if (msg.steer_control_status !== undefined) {
      resolved.steer_control_status = msg.steer_control_status;
    }
    else {
      resolved.steer_control_status = 0
    }

    if (msg.thr_angle !== undefined) {
      resolved.thr_angle = msg.thr_angle;
    }
    else {
      resolved.thr_angle = 0.0
    }

    if (msg.gear_num !== undefined) {
      resolved.gear_num = msg.gear_num;
    }
    else {
      resolved.gear_num = 0
    }

    if (msg.emerg_state !== undefined) {
      resolved.emerg_state = msg.emerg_state;
    }
    else {
      resolved.emerg_state = 0
    }

    if (msg.braking_dece !== undefined) {
      resolved.braking_dece = msg.braking_dece;
    }
    else {
      resolved.braking_dece = 0.0
    }

    if (msg.fuel_num !== undefined) {
      resolved.fuel_num = msg.fuel_num;
    }
    else {
      resolved.fuel_num = 0.0
    }

    if (msg.park_brk !== undefined) {
      resolved.park_brk = msg.park_brk;
    }
    else {
      resolved.park_brk = 0
    }

    if (msg.carrier_angle !== undefined) {
      resolved.carrier_angle = msg.carrier_angle;
    }
    else {
      resolved.carrier_angle = 0.0
    }

    if (msg.turn_light !== undefined) {
      resolved.turn_light = msg.turn_light;
    }
    else {
      resolved.turn_light = 0
    }

    if (msg.dipped_light !== undefined) {
      resolved.dipped_light = msg.dipped_light;
    }
    else {
      resolved.dipped_light = 0
    }

    if (msg.marker_light !== undefined) {
      resolved.marker_light = msg.marker_light;
    }
    else {
      resolved.marker_light = 0
    }

    if (msg.brake_light !== undefined) {
      resolved.brake_light = msg.brake_light;
    }
    else {
      resolved.brake_light = 0
    }

    if (msg.emer_light !== undefined) {
      resolved.emer_light = msg.emer_light;
    }
    else {
      resolved.emer_light = 0
    }

    if (msg.backup_light !== undefined) {
      resolved.backup_light = msg.backup_light;
    }
    else {
      resolved.backup_light = 0
    }

    if (msg.position_light !== undefined) {
      resolved.position_light = msg.position_light;
    }
    else {
      resolved.position_light = 0
    }

    if (msg.carrire_warm_light !== undefined) {
      resolved.carrire_warm_light = msg.carrire_warm_light;
    }
    else {
      resolved.carrire_warm_light = 0
    }

    if (msg.illumination_light !== undefined) {
      resolved.illumination_light = msg.illumination_light;
    }
    else {
      resolved.illumination_light = 0
    }

    if (msg.trumpet !== undefined) {
      resolved.trumpet = msg.trumpet;
    }
    else {
      resolved.trumpet = 0
    }

    return resolved;
    }
};

module.exports = msg_v_prep;
