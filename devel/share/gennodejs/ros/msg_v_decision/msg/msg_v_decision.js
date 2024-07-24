// Auto-generated. Do not edit!

// (in-package msg_v_decision.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let msg_safety_diagn = _finder('msg_safety_diagn');
let msg_obj = _finder('msg_obj');
let msg_common = _finder('msg_common');

//-----------------------------------------------------------

class msg_v_decision {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.task_mode = null;
      this.target_id = null;
      this.task_num = null;
      this.task_state = null;
      this.system_state = null;
      this.obj_fuse = null;
      this.target_obstacle = null;
      this.dis2front = null;
      this.distance2vehicle = null;
      this.distance2obstacle = null;
      this.fault_info = null;
      this.event_report = null;
      this.mode = null;
      this.is_update_map = null;
      this.traj_id = null;
      this.way_point = null;
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
      this.emer_light = null;
      this.trumpet = null;
      this.is_clean = null;
    }
    else {
      if (initObj.hasOwnProperty('task_mode')) {
        this.task_mode = initObj.task_mode
      }
      else {
        this.task_mode = 0;
      }
      if (initObj.hasOwnProperty('target_id')) {
        this.target_id = initObj.target_id
      }
      else {
        this.target_id = 0;
      }
      if (initObj.hasOwnProperty('task_num')) {
        this.task_num = initObj.task_num
      }
      else {
        this.task_num = 0;
      }
      if (initObj.hasOwnProperty('task_state')) {
        this.task_state = initObj.task_state
      }
      else {
        this.task_state = 0;
      }
      if (initObj.hasOwnProperty('system_state')) {
        this.system_state = initObj.system_state
      }
      else {
        this.system_state = 0;
      }
      if (initObj.hasOwnProperty('obj_fuse')) {
        this.obj_fuse = initObj.obj_fuse
      }
      else {
        this.obj_fuse = [];
      }
      if (initObj.hasOwnProperty('target_obstacle')) {
        this.target_obstacle = initObj.target_obstacle
      }
      else {
        this.target_obstacle = [];
      }
      if (initObj.hasOwnProperty('dis2front')) {
        this.dis2front = initObj.dis2front
      }
      else {
        this.dis2front = 0.0;
      }
      if (initObj.hasOwnProperty('distance2vehicle')) {
        this.distance2vehicle = initObj.distance2vehicle
      }
      else {
        this.distance2vehicle = 0.0;
      }
      if (initObj.hasOwnProperty('distance2obstacle')) {
        this.distance2obstacle = initObj.distance2obstacle
      }
      else {
        this.distance2obstacle = 0.0;
      }
      if (initObj.hasOwnProperty('fault_info')) {
        this.fault_info = initObj.fault_info
      }
      else {
        this.fault_info = [];
      }
      if (initObj.hasOwnProperty('event_report')) {
        this.event_report = initObj.event_report
      }
      else {
        this.event_report = 0;
      }
      if (initObj.hasOwnProperty('mode')) {
        this.mode = initObj.mode
      }
      else {
        this.mode = 0;
      }
      if (initObj.hasOwnProperty('is_update_map')) {
        this.is_update_map = initObj.is_update_map
      }
      else {
        this.is_update_map = 0;
      }
      if (initObj.hasOwnProperty('traj_id')) {
        this.traj_id = initObj.traj_id
      }
      else {
        this.traj_id = 0;
      }
      if (initObj.hasOwnProperty('way_point')) {
        this.way_point = initObj.way_point
      }
      else {
        this.way_point = [];
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
        this.remote_parking = 0;
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
      if (initObj.hasOwnProperty('is_clean')) {
        this.is_clean = initObj.is_clean
      }
      else {
        this.is_clean = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type msg_v_decision
    // Serialize message field [task_mode]
    bufferOffset = _serializer.int32(obj.task_mode, buffer, bufferOffset);
    // Serialize message field [target_id]
    bufferOffset = _serializer.uint16(obj.target_id, buffer, bufferOffset);
    // Serialize message field [task_num]
    bufferOffset = _serializer.uint16(obj.task_num, buffer, bufferOffset);
    // Serialize message field [task_state]
    bufferOffset = _serializer.uint16(obj.task_state, buffer, bufferOffset);
    // Serialize message field [system_state]
    bufferOffset = _serializer.int32(obj.system_state, buffer, bufferOffset);
    // Serialize message field [obj_fuse]
    // Serialize the length for message field [obj_fuse]
    bufferOffset = _serializer.uint32(obj.obj_fuse.length, buffer, bufferOffset);
    obj.obj_fuse.forEach((val) => {
      bufferOffset = msg_obj.msg.Obj.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [target_obstacle]
    // Serialize the length for message field [target_obstacle]
    bufferOffset = _serializer.uint32(obj.target_obstacle.length, buffer, bufferOffset);
    obj.target_obstacle.forEach((val) => {
      bufferOffset = msg_obj.msg.Obj.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [dis2front]
    bufferOffset = _serializer.float32(obj.dis2front, buffer, bufferOffset);
    // Serialize message field [distance2vehicle]
    bufferOffset = _serializer.float32(obj.distance2vehicle, buffer, bufferOffset);
    // Serialize message field [distance2obstacle]
    bufferOffset = _serializer.float32(obj.distance2obstacle, buffer, bufferOffset);
    // Serialize message field [fault_info]
    // Serialize the length for message field [fault_info]
    bufferOffset = _serializer.uint32(obj.fault_info.length, buffer, bufferOffset);
    obj.fault_info.forEach((val) => {
      bufferOffset = msg_safety_diagn.msg.DiagnDataStruct.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [event_report]
    bufferOffset = _serializer.uint16(obj.event_report, buffer, bufferOffset);
    // Serialize message field [mode]
    bufferOffset = _serializer.uint8(obj.mode, buffer, bufferOffset);
    // Serialize message field [is_update_map]
    bufferOffset = _serializer.uint8(obj.is_update_map, buffer, bufferOffset);
    // Serialize message field [traj_id]
    bufferOffset = _serializer.uint32(obj.traj_id, buffer, bufferOffset);
    // Serialize message field [way_point]
    // Serialize the length for message field [way_point]
    bufferOffset = _serializer.uint32(obj.way_point.length, buffer, bufferOffset);
    obj.way_point.forEach((val) => {
      bufferOffset = msg_common.msg.WayPoint.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [remote_spd]
    bufferOffset = _serializer.float32(obj.remote_spd, buffer, bufferOffset);
    // Serialize message field [remote_steering]
    bufferOffset = _serializer.float32(obj.remote_steering, buffer, bufferOffset);
    // Serialize message field [remote_parking]
    bufferOffset = _serializer.uint8(obj.remote_parking, buffer, bufferOffset);
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
    // Serialize message field [emer_light]
    bufferOffset = _serializer.uint8(obj.emer_light, buffer, bufferOffset);
    // Serialize message field [trumpet]
    bufferOffset = _serializer.uint8(obj.trumpet, buffer, bufferOffset);
    // Serialize message field [is_clean]
    bufferOffset = _arraySerializer.bool(obj.is_clean, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type msg_v_decision
    let len;
    let data = new msg_v_decision(null);
    // Deserialize message field [task_mode]
    data.task_mode = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [target_id]
    data.target_id = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [task_num]
    data.task_num = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [task_state]
    data.task_state = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [system_state]
    data.system_state = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [obj_fuse]
    // Deserialize array length for message field [obj_fuse]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.obj_fuse = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.obj_fuse[i] = msg_obj.msg.Obj.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [target_obstacle]
    // Deserialize array length for message field [target_obstacle]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.target_obstacle = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.target_obstacle[i] = msg_obj.msg.Obj.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [dis2front]
    data.dis2front = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [distance2vehicle]
    data.distance2vehicle = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [distance2obstacle]
    data.distance2obstacle = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [fault_info]
    // Deserialize array length for message field [fault_info]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.fault_info = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.fault_info[i] = msg_safety_diagn.msg.DiagnDataStruct.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [event_report]
    data.event_report = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [mode]
    data.mode = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [is_update_map]
    data.is_update_map = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [traj_id]
    data.traj_id = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [way_point]
    // Deserialize array length for message field [way_point]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.way_point = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.way_point[i] = msg_common.msg.WayPoint.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [remote_spd]
    data.remote_spd = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [remote_steering]
    data.remote_steering = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [remote_parking]
    data.remote_parking = _deserializer.uint8(buffer, bufferOffset);
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
    // Deserialize message field [emer_light]
    data.emer_light = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [trumpet]
    data.trumpet = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [is_clean]
    data.is_clean = _arrayDeserializer.bool(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    object.obj_fuse.forEach((val) => {
      length += msg_obj.msg.Obj.getMessageSize(val);
    });
    object.target_obstacle.forEach((val) => {
      length += msg_obj.msg.Obj.getMessageSize(val);
    });
    object.fault_info.forEach((val) => {
      length += msg_safety_diagn.msg.DiagnDataStruct.getMessageSize(val);
    });
    object.way_point.forEach((val) => {
      length += msg_common.msg.WayPoint.getMessageSize(val);
    });
    length += object.is_clean.length;
    return length + 74;
  }

  static datatype() {
    // Returns string type for a message object
    return 'msg_v_decision/msg_v_decision';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '9972371d5850ca25138bae62dc721d39';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 task_mode   #(任务类型)前往装载点:10001 前往装载区候车区:10002 前往卸载点:10003 前往卸载候车区:10004 前往停车场停车点:10005 前往停车候车区:10006 取消当前:10007 保持当前任务:10008
    uint16 target_id #0保留  1自检  2启动发动机  3静态测试  4待机  5路径跟踪 6路口通行 7路口等待 8卸载...
    uint16 task_num	#任务编号
    uint16 task_state	#任务状态	0：保留  1：未就绪  2：执行中  3：完成/等待
    int32 system_state #(矿卡当前模式状态) 自检:20001 启动发动机:20002 静态测试:20003 轨迹跟随:20004 排队停车:20005 跟车模式:20006 后台轨迹跟随:20007 卸载模式:20008 装载模式:20009 安全停车:20010 关闭发动机:20011 紧急停车:20012 待机:20013 装载完成:20014 后台绕障:20015
    
    msg_obj/Obj[] obj_fuse  	#障碍物信息结构体
    msg_obj/Obj[] target_obstacle  #距离自车最近障碍物
    float32 dis2front  		#自车与前车距离
    float32 distance2vehicle	#车辆与全局路径的最小横向距离差值
    float32 distance2obstacle	#目标障碍物最近点最小横向距离差值
    
    msg_safety_diagn/DiagnDataStruct[] fault_info   #故障信息结构体
    uint16 event_report #1：车端请求后台局部路径规划 2:车端到达装载点 装载状态切换后触发装载请求事件 3:车端完成卸载任务后出发卸载完成事件
    uint8 mode	#(矿卡当前执行的模式)手动：0    自动：1    远程遥控：2
    uint8 is_update_map #地图更新情况:0:未更新 1:更新成功 2:拒绝更新
    uint32 traj_id
    msg_common/WayPoint[] way_point
    float32 remote_spd
    float32 remote_steering
    uint8 remote_parking
    uint8 remote_stopengine
    uint8 remote_service_brake #行车制动
    uint8 remote_park_brake #停车制动
    uint8 remote_load_brake #装载制动
    uint8 gear_num 		#档位
    uint8 carrier_control		#货舱控制信号
    uint8 turn_light		#转向灯信号
    uint8 dipped_light		#近光灯信号
    uint8 marker_light		#示廓灯信号
    uint8 emer_light		#紧急信号灯信号
    uint8 trumpet			#喇叭信号
    bool[] is_clean
    
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
    MSG: msg_safety_diagn/DiagnDataStruct
    int32 equip_num 
    int32 diagn_type
    msg_obj/Obj[] obj_state
    
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new msg_v_decision(null);
    if (msg.task_mode !== undefined) {
      resolved.task_mode = msg.task_mode;
    }
    else {
      resolved.task_mode = 0
    }

    if (msg.target_id !== undefined) {
      resolved.target_id = msg.target_id;
    }
    else {
      resolved.target_id = 0
    }

    if (msg.task_num !== undefined) {
      resolved.task_num = msg.task_num;
    }
    else {
      resolved.task_num = 0
    }

    if (msg.task_state !== undefined) {
      resolved.task_state = msg.task_state;
    }
    else {
      resolved.task_state = 0
    }

    if (msg.system_state !== undefined) {
      resolved.system_state = msg.system_state;
    }
    else {
      resolved.system_state = 0
    }

    if (msg.obj_fuse !== undefined) {
      resolved.obj_fuse = new Array(msg.obj_fuse.length);
      for (let i = 0; i < resolved.obj_fuse.length; ++i) {
        resolved.obj_fuse[i] = msg_obj.msg.Obj.Resolve(msg.obj_fuse[i]);
      }
    }
    else {
      resolved.obj_fuse = []
    }

    if (msg.target_obstacle !== undefined) {
      resolved.target_obstacle = new Array(msg.target_obstacle.length);
      for (let i = 0; i < resolved.target_obstacle.length; ++i) {
        resolved.target_obstacle[i] = msg_obj.msg.Obj.Resolve(msg.target_obstacle[i]);
      }
    }
    else {
      resolved.target_obstacle = []
    }

    if (msg.dis2front !== undefined) {
      resolved.dis2front = msg.dis2front;
    }
    else {
      resolved.dis2front = 0.0
    }

    if (msg.distance2vehicle !== undefined) {
      resolved.distance2vehicle = msg.distance2vehicle;
    }
    else {
      resolved.distance2vehicle = 0.0
    }

    if (msg.distance2obstacle !== undefined) {
      resolved.distance2obstacle = msg.distance2obstacle;
    }
    else {
      resolved.distance2obstacle = 0.0
    }

    if (msg.fault_info !== undefined) {
      resolved.fault_info = new Array(msg.fault_info.length);
      for (let i = 0; i < resolved.fault_info.length; ++i) {
        resolved.fault_info[i] = msg_safety_diagn.msg.DiagnDataStruct.Resolve(msg.fault_info[i]);
      }
    }
    else {
      resolved.fault_info = []
    }

    if (msg.event_report !== undefined) {
      resolved.event_report = msg.event_report;
    }
    else {
      resolved.event_report = 0
    }

    if (msg.mode !== undefined) {
      resolved.mode = msg.mode;
    }
    else {
      resolved.mode = 0
    }

    if (msg.is_update_map !== undefined) {
      resolved.is_update_map = msg.is_update_map;
    }
    else {
      resolved.is_update_map = 0
    }

    if (msg.traj_id !== undefined) {
      resolved.traj_id = msg.traj_id;
    }
    else {
      resolved.traj_id = 0
    }

    if (msg.way_point !== undefined) {
      resolved.way_point = new Array(msg.way_point.length);
      for (let i = 0; i < resolved.way_point.length; ++i) {
        resolved.way_point[i] = msg_common.msg.WayPoint.Resolve(msg.way_point[i]);
      }
    }
    else {
      resolved.way_point = []
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
      resolved.remote_parking = 0
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

    if (msg.is_clean !== undefined) {
      resolved.is_clean = msg.is_clean;
    }
    else {
      resolved.is_clean = []
    }

    return resolved;
    }
};

module.exports = msg_v_decision;
