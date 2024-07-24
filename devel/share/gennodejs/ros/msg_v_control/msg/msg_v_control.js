// Auto-generated. Do not edit!

// (in-package msg_v_control.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class msg_v_control {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.static_check = null;
      this.steering_angle = null;
      this.steering_spd = null;
      this.thr_angle = null;
      this.brake_pressure = null;
      this.brk_current = null;
      this.flag = null;
      this.engine_ctr = null;
      this.park_brk = null;
      this.load_brk = null;
      this.carrier_control = null;
      this.dumpbed_ctr = null;
      this.turn_light = null;
      this.gear_num = null;
      this.gear_cmd = null;
      this.gear_flag = null;
      this.gear_cleardriver = null;
      this.dipped_light = null;
      this.marker_light = null;
      this.brake_light = null;
      this.emer_light = null;
      this.trumpet = null;
      this.state_light = null;
      this.rest_off_ctr = null;
      this.lube_ctr = null;
      this.auto_cmd = null;
      this.override_cmd = null;
      this.light_ctr = null;
    }
    else {
      if (initObj.hasOwnProperty('static_check')) {
        this.static_check = initObj.static_check
      }
      else {
        this.static_check = 0;
      }
      if (initObj.hasOwnProperty('steering_angle')) {
        this.steering_angle = initObj.steering_angle
      }
      else {
        this.steering_angle = 0.0;
      }
      if (initObj.hasOwnProperty('steering_spd')) {
        this.steering_spd = initObj.steering_spd
      }
      else {
        this.steering_spd = 0.0;
      }
      if (initObj.hasOwnProperty('thr_angle')) {
        this.thr_angle = initObj.thr_angle
      }
      else {
        this.thr_angle = 0;
      }
      if (initObj.hasOwnProperty('brake_pressure')) {
        this.brake_pressure = initObj.brake_pressure
      }
      else {
        this.brake_pressure = 0.0;
      }
      if (initObj.hasOwnProperty('brk_current')) {
        this.brk_current = initObj.brk_current
      }
      else {
        this.brk_current = 0.0;
      }
      if (initObj.hasOwnProperty('flag')) {
        this.flag = initObj.flag
      }
      else {
        this.flag = 0;
      }
      if (initObj.hasOwnProperty('engine_ctr')) {
        this.engine_ctr = initObj.engine_ctr
      }
      else {
        this.engine_ctr = 0;
      }
      if (initObj.hasOwnProperty('park_brk')) {
        this.park_brk = initObj.park_brk
      }
      else {
        this.park_brk = 0;
      }
      if (initObj.hasOwnProperty('load_brk')) {
        this.load_brk = initObj.load_brk
      }
      else {
        this.load_brk = 0;
      }
      if (initObj.hasOwnProperty('carrier_control')) {
        this.carrier_control = initObj.carrier_control
      }
      else {
        this.carrier_control = 0;
      }
      if (initObj.hasOwnProperty('dumpbed_ctr')) {
        this.dumpbed_ctr = initObj.dumpbed_ctr
      }
      else {
        this.dumpbed_ctr = 0.0;
      }
      if (initObj.hasOwnProperty('turn_light')) {
        this.turn_light = initObj.turn_light
      }
      else {
        this.turn_light = 0;
      }
      if (initObj.hasOwnProperty('gear_num')) {
        this.gear_num = initObj.gear_num
      }
      else {
        this.gear_num = 0;
      }
      if (initObj.hasOwnProperty('gear_cmd')) {
        this.gear_cmd = initObj.gear_cmd
      }
      else {
        this.gear_cmd = 0;
      }
      if (initObj.hasOwnProperty('gear_flag')) {
        this.gear_flag = initObj.gear_flag
      }
      else {
        this.gear_flag = 0;
      }
      if (initObj.hasOwnProperty('gear_cleardriver')) {
        this.gear_cleardriver = initObj.gear_cleardriver
      }
      else {
        this.gear_cleardriver = 0;
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
      if (initObj.hasOwnProperty('trumpet')) {
        this.trumpet = initObj.trumpet
      }
      else {
        this.trumpet = 0;
      }
      if (initObj.hasOwnProperty('state_light')) {
        this.state_light = initObj.state_light
      }
      else {
        this.state_light = 0;
      }
      if (initObj.hasOwnProperty('rest_off_ctr')) {
        this.rest_off_ctr = initObj.rest_off_ctr
      }
      else {
        this.rest_off_ctr = 0;
      }
      if (initObj.hasOwnProperty('lube_ctr')) {
        this.lube_ctr = initObj.lube_ctr
      }
      else {
        this.lube_ctr = 0;
      }
      if (initObj.hasOwnProperty('auto_cmd')) {
        this.auto_cmd = initObj.auto_cmd
      }
      else {
        this.auto_cmd = 0;
      }
      if (initObj.hasOwnProperty('override_cmd')) {
        this.override_cmd = initObj.override_cmd
      }
      else {
        this.override_cmd = 0;
      }
      if (initObj.hasOwnProperty('light_ctr')) {
        this.light_ctr = initObj.light_ctr
      }
      else {
        this.light_ctr = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type msg_v_control
    // Serialize message field [static_check]
    bufferOffset = _serializer.char(obj.static_check, buffer, bufferOffset);
    // Serialize message field [steering_angle]
    bufferOffset = _serializer.float64(obj.steering_angle, buffer, bufferOffset);
    // Serialize message field [steering_spd]
    bufferOffset = _serializer.float64(obj.steering_spd, buffer, bufferOffset);
    // Serialize message field [thr_angle]
    bufferOffset = _serializer.int32(obj.thr_angle, buffer, bufferOffset);
    // Serialize message field [brake_pressure]
    bufferOffset = _serializer.float32(obj.brake_pressure, buffer, bufferOffset);
    // Serialize message field [brk_current]
    bufferOffset = _serializer.float32(obj.brk_current, buffer, bufferOffset);
    // Serialize message field [flag]
    bufferOffset = _serializer.char(obj.flag, buffer, bufferOffset);
    // Serialize message field [engine_ctr]
    bufferOffset = _serializer.char(obj.engine_ctr, buffer, bufferOffset);
    // Serialize message field [park_brk]
    bufferOffset = _serializer.char(obj.park_brk, buffer, bufferOffset);
    // Serialize message field [load_brk]
    bufferOffset = _serializer.char(obj.load_brk, buffer, bufferOffset);
    // Serialize message field [carrier_control]
    bufferOffset = _serializer.char(obj.carrier_control, buffer, bufferOffset);
    // Serialize message field [dumpbed_ctr]
    bufferOffset = _serializer.float32(obj.dumpbed_ctr, buffer, bufferOffset);
    // Serialize message field [turn_light]
    bufferOffset = _serializer.char(obj.turn_light, buffer, bufferOffset);
    // Serialize message field [gear_num]
    bufferOffset = _serializer.int32(obj.gear_num, buffer, bufferOffset);
    // Serialize message field [gear_cmd]
    bufferOffset = _serializer.int32(obj.gear_cmd, buffer, bufferOffset);
    // Serialize message field [gear_flag]
    bufferOffset = _serializer.int32(obj.gear_flag, buffer, bufferOffset);
    // Serialize message field [gear_cleardriver]
    bufferOffset = _serializer.int32(obj.gear_cleardriver, buffer, bufferOffset);
    // Serialize message field [dipped_light]
    bufferOffset = _serializer.char(obj.dipped_light, buffer, bufferOffset);
    // Serialize message field [marker_light]
    bufferOffset = _serializer.char(obj.marker_light, buffer, bufferOffset);
    // Serialize message field [brake_light]
    bufferOffset = _serializer.char(obj.brake_light, buffer, bufferOffset);
    // Serialize message field [emer_light]
    bufferOffset = _serializer.char(obj.emer_light, buffer, bufferOffset);
    // Serialize message field [trumpet]
    bufferOffset = _serializer.char(obj.trumpet, buffer, bufferOffset);
    // Serialize message field [state_light]
    bufferOffset = _serializer.char(obj.state_light, buffer, bufferOffset);
    // Serialize message field [rest_off_ctr]
    bufferOffset = _serializer.char(obj.rest_off_ctr, buffer, bufferOffset);
    // Serialize message field [lube_ctr]
    bufferOffset = _serializer.char(obj.lube_ctr, buffer, bufferOffset);
    // Serialize message field [auto_cmd]
    bufferOffset = _serializer.char(obj.auto_cmd, buffer, bufferOffset);
    // Serialize message field [override_cmd]
    bufferOffset = _serializer.char(obj.override_cmd, buffer, bufferOffset);
    // Serialize message field [light_ctr]
    bufferOffset = _serializer.char(obj.light_ctr, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type msg_v_control
    let len;
    let data = new msg_v_control(null);
    // Deserialize message field [static_check]
    data.static_check = _deserializer.char(buffer, bufferOffset);
    // Deserialize message field [steering_angle]
    data.steering_angle = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [steering_spd]
    data.steering_spd = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [thr_angle]
    data.thr_angle = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [brake_pressure]
    data.brake_pressure = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [brk_current]
    data.brk_current = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [flag]
    data.flag = _deserializer.char(buffer, bufferOffset);
    // Deserialize message field [engine_ctr]
    data.engine_ctr = _deserializer.char(buffer, bufferOffset);
    // Deserialize message field [park_brk]
    data.park_brk = _deserializer.char(buffer, bufferOffset);
    // Deserialize message field [load_brk]
    data.load_brk = _deserializer.char(buffer, bufferOffset);
    // Deserialize message field [carrier_control]
    data.carrier_control = _deserializer.char(buffer, bufferOffset);
    // Deserialize message field [dumpbed_ctr]
    data.dumpbed_ctr = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [turn_light]
    data.turn_light = _deserializer.char(buffer, bufferOffset);
    // Deserialize message field [gear_num]
    data.gear_num = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [gear_cmd]
    data.gear_cmd = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [gear_flag]
    data.gear_flag = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [gear_cleardriver]
    data.gear_cleardriver = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [dipped_light]
    data.dipped_light = _deserializer.char(buffer, bufferOffset);
    // Deserialize message field [marker_light]
    data.marker_light = _deserializer.char(buffer, bufferOffset);
    // Deserialize message field [brake_light]
    data.brake_light = _deserializer.char(buffer, bufferOffset);
    // Deserialize message field [emer_light]
    data.emer_light = _deserializer.char(buffer, bufferOffset);
    // Deserialize message field [trumpet]
    data.trumpet = _deserializer.char(buffer, bufferOffset);
    // Deserialize message field [state_light]
    data.state_light = _deserializer.char(buffer, bufferOffset);
    // Deserialize message field [rest_off_ctr]
    data.rest_off_ctr = _deserializer.char(buffer, bufferOffset);
    // Deserialize message field [lube_ctr]
    data.lube_ctr = _deserializer.char(buffer, bufferOffset);
    // Deserialize message field [auto_cmd]
    data.auto_cmd = _deserializer.char(buffer, bufferOffset);
    // Deserialize message field [override_cmd]
    data.override_cmd = _deserializer.char(buffer, bufferOffset);
    // Deserialize message field [light_ctr]
    data.light_ctr = _deserializer.char(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 66;
  }

  static datatype() {
    // Returns string type for a message object
    return 'msg_v_control/msg_v_control';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '22edec3cff924e8fcb908dbc10ac7aff';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    char static_check                 # 0:no commend; 1: checking; 2: pass check; 4: check failed
    float64 steering_angle            # Steering angle. Unit: deg.
    float64 steering_spd              # Steering speed. Unit: deg/s.
    int32 thr_angle                   # Throttle angle. Unit: %.
    float32 brake_pressure            # Brake pressure. Unit: MPa.
    float32 brk_current               # Unit: %.
    char   flag                       # Drive: 1; Brake: 2; Emergency brake: 3.
    char   engine_ctr                 # No operation: 0; turn off: 1; start: 2.
    char   park_brk                   # Turn off: 0; start: 1.
    char   load_brk                   # Turn off: 0; start: 1.
    char   carrier_control            # Rising: 0; keep: 1; floating: 2; decline: 3;
    float32 dumpbed_ctr               # dumpbed level, %
    char   turn_light                 # Turn off: 0; turn on the right: 1; turn on the left: 2;
    int32  gear_num
    int32  gear_cmd
    int32  gear_flag
    int32  gear_cleardriver
    char   dipped_light               # Turn off: 0; turn on the near light: 1; turn on the high beam: 2;
    char   marker_light               # Turn off: 0; turn on: 1;
    char   brake_light                # Turn off: 0; turn on: 1;
    char   emer_light                 # Turn off: 0; turn on: 1;
    char   trumpet                    # Turn off: 0; turn on: 1;
    char   state_light                # Under power state: 0; silent mode: 1; automatic driving mode: 2; remote control mode: 3; Manual driving mode: 4;
    char   rest_off_ctr               # Turn off: 1; turn on: 0;
    char   lube_ctr                   # Turn off: 0; turn on: 1;
    char   auto_cmd                   # Manual: 0; Auto: 1;
    char   override_cmd               # Off: 0; On: 1;
    char   light_ctr                  # Off: 0; Red: 1; Yellow: 2; Blue: 4;
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new msg_v_control(null);
    if (msg.static_check !== undefined) {
      resolved.static_check = msg.static_check;
    }
    else {
      resolved.static_check = 0
    }

    if (msg.steering_angle !== undefined) {
      resolved.steering_angle = msg.steering_angle;
    }
    else {
      resolved.steering_angle = 0.0
    }

    if (msg.steering_spd !== undefined) {
      resolved.steering_spd = msg.steering_spd;
    }
    else {
      resolved.steering_spd = 0.0
    }

    if (msg.thr_angle !== undefined) {
      resolved.thr_angle = msg.thr_angle;
    }
    else {
      resolved.thr_angle = 0
    }

    if (msg.brake_pressure !== undefined) {
      resolved.brake_pressure = msg.brake_pressure;
    }
    else {
      resolved.brake_pressure = 0.0
    }

    if (msg.brk_current !== undefined) {
      resolved.brk_current = msg.brk_current;
    }
    else {
      resolved.brk_current = 0.0
    }

    if (msg.flag !== undefined) {
      resolved.flag = msg.flag;
    }
    else {
      resolved.flag = 0
    }

    if (msg.engine_ctr !== undefined) {
      resolved.engine_ctr = msg.engine_ctr;
    }
    else {
      resolved.engine_ctr = 0
    }

    if (msg.park_brk !== undefined) {
      resolved.park_brk = msg.park_brk;
    }
    else {
      resolved.park_brk = 0
    }

    if (msg.load_brk !== undefined) {
      resolved.load_brk = msg.load_brk;
    }
    else {
      resolved.load_brk = 0
    }

    if (msg.carrier_control !== undefined) {
      resolved.carrier_control = msg.carrier_control;
    }
    else {
      resolved.carrier_control = 0
    }

    if (msg.dumpbed_ctr !== undefined) {
      resolved.dumpbed_ctr = msg.dumpbed_ctr;
    }
    else {
      resolved.dumpbed_ctr = 0.0
    }

    if (msg.turn_light !== undefined) {
      resolved.turn_light = msg.turn_light;
    }
    else {
      resolved.turn_light = 0
    }

    if (msg.gear_num !== undefined) {
      resolved.gear_num = msg.gear_num;
    }
    else {
      resolved.gear_num = 0
    }

    if (msg.gear_cmd !== undefined) {
      resolved.gear_cmd = msg.gear_cmd;
    }
    else {
      resolved.gear_cmd = 0
    }

    if (msg.gear_flag !== undefined) {
      resolved.gear_flag = msg.gear_flag;
    }
    else {
      resolved.gear_flag = 0
    }

    if (msg.gear_cleardriver !== undefined) {
      resolved.gear_cleardriver = msg.gear_cleardriver;
    }
    else {
      resolved.gear_cleardriver = 0
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

    if (msg.trumpet !== undefined) {
      resolved.trumpet = msg.trumpet;
    }
    else {
      resolved.trumpet = 0
    }

    if (msg.state_light !== undefined) {
      resolved.state_light = msg.state_light;
    }
    else {
      resolved.state_light = 0
    }

    if (msg.rest_off_ctr !== undefined) {
      resolved.rest_off_ctr = msg.rest_off_ctr;
    }
    else {
      resolved.rest_off_ctr = 0
    }

    if (msg.lube_ctr !== undefined) {
      resolved.lube_ctr = msg.lube_ctr;
    }
    else {
      resolved.lube_ctr = 0
    }

    if (msg.auto_cmd !== undefined) {
      resolved.auto_cmd = msg.auto_cmd;
    }
    else {
      resolved.auto_cmd = 0
    }

    if (msg.override_cmd !== undefined) {
      resolved.override_cmd = msg.override_cmd;
    }
    else {
      resolved.override_cmd = 0
    }

    if (msg.light_ctr !== undefined) {
      resolved.light_ctr = msg.light_ctr;
    }
    else {
      resolved.light_ctr = 0
    }

    return resolved;
    }
};

module.exports = msg_v_control;
