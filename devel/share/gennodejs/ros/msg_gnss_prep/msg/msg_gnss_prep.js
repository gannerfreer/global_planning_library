// Auto-generated. Do not edit!

// (in-package msg_gnss_prep.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class msg_gnss_prep {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.x = null;
      this.y = null;
      this.z = null;
      this.latitude = null;
      this.longitude = null;
      this.height = null;
      this.spd_east = null;
      this.spd_north = null;
      this.spd_down = null;
      this.heading_angle = null;
      this.yaw_angle = null;
      this.yaw_rate = null;
      this.pitch_angle = null;
      this.roll_angle = null;
      this.speed = null;
      this.spd_lon = null;
      this.spd_lat = null;
      this.acce = null;
      this.acce_lon = null;
      this.acce_lat = null;
      this.flag = null;
      this.gps_status = null;
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
      if (initObj.hasOwnProperty('latitude')) {
        this.latitude = initObj.latitude
      }
      else {
        this.latitude = 0.0;
      }
      if (initObj.hasOwnProperty('longitude')) {
        this.longitude = initObj.longitude
      }
      else {
        this.longitude = 0.0;
      }
      if (initObj.hasOwnProperty('height')) {
        this.height = initObj.height
      }
      else {
        this.height = 0.0;
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
      if (initObj.hasOwnProperty('spd_down')) {
        this.spd_down = initObj.spd_down
      }
      else {
        this.spd_down = 0.0;
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
      if (initObj.hasOwnProperty('roll_angle')) {
        this.roll_angle = initObj.roll_angle
      }
      else {
        this.roll_angle = 0.0;
      }
      if (initObj.hasOwnProperty('speed')) {
        this.speed = initObj.speed
      }
      else {
        this.speed = 0.0;
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
      if (initObj.hasOwnProperty('flag')) {
        this.flag = initObj.flag
      }
      else {
        this.flag = 0;
      }
      if (initObj.hasOwnProperty('gps_status')) {
        this.gps_status = initObj.gps_status
      }
      else {
        this.gps_status = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type msg_gnss_prep
    // Serialize message field [x]
    bufferOffset = _serializer.float64(obj.x, buffer, bufferOffset);
    // Serialize message field [y]
    bufferOffset = _serializer.float64(obj.y, buffer, bufferOffset);
    // Serialize message field [z]
    bufferOffset = _serializer.float64(obj.z, buffer, bufferOffset);
    // Serialize message field [latitude]
    bufferOffset = _serializer.float64(obj.latitude, buffer, bufferOffset);
    // Serialize message field [longitude]
    bufferOffset = _serializer.float64(obj.longitude, buffer, bufferOffset);
    // Serialize message field [height]
    bufferOffset = _serializer.float64(obj.height, buffer, bufferOffset);
    // Serialize message field [spd_east]
    bufferOffset = _serializer.float32(obj.spd_east, buffer, bufferOffset);
    // Serialize message field [spd_north]
    bufferOffset = _serializer.float32(obj.spd_north, buffer, bufferOffset);
    // Serialize message field [spd_down]
    bufferOffset = _serializer.float32(obj.spd_down, buffer, bufferOffset);
    // Serialize message field [heading_angle]
    bufferOffset = _serializer.float32(obj.heading_angle, buffer, bufferOffset);
    // Serialize message field [yaw_angle]
    bufferOffset = _serializer.float32(obj.yaw_angle, buffer, bufferOffset);
    // Serialize message field [yaw_rate]
    bufferOffset = _serializer.float32(obj.yaw_rate, buffer, bufferOffset);
    // Serialize message field [pitch_angle]
    bufferOffset = _serializer.float32(obj.pitch_angle, buffer, bufferOffset);
    // Serialize message field [roll_angle]
    bufferOffset = _serializer.float32(obj.roll_angle, buffer, bufferOffset);
    // Serialize message field [speed]
    bufferOffset = _serializer.float32(obj.speed, buffer, bufferOffset);
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
    // Serialize message field [flag]
    bufferOffset = _serializer.uint8(obj.flag, buffer, bufferOffset);
    // Serialize message field [gps_status]
    bufferOffset = _serializer.uint8(obj.gps_status, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type msg_gnss_prep
    let len;
    let data = new msg_gnss_prep(null);
    // Deserialize message field [x]
    data.x = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [y]
    data.y = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [z]
    data.z = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [latitude]
    data.latitude = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [longitude]
    data.longitude = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [height]
    data.height = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [spd_east]
    data.spd_east = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [spd_north]
    data.spd_north = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [spd_down]
    data.spd_down = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [heading_angle]
    data.heading_angle = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [yaw_angle]
    data.yaw_angle = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [yaw_rate]
    data.yaw_rate = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [pitch_angle]
    data.pitch_angle = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [roll_angle]
    data.roll_angle = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [speed]
    data.speed = _deserializer.float32(buffer, bufferOffset);
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
    // Deserialize message field [flag]
    data.flag = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [gps_status]
    data.gps_status = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 106;
  }

  static datatype() {
    // Returns string type for a message object
    return 'msg_gnss_prep/msg_gnss_prep';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e134d5a1a517850320e9c8189731570d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 x
    float64 y
    float64 z
    float64 latitude
    float64 longitude
    float64 height
    float32 spd_east
    float32 spd_north
    float32 spd_down
    float32 heading_angle
    float32 yaw_angle
    float32 yaw_rate
    float32 pitch_angle
    float32 roll_angle
    float32 speed
    float32 spd_lon
    float32 spd_lat
    float32 acce
    float32 acce_lon
    float32 acce_lat
    uint8 flag
    uint8 gps_status
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new msg_gnss_prep(null);
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

    if (msg.latitude !== undefined) {
      resolved.latitude = msg.latitude;
    }
    else {
      resolved.latitude = 0.0
    }

    if (msg.longitude !== undefined) {
      resolved.longitude = msg.longitude;
    }
    else {
      resolved.longitude = 0.0
    }

    if (msg.height !== undefined) {
      resolved.height = msg.height;
    }
    else {
      resolved.height = 0.0
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

    if (msg.spd_down !== undefined) {
      resolved.spd_down = msg.spd_down;
    }
    else {
      resolved.spd_down = 0.0
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

    if (msg.roll_angle !== undefined) {
      resolved.roll_angle = msg.roll_angle;
    }
    else {
      resolved.roll_angle = 0.0
    }

    if (msg.speed !== undefined) {
      resolved.speed = msg.speed;
    }
    else {
      resolved.speed = 0.0
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

    if (msg.flag !== undefined) {
      resolved.flag = msg.flag;
    }
    else {
      resolved.flag = 0
    }

    if (msg.gps_status !== undefined) {
      resolved.gps_status = msg.gps_status;
    }
    else {
      resolved.gps_status = 0
    }

    return resolved;
    }
};

module.exports = msg_gnss_prep;
