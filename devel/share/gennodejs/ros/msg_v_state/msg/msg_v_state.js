// Auto-generated. Do not edit!

// (in-package msg_v_state.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class msg_v_state {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.gps_status = null;
      this.gps_week = null;
      this.gps_time = null;
      this.longitude = null;
      this.latitude = null;
      this.altitude = null;
      this.x = null;
      this.y = null;
      this.z = null;
      this.heading_angle = null;
      this.yaw_angle = null;
      this.yaw_rate = null;
      this.pitch_angle = null;
      this.pitch_rate = null;
      this.roll_angle = null;
      this.roll_rate = null;
      this.spd_east = null;
      this.spd_north = null;
      this.spd_up = null;
      this.spd = null;
      this.spd_lon = null;
      this.spd_lat = null;
      this.acce = null;
      this.acce_lon = null;
      this.acce_lat = null;
      this.static_check = null;
      this.auto_status_mode = null;
      this.auto_status_ready = null;
      this.auto_status_intervene = null;
      this.speed = null;
      this.steering_angle = null;
      this.steer_control_status = null;
      this.steering_spd = null;
      this.wheel_angle = null;
      this.target_steering_angle = null;
      this.trq = null;
      this.target_trq = null;
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
      this.pto_status = null;
      this.brim_state = null;
      this.clean_status = null;
      this.switch_status = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('gps_status')) {
        this.gps_status = initObj.gps_status
      }
      else {
        this.gps_status = 0;
      }
      if (initObj.hasOwnProperty('gps_week')) {
        this.gps_week = initObj.gps_week
      }
      else {
        this.gps_week = 0;
      }
      if (initObj.hasOwnProperty('gps_time')) {
        this.gps_time = initObj.gps_time
      }
      else {
        this.gps_time = 0.0;
      }
      if (initObj.hasOwnProperty('longitude')) {
        this.longitude = initObj.longitude
      }
      else {
        this.longitude = 0.0;
      }
      if (initObj.hasOwnProperty('latitude')) {
        this.latitude = initObj.latitude
      }
      else {
        this.latitude = 0.0;
      }
      if (initObj.hasOwnProperty('altitude')) {
        this.altitude = initObj.altitude
      }
      else {
        this.altitude = 0.0;
      }
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
      if (initObj.hasOwnProperty('heading_angle')) {
        this.heading_angle = initObj.heading_angle
      }
      else {
        this.heading_angle = 0.0;
      }
      if (initObj.hasOwnProperty('yaw_angle')) {
        this.yaw_angle = initObj.yaw_angle
      }
      else {
        this.yaw_angle = 0.0;
      }
      if (initObj.hasOwnProperty('yaw_rate')) {
        this.yaw_rate = initObj.yaw_rate
      }
      else {
        this.yaw_rate = 0.0;
      }
      if (initObj.hasOwnProperty('pitch_angle')) {
        this.pitch_angle = initObj.pitch_angle
      }
      else {
        this.pitch_angle = 0.0;
      }
      if (initObj.hasOwnProperty('pitch_rate')) {
        this.pitch_rate = initObj.pitch_rate
      }
      else {
        this.pitch_rate = 0.0;
      }
      if (initObj.hasOwnProperty('roll_angle')) {
        this.roll_angle = initObj.roll_angle
      }
      else {
        this.roll_angle = 0.0;
      }
      if (initObj.hasOwnProperty('roll_rate')) {
        this.roll_rate = initObj.roll_rate
      }
      else {
        this.roll_rate = 0.0;
      }
      if (initObj.hasOwnProperty('spd_east')) {
        this.spd_east = initObj.spd_east
      }
      else {
        this.spd_east = 0.0;
      }
      if (initObj.hasOwnProperty('spd_north')) {
        this.spd_north = initObj.spd_north
      }
      else {
        this.spd_north = 0.0;
      }
      if (initObj.hasOwnProperty('spd_up')) {
        this.spd_up = initObj.spd_up
      }
      else {
        this.spd_up = 0.0;
      }
      if (initObj.hasOwnProperty('spd')) {
        this.spd = initObj.spd
      }
      else {
        this.spd = 0.0;
      }
      if (initObj.hasOwnProperty('spd_lon')) {
        this.spd_lon = initObj.spd_lon
      }
      else {
        this.spd_lon = 0.0;
      }
      if (initObj.hasOwnProperty('spd_lat')) {
        this.spd_lat = initObj.spd_lat
      }
      else {
        this.spd_lat = 0.0;
      }
      if (initObj.hasOwnProperty('acce')) {
        this.acce = initObj.acce
      }
      else {
        this.acce = 0.0;
      }
      if (initObj.hasOwnProperty('acce_lon')) {
        this.acce_lon = initObj.acce_lon
      }
      else {
        this.acce_lon = 0.0;
      }
      if (initObj.hasOwnProperty('acce_lat')) {
        this.acce_lat = initObj.acce_lat
      }
      else {
        this.acce_lat = 0.0;
      }
      if (initObj.hasOwnProperty('static_check')) {
        this.static_check = initObj.static_check
      }
      else {
        this.static_check = 0;
      }
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
      if (initObj.hasOwnProperty('steering_angle')) {
        this.steering_angle = initObj.steering_angle
      }
      else {
        this.steering_angle = 0.0;
      }
      if (initObj.hasOwnProperty('steer_control_status')) {
        this.steer_control_status = initObj.steer_control_status
      }
      else {
        this.steer_control_status = 0;
      }
      if (initObj.hasOwnProperty('steering_spd')) {
        this.steering_spd = initObj.steering_spd
      }
      else {
        this.steering_spd = 0.0;
      }
      if (initObj.hasOwnProperty('wheel_angle')) {
        this.wheel_angle = initObj.wheel_angle
      }
      else {
        this.wheel_angle = 0.0;
      }
      if (initObj.hasOwnProperty('target_steering_angle')) {
        this.target_steering_angle = initObj.target_steering_angle
      }
      else {
        this.target_steering_angle = 0.0;
      }
      if (initObj.hasOwnProperty('trq')) {
        this.trq = initObj.trq
      }
      else {
        this.trq = 0.0;
      }
      if (initObj.hasOwnProperty('target_trq')) {
        this.target_trq = initObj.target_trq
      }
      else {
        this.target_trq = 0.0;
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
      if (initObj.hasOwnProperty('pto_status')) {
        this.pto_status = initObj.pto_status
      }
      else {
        this.pto_status = 0;
      }
      if (initObj.hasOwnProperty('brim_state')) {
        this.brim_state = initObj.brim_state
      }
      else {
        this.brim_state = 0;
      }
      if (initObj.hasOwnProperty('clean_status')) {
        this.clean_status = initObj.clean_status
      }
      else {
        this.clean_status = [];
      }
      if (initObj.hasOwnProperty('switch_status')) {
        this.switch_status = initObj.switch_status
      }
      else {
        this.switch_status = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type msg_v_state
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [gps_status]
    bufferOffset = _serializer.uint8(obj.gps_status, buffer, bufferOffset);
    // Serialize message field [gps_week]
    bufferOffset = _serializer.int32(obj.gps_week, buffer, bufferOffset);
    // Serialize message field [gps_time]
    bufferOffset = _serializer.float64(obj.gps_time, buffer, bufferOffset);
    // Serialize message field [longitude]
    bufferOffset = _serializer.float64(obj.longitude, buffer, bufferOffset);
    // Serialize message field [latitude]
    bufferOffset = _serializer.float64(obj.latitude, buffer, bufferOffset);
    // Serialize message field [altitude]
    bufferOffset = _serializer.float64(obj.altitude, buffer, bufferOffset);
    // Serialize message field [x]
    bufferOffset = _serializer.float64(obj.x, buffer, bufferOffset);
    // Serialize message field [y]
    bufferOffset = _serializer.float64(obj.y, buffer, bufferOffset);
    // Serialize message field [z]
    bufferOffset = _serializer.float64(obj.z, buffer, bufferOffset);
    // Serialize message field [heading_angle]
    bufferOffset = _serializer.float32(obj.heading_angle, buffer, bufferOffset);
    // Serialize message field [yaw_angle]
    bufferOffset = _serializer.float32(obj.yaw_angle, buffer, bufferOffset);
    // Serialize message field [yaw_rate]
    bufferOffset = _serializer.float32(obj.yaw_rate, buffer, bufferOffset);
    // Serialize message field [pitch_angle]
    bufferOffset = _serializer.float32(obj.pitch_angle, buffer, bufferOffset);
    // Serialize message field [pitch_rate]
    bufferOffset = _serializer.float32(obj.pitch_rate, buffer, bufferOffset);
    // Serialize message field [roll_angle]
    bufferOffset = _serializer.float32(obj.roll_angle, buffer, bufferOffset);
    // Serialize message field [roll_rate]
    bufferOffset = _serializer.float32(obj.roll_rate, buffer, bufferOffset);
    // Serialize message field [spd_east]
    bufferOffset = _serializer.float32(obj.spd_east, buffer, bufferOffset);
    // Serialize message field [spd_north]
    bufferOffset = _serializer.float32(obj.spd_north, buffer, bufferOffset);
    // Serialize message field [spd_up]
    bufferOffset = _serializer.float32(obj.spd_up, buffer, bufferOffset);
    // Serialize message field [spd]
    bufferOffset = _serializer.float32(obj.spd, buffer, bufferOffset);
    // Serialize message field [spd_lon]
    bufferOffset = _serializer.float32(obj.spd_lon, buffer, bufferOffset);
    // Serialize message field [spd_lat]
    bufferOffset = _serializer.float32(obj.spd_lat, buffer, bufferOffset);
    // Serialize message field [acce]
    bufferOffset = _serializer.float32(obj.acce, buffer, bufferOffset);
    // Serialize message field [acce_lon]
    bufferOffset = _serializer.float32(obj.acce_lon, buffer, bufferOffset);
    // Serialize message field [acce_lat]
    bufferOffset = _serializer.float32(obj.acce_lat, buffer, bufferOffset);
    // Serialize message field [static_check]
    bufferOffset = _serializer.char(obj.static_check, buffer, bufferOffset);
    // Serialize message field [auto_status_mode]
    bufferOffset = _serializer.uint8(obj.auto_status_mode, buffer, bufferOffset);
    // Serialize message field [auto_status_ready]
    bufferOffset = _serializer.uint8(obj.auto_status_ready, buffer, bufferOffset);
    // Serialize message field [auto_status_intervene]
    bufferOffset = _serializer.uint8(obj.auto_status_intervene, buffer, bufferOffset);
    // Serialize message field [speed]
    bufferOffset = _serializer.float32(obj.speed, buffer, bufferOffset);
    // Serialize message field [steering_angle]
    bufferOffset = _serializer.float64(obj.steering_angle, buffer, bufferOffset);
    // Serialize message field [steer_control_status]
    bufferOffset = _serializer.uint8(obj.steer_control_status, buffer, bufferOffset);
    // Serialize message field [steering_spd]
    bufferOffset = _serializer.float64(obj.steering_spd, buffer, bufferOffset);
    // Serialize message field [wheel_angle]
    bufferOffset = _serializer.float32(obj.wheel_angle, buffer, bufferOffset);
    // Serialize message field [target_steering_angle]
    bufferOffset = _serializer.float32(obj.target_steering_angle, buffer, bufferOffset);
    // Serialize message field [trq]
    bufferOffset = _serializer.float32(obj.trq, buffer, bufferOffset);
    // Serialize message field [target_trq]
    bufferOffset = _serializer.float32(obj.target_trq, buffer, bufferOffset);
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
    // Serialize message field [pto_status]
    bufferOffset = _serializer.uint8(obj.pto_status, buffer, bufferOffset);
    // Serialize message field [brim_state]
    bufferOffset = _serializer.uint8(obj.brim_state, buffer, bufferOffset);
    // Serialize message field [clean_status]
    bufferOffset = _arraySerializer.bool(obj.clean_status, buffer, bufferOffset, null);
    // Serialize message field [switch_status]
    bufferOffset = _serializer.bool(obj.switch_status, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type msg_v_state
    let len;
    let data = new msg_v_state(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [gps_status]
    data.gps_status = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [gps_week]
    data.gps_week = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [gps_time]
    data.gps_time = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [longitude]
    data.longitude = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [latitude]
    data.latitude = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [altitude]
    data.altitude = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [x]
    data.x = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [y]
    data.y = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [z]
    data.z = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [heading_angle]
    data.heading_angle = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [yaw_angle]
    data.yaw_angle = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [yaw_rate]
    data.yaw_rate = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [pitch_angle]
    data.pitch_angle = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [pitch_rate]
    data.pitch_rate = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [roll_angle]
    data.roll_angle = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [roll_rate]
    data.roll_rate = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [spd_east]
    data.spd_east = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [spd_north]
    data.spd_north = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [spd_up]
    data.spd_up = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [spd]
    data.spd = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [spd_lon]
    data.spd_lon = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [spd_lat]
    data.spd_lat = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [acce]
    data.acce = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [acce_lon]
    data.acce_lon = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [acce_lat]
    data.acce_lat = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [static_check]
    data.static_check = _deserializer.char(buffer, bufferOffset);
    // Deserialize message field [auto_status_mode]
    data.auto_status_mode = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [auto_status_ready]
    data.auto_status_ready = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [auto_status_intervene]
    data.auto_status_intervene = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [speed]
    data.speed = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [steering_angle]
    data.steering_angle = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [steer_control_status]
    data.steer_control_status = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [steering_spd]
    data.steering_spd = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [wheel_angle]
    data.wheel_angle = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [target_steering_angle]
    data.target_steering_angle = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [trq]
    data.trq = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [target_trq]
    data.target_trq = _deserializer.float32(buffer, bufferOffset);
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
    // Deserialize message field [pto_status]
    data.pto_status = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [brim_state]
    data.brim_state = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [clean_status]
    data.clean_status = _arrayDeserializer.bool(buffer, bufferOffset, null)
    // Deserialize message field [switch_status]
    data.switch_status = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += object.clean_status.length;
    return length + 206;
  }

  static datatype() {
    // Returns string type for a message object
    return 'msg_v_state/msg_v_state';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'aa6af63a1ba367c32483e9b79096ee80';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header   header         # ROS time header
    uint8    gps_status
    int32    gps_week
    float64  gps_time
    float64  longitude            
    float64  latitude
    float64  altitude
    float64  x
    float64  y
    float64  z
    float32  heading_angle
    float32  yaw_angle
    float32  yaw_rate
    float32  pitch_angle
    float32  pitch_rate
    float32  roll_angle
    float32  roll_rate
    float32  spd_east
    float32  spd_north
    float32  spd_up
    float32  spd 
    float32  spd_lon
    float32  spd_lat
    float32  acce
    float32  acce_lon
    float32  acce_lat
    char static_check                 # 0:no commend; 1: checking; 2: pass check; 4: check failed
    uint8 auto_status_mode		   	   # 自动驾驶模式: 0,手动;1,自动
    uint8 auto_status_ready		   # 自动驾驶状态准备：0,未就绪;1,就绪
    uint8 auto_status_intervene		   # 自动驾驶状态下有刹车介入：0,无介入;1,有介入
    float32 speed			           # 底层提供的车速
    float64 steering_angle		   # 实际车轮转角
    uint8 steer_control_status	           # 转向控制器状态：0, 待机； 1,自动驾驶模式;4,手动模式;5,驾驶员介入模式
    float64 steering_spd
    float32 wheel_angle
    float32 target_steering_angle
    float32 trq
    float32 target_trq
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
    uint8 pto_status                    #取力器使能状态
    uint8 brim_state                    #帽檐举升状态
    bool[] clean_status              # 传感器状态
    bool switch_status		  #自动驾驶开关状态：0：关闭 1：打开
    
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new msg_v_state(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.gps_status !== undefined) {
      resolved.gps_status = msg.gps_status;
    }
    else {
      resolved.gps_status = 0
    }

    if (msg.gps_week !== undefined) {
      resolved.gps_week = msg.gps_week;
    }
    else {
      resolved.gps_week = 0
    }

    if (msg.gps_time !== undefined) {
      resolved.gps_time = msg.gps_time;
    }
    else {
      resolved.gps_time = 0.0
    }

    if (msg.longitude !== undefined) {
      resolved.longitude = msg.longitude;
    }
    else {
      resolved.longitude = 0.0
    }

    if (msg.latitude !== undefined) {
      resolved.latitude = msg.latitude;
    }
    else {
      resolved.latitude = 0.0
    }

    if (msg.altitude !== undefined) {
      resolved.altitude = msg.altitude;
    }
    else {
      resolved.altitude = 0.0
    }

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

    if (msg.heading_angle !== undefined) {
      resolved.heading_angle = msg.heading_angle;
    }
    else {
      resolved.heading_angle = 0.0
    }

    if (msg.yaw_angle !== undefined) {
      resolved.yaw_angle = msg.yaw_angle;
    }
    else {
      resolved.yaw_angle = 0.0
    }

    if (msg.yaw_rate !== undefined) {
      resolved.yaw_rate = msg.yaw_rate;
    }
    else {
      resolved.yaw_rate = 0.0
    }

    if (msg.pitch_angle !== undefined) {
      resolved.pitch_angle = msg.pitch_angle;
    }
    else {
      resolved.pitch_angle = 0.0
    }

    if (msg.pitch_rate !== undefined) {
      resolved.pitch_rate = msg.pitch_rate;
    }
    else {
      resolved.pitch_rate = 0.0
    }

    if (msg.roll_angle !== undefined) {
      resolved.roll_angle = msg.roll_angle;
    }
    else {
      resolved.roll_angle = 0.0
    }

    if (msg.roll_rate !== undefined) {
      resolved.roll_rate = msg.roll_rate;
    }
    else {
      resolved.roll_rate = 0.0
    }

    if (msg.spd_east !== undefined) {
      resolved.spd_east = msg.spd_east;
    }
    else {
      resolved.spd_east = 0.0
    }

    if (msg.spd_north !== undefined) {
      resolved.spd_north = msg.spd_north;
    }
    else {
      resolved.spd_north = 0.0
    }

    if (msg.spd_up !== undefined) {
      resolved.spd_up = msg.spd_up;
    }
    else {
      resolved.spd_up = 0.0
    }

    if (msg.spd !== undefined) {
      resolved.spd = msg.spd;
    }
    else {
      resolved.spd = 0.0
    }

    if (msg.spd_lon !== undefined) {
      resolved.spd_lon = msg.spd_lon;
    }
    else {
      resolved.spd_lon = 0.0
    }

    if (msg.spd_lat !== undefined) {
      resolved.spd_lat = msg.spd_lat;
    }
    else {
      resolved.spd_lat = 0.0
    }

    if (msg.acce !== undefined) {
      resolved.acce = msg.acce;
    }
    else {
      resolved.acce = 0.0
    }

    if (msg.acce_lon !== undefined) {
      resolved.acce_lon = msg.acce_lon;
    }
    else {
      resolved.acce_lon = 0.0
    }

    if (msg.acce_lat !== undefined) {
      resolved.acce_lat = msg.acce_lat;
    }
    else {
      resolved.acce_lat = 0.0
    }

    if (msg.static_check !== undefined) {
      resolved.static_check = msg.static_check;
    }
    else {
      resolved.static_check = 0
    }

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

    if (msg.steering_angle !== undefined) {
      resolved.steering_angle = msg.steering_angle;
    }
    else {
      resolved.steering_angle = 0.0
    }

    if (msg.steer_control_status !== undefined) {
      resolved.steer_control_status = msg.steer_control_status;
    }
    else {
      resolved.steer_control_status = 0
    }

    if (msg.steering_spd !== undefined) {
      resolved.steering_spd = msg.steering_spd;
    }
    else {
      resolved.steering_spd = 0.0
    }

    if (msg.wheel_angle !== undefined) {
      resolved.wheel_angle = msg.wheel_angle;
    }
    else {
      resolved.wheel_angle = 0.0
    }

    if (msg.target_steering_angle !== undefined) {
      resolved.target_steering_angle = msg.target_steering_angle;
    }
    else {
      resolved.target_steering_angle = 0.0
    }

    if (msg.trq !== undefined) {
      resolved.trq = msg.trq;
    }
    else {
      resolved.trq = 0.0
    }

    if (msg.target_trq !== undefined) {
      resolved.target_trq = msg.target_trq;
    }
    else {
      resolved.target_trq = 0.0
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

    if (msg.pto_status !== undefined) {
      resolved.pto_status = msg.pto_status;
    }
    else {
      resolved.pto_status = 0
    }

    if (msg.brim_state !== undefined) {
      resolved.brim_state = msg.brim_state;
    }
    else {
      resolved.brim_state = 0
    }

    if (msg.clean_status !== undefined) {
      resolved.clean_status = msg.clean_status;
    }
    else {
      resolved.clean_status = []
    }

    if (msg.switch_status !== undefined) {
      resolved.switch_status = msg.switch_status;
    }
    else {
      resolved.switch_status = false
    }

    return resolved;
    }
};

module.exports = msg_v_state;
