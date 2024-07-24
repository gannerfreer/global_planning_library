// Auto-generated. Do not edit!

// (in-package msg_info_router.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let Point = require('./Point.js');
let msg_common = _finder('msg_common');

//-----------------------------------------------------------

class msg_info_router {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.mode = null;
      this.task_type = null;
      this.task_num = null;
      this.segments_num = null;
      this.cur_segments_num = null;
      this.state_type = null;
      this.path_point = null;
      this.stop_point = null;
      this.is_update_map = null;
      this.remote_spd = null;
      this.remote_steering = null;
      this.remote_parking = null;
      this.remote_stopengine = null;
      this.remote_service_brake = null;
      this.remote_park_brake = null;
      this.remote_load_brake = null;
      this.gear_num = null;
      this.carrier_control = null;
      this.turn_light = null;
      this.dipped_light = null;
      this.marker_light = null;
      this.fog_light = null;
      this.brake_light = null;
      this.emer_light = null;
      this.wiper_sign = null;
      this.trumpet = null;
    }
    else {
      if (initObj.hasOwnProperty('mode')) {
        this.mode = initObj.mode
      }
      else {
        this.mode = 0;
      }
      if (initObj.hasOwnProperty('task_type')) {
        this.task_type = initObj.task_type
      }
      else {
        this.task_type = 0;
      }
      if (initObj.hasOwnProperty('task_num')) {
        this.task_num = initObj.task_num
      }
      else {
        this.task_num = 0;
      }
      if (initObj.hasOwnProperty('segments_num')) {
        this.segments_num = initObj.segments_num
      }
      else {
        this.segments_num = 0;
      }
      if (initObj.hasOwnProperty('cur_segments_num')) {
        this.cur_segments_num = initObj.cur_segments_num
      }
      else {
        this.cur_segments_num = 0;
      }
      if (initObj.hasOwnProperty('state_type')) {
        this.state_type = initObj.state_type
      }
      else {
        this.state_type = 0;
      }
      if (initObj.hasOwnProperty('path_point')) {
        this.path_point = initObj.path_point
      }
      else {
        this.path_point = [];
      }
      if (initObj.hasOwnProperty('stop_point')) {
        this.stop_point = initObj.stop_point
      }
      else {
        this.stop_point = new Point();
      }
      if (initObj.hasOwnProperty('is_update_map')) {
        this.is_update_map = initObj.is_update_map
      }
      else {
        this.is_update_map = false;
      }
      if (initObj.hasOwnProperty('remote_spd')) {
        this.remote_spd = initObj.remote_spd
      }
      else {
        this.remote_spd = 0.0;
      }
      if (initObj.hasOwnProperty('remote_steering')) {
        this.remote_steering = initObj.remote_steering
      }
      else {
        this.remote_steering = 0.0;
      }
      if (initObj.hasOwnProperty('remote_parking')) {
        this.remote_parking = initObj.remote_parking
      }
      else {
        this.remote_parking = 0.0;
      }
      if (initObj.hasOwnProperty('remote_stopengine')) {
        this.remote_stopengine = initObj.remote_stopengine
      }
      else {
        this.remote_stopengine = 0;
      }
      if (initObj.hasOwnProperty('remote_service_brake')) {
        this.remote_service_brake = initObj.remote_service_brake
      }
      else {
        this.remote_service_brake = 0;
      }
      if (initObj.hasOwnProperty('remote_park_brake')) {
        this.remote_park_brake = initObj.remote_park_brake
      }
      else {
        this.remote_park_brake = 0;
      }
      if (initObj.hasOwnProperty('remote_load_brake')) {
        this.remote_load_brake = initObj.remote_load_brake
      }
      else {
        this.remote_load_brake = 0;
      }
      if (initObj.hasOwnProperty('gear_num')) {
        this.gear_num = initObj.gear_num
      }
      else {
        this.gear_num = 0;
      }
      if (initObj.hasOwnProperty('carrier_control')) {
        this.carrier_control = initObj.carrier_control
      }
      else {
        this.carrier_control = 0;
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
      if (initObj.hasOwnProperty('fog_light')) {
        this.fog_light = initObj.fog_light
      }
      else {
        this.fog_light = 0;
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
      if (initObj.hasOwnProperty('wiper_sign')) {
        this.wiper_sign = initObj.wiper_sign
      }
      else {
        this.wiper_sign = 0;
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
    // Serializes a message object of type msg_info_router
    // Serialize message field [mode]
    bufferOffset = _serializer.uint8(obj.mode, buffer, bufferOffset);
    // Serialize message field [task_type]
    bufferOffset = _serializer.uint16(obj.task_type, buffer, bufferOffset);
    // Serialize message field [task_num]
    bufferOffset = _serializer.uint16(obj.task_num, buffer, bufferOffset);
    // Serialize message field [segments_num]
    bufferOffset = _serializer.uint16(obj.segments_num, buffer, bufferOffset);
    // Serialize message field [cur_segments_num]
    bufferOffset = _serializer.uint16(obj.cur_segments_num, buffer, bufferOffset);
    // Serialize message field [state_type]
    bufferOffset = _serializer.uint16(obj.state_type, buffer, bufferOffset);
    // Serialize message field [path_point]
    // Serialize the length for message field [path_point]
    bufferOffset = _serializer.uint32(obj.path_point.length, buffer, bufferOffset);
    obj.path_point.forEach((val) => {
      bufferOffset = msg_common.msg.WayPoint.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [stop_point]
    bufferOffset = Point.serialize(obj.stop_point, buffer, bufferOffset);
    // Serialize message field [is_update_map]
    bufferOffset = _serializer.bool(obj.is_update_map, buffer, bufferOffset);
    // Serialize message field [remote_spd]
    bufferOffset = _serializer.float32(obj.remote_spd, buffer, bufferOffset);
    // Serialize message field [remote_steering]
    bufferOffset = _serializer.float32(obj.remote_steering, buffer, bufferOffset);
    // Serialize message field [remote_parking]
    bufferOffset = _serializer.float32(obj.remote_parking, buffer, bufferOffset);
    // Serialize message field [remote_stopengine]
    bufferOffset = _serializer.uint8(obj.remote_stopengine, buffer, bufferOffset);
    // Serialize message field [remote_service_brake]
    bufferOffset = _serializer.uint8(obj.remote_service_brake, buffer, bufferOffset);
    // Serialize message field [remote_park_brake]
    bufferOffset = _serializer.uint8(obj.remote_park_brake, buffer, bufferOffset);
    // Serialize message field [remote_load_brake]
    bufferOffset = _serializer.uint8(obj.remote_load_brake, buffer, bufferOffset);
    // Serialize message field [gear_num]
    bufferOffset = _serializer.uint8(obj.gear_num, buffer, bufferOffset);
    // Serialize message field [carrier_control]
    bufferOffset = _serializer.uint8(obj.carrier_control, buffer, bufferOffset);
    // Serialize message field [turn_light]
    bufferOffset = _serializer.uint8(obj.turn_light, buffer, bufferOffset);
    // Serialize message field [dipped_light]
    bufferOffset = _serializer.uint8(obj.dipped_light, buffer, bufferOffset);
    // Serialize message field [marker_light]
    bufferOffset = _serializer.uint8(obj.marker_light, buffer, bufferOffset);
    // Serialize message field [fog_light]
    bufferOffset = _serializer.uint8(obj.fog_light, buffer, bufferOffset);
    // Serialize message field [brake_light]
    bufferOffset = _serializer.uint8(obj.brake_light, buffer, bufferOffset);
    // Serialize message field [emer_light]
    bufferOffset = _serializer.uint8(obj.emer_light, buffer, bufferOffset);
    // Serialize message field [wiper_sign]
    bufferOffset = _serializer.uint8(obj.wiper_sign, buffer, bufferOffset);
    // Serialize message field [trumpet]
    bufferOffset = _serializer.uint8(obj.trumpet, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type msg_info_router
    let len;
    let data = new msg_info_router(null);
    // Deserialize message field [mode]
    data.mode = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [task_type]
    data.task_type = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [task_num]
    data.task_num = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [segments_num]
    data.segments_num = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [cur_segments_num]
    data.cur_segments_num = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [state_type]
    data.state_type = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [path_point]
    // Deserialize array length for message field [path_point]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.path_point = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.path_point[i] = msg_common.msg.WayPoint.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [stop_point]
    data.stop_point = Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [is_update_map]
    data.is_update_map = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [remote_spd]
    data.remote_spd = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [remote_steering]
    data.remote_steering = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [remote_parking]
    data.remote_parking = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [remote_stopengine]
    data.remote_stopengine = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [remote_service_brake]
    data.remote_service_brake = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [remote_park_brake]
    data.remote_park_brake = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [remote_load_brake]
    data.remote_load_brake = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [gear_num]
    data.gear_num = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [carrier_control]
    data.carrier_control = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [turn_light]
    data.turn_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [dipped_light]
    data.dipped_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [marker_light]
    data.marker_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [fog_light]
    data.fog_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [brake_light]
    data.brake_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [emer_light]
    data.emer_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [wiper_sign]
    data.wiper_sign = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [trumpet]
    data.trumpet = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    object.path_point.forEach((val) => {
      length += msg_common.msg.WayPoint.getMessageSize(val);
    });
    return length + 62;
  }

  static datatype() {
    // Returns string type for a message object
    return 'msg_info_router/msg_info_router';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '48626aa112e3a63e18582859d48dcf2e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 mode 	#当前模式  	0:驾驶员驾驶(手动); 1:自动驾驶授权（地面自动驾驶）; 2:遥控
    uint16 task_type	#当前任务  	0:保留; 1:前往装载点; 2:前往装载区候车区; 3:前往卸载点; 4:前往卸载候车区; 5:前往停车场停车点; 6:前往停车候车区
    uint16 task_num	#任务编号  
    uint16 segments_num	#全局路径分段数
    uint16 cur_segments_num	#当前段数
    uint16 state_type 	#状态类型  	0:保留; 1:自检; 2:启动发动机; 3:静态测试; 4:轨迹跟随; 5:排队停车; 6:跟车模式; 7:后台轨迹跟随; 8:卸载模式; 9:装载模式; 10:安全停车; 11:关闭发动机; 12:紧急停车; 13:待机；14:装载完成；
    msg_common/WayPoint[] path_point	#轨迹点信息
    Point stop_point		        #目标停车点
    bool is_update_map		      #地图是否更新
    float32 remote_spd		      #期望车速
    float32 remote_steering	    #方向盘转角
    float32 remote_parking		  #紧急停车指令
    uint8 remote_stopengine	    #发动机停止信号
    uint8 remote_service_brake 	#行车制动信号
    uint8 remote_park_brake 	  #停车制动信号
    uint8 remote_load_brake 	  #装载制动信号
    uint8 gear_num    		  #期望档位
    uint8 carrier_control  	#货舱控制信号
    uint8 turn_light  		  #转向灯信号
    uint8 dipped_light  		#远近光灯信号
    uint8 marker_light  		#示廓灯信号
    uint8 fog_light  		    #前雾灯信号
    uint8 brake_light  		  #刹车灯信号
    uint8 emer_light  		  #紧急灯信号
    uint8 wiper_sign		    #雨刮控制信号
    uint8 trumpet   		    #喇叭信号
    
    ================================================================================
    MSG: msg_common/WayPoint
    float64 x			#路径x坐标
    float64 y			#路径y坐标
    float64 z			#路径z坐标
    float64 left			#距左边界值
    float64 right			#距右边界值
    float32 heading_angle		#路径的方向
    float32 curvature		#曲率
    float32 speed			#路径的速度
    float32 distance		#路点与路径起点沿路径的距离
    float32 slope			#坡度信息
    uint32  attribute		#属性(0: 进站路段 1: 出站路段 2: 路口路段(圆弧) 3:常规路段)
    float32 speed_limit	        #速度上限
    uint8 direction			#0表示前进，1表示后退
    uint8 waypointattr		#路点属性，1代表是参考路径上的点，2代表混合AStar搜出来的点
    float64 t			#时间
    string area_name		#区域名称	
    string onareaid			#混合AStar搜出来的点为区域名，参考路径上的点为参考路径所在的区域(与点所在的区域无关)	
    
    ================================================================================
    MSG: msg_info_router/Point
    float64 x   		#大地坐标系x轴坐标
    float64 y   		#大地坐标系y轴坐标
    float32 heading_angle  	#航行角
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new msg_info_router(null);
    if (msg.mode !== undefined) {
      resolved.mode = msg.mode;
    }
    else {
      resolved.mode = 0
    }

    if (msg.task_type !== undefined) {
      resolved.task_type = msg.task_type;
    }
    else {
      resolved.task_type = 0
    }

    if (msg.task_num !== undefined) {
      resolved.task_num = msg.task_num;
    }
    else {
      resolved.task_num = 0
    }

    if (msg.segments_num !== undefined) {
      resolved.segments_num = msg.segments_num;
    }
    else {
      resolved.segments_num = 0
    }

    if (msg.cur_segments_num !== undefined) {
      resolved.cur_segments_num = msg.cur_segments_num;
    }
    else {
      resolved.cur_segments_num = 0
    }

    if (msg.state_type !== undefined) {
      resolved.state_type = msg.state_type;
    }
    else {
      resolved.state_type = 0
    }

    if (msg.path_point !== undefined) {
      resolved.path_point = new Array(msg.path_point.length);
      for (let i = 0; i < resolved.path_point.length; ++i) {
        resolved.path_point[i] = msg_common.msg.WayPoint.Resolve(msg.path_point[i]);
      }
    }
    else {
      resolved.path_point = []
    }

    if (msg.stop_point !== undefined) {
      resolved.stop_point = Point.Resolve(msg.stop_point)
    }
    else {
      resolved.stop_point = new Point()
    }

    if (msg.is_update_map !== undefined) {
      resolved.is_update_map = msg.is_update_map;
    }
    else {
      resolved.is_update_map = false
    }

    if (msg.remote_spd !== undefined) {
      resolved.remote_spd = msg.remote_spd;
    }
    else {
      resolved.remote_spd = 0.0
    }

    if (msg.remote_steering !== undefined) {
      resolved.remote_steering = msg.remote_steering;
    }
    else {
      resolved.remote_steering = 0.0
    }

    if (msg.remote_parking !== undefined) {
      resolved.remote_parking = msg.remote_parking;
    }
    else {
      resolved.remote_parking = 0.0
    }

    if (msg.remote_stopengine !== undefined) {
      resolved.remote_stopengine = msg.remote_stopengine;
    }
    else {
      resolved.remote_stopengine = 0
    }

    if (msg.remote_service_brake !== undefined) {
      resolved.remote_service_brake = msg.remote_service_brake;
    }
    else {
      resolved.remote_service_brake = 0
    }

    if (msg.remote_park_brake !== undefined) {
      resolved.remote_park_brake = msg.remote_park_brake;
    }
    else {
      resolved.remote_park_brake = 0
    }

    if (msg.remote_load_brake !== undefined) {
      resolved.remote_load_brake = msg.remote_load_brake;
    }
    else {
      resolved.remote_load_brake = 0
    }

    if (msg.gear_num !== undefined) {
      resolved.gear_num = msg.gear_num;
    }
    else {
      resolved.gear_num = 0
    }

    if (msg.carrier_control !== undefined) {
      resolved.carrier_control = msg.carrier_control;
    }
    else {
      resolved.carrier_control = 0
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

    if (msg.fog_light !== undefined) {
      resolved.fog_light = msg.fog_light;
    }
    else {
      resolved.fog_light = 0
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

    if (msg.wiper_sign !== undefined) {
      resolved.wiper_sign = msg.wiper_sign;
    }
    else {
      resolved.wiper_sign = 0
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

module.exports = msg_info_router;
