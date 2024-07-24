;; Auto-generated. Do not edit!


(when (boundp 'msg_v_control::msg_v_control)
  (if (not (find-package "MSG_V_CONTROL"))
    (make-package "MSG_V_CONTROL"))
  (shadow 'msg_v_control (find-package "MSG_V_CONTROL")))
(unless (find-package "MSG_V_CONTROL::MSG_V_CONTROL")
  (make-package "MSG_V_CONTROL::MSG_V_CONTROL"))

(in-package "ROS")
;;//! \htmlinclude msg_v_control.msg.html


(defclass msg_v_control::msg_v_control
  :super ros::object
  :slots (_static_check _steering_angle _steering_spd _thr_angle _brake_pressure _brk_current _flag _engine_ctr _park_brk _load_brk _carrier_control _dumpbed_ctr _turn_light _gear_num _gear_cmd _gear_flag _gear_cleardriver _dipped_light _marker_light _brake_light _emer_light _trumpet _state_light _rest_off_ctr _lube_ctr _auto_cmd _override_cmd _light_ctr ))

(defmethod msg_v_control::msg_v_control
  (:init
   (&key
    ((:static_check __static_check) 0)
    ((:steering_angle __steering_angle) 0.0)
    ((:steering_spd __steering_spd) 0.0)
    ((:thr_angle __thr_angle) 0)
    ((:brake_pressure __brake_pressure) 0.0)
    ((:brk_current __brk_current) 0.0)
    ((:flag __flag) 0)
    ((:engine_ctr __engine_ctr) 0)
    ((:park_brk __park_brk) 0)
    ((:load_brk __load_brk) 0)
    ((:carrier_control __carrier_control) 0)
    ((:dumpbed_ctr __dumpbed_ctr) 0.0)
    ((:turn_light __turn_light) 0)
    ((:gear_num __gear_num) 0)
    ((:gear_cmd __gear_cmd) 0)
    ((:gear_flag __gear_flag) 0)
    ((:gear_cleardriver __gear_cleardriver) 0)
    ((:dipped_light __dipped_light) 0)
    ((:marker_light __marker_light) 0)
    ((:brake_light __brake_light) 0)
    ((:emer_light __emer_light) 0)
    ((:trumpet __trumpet) 0)
    ((:state_light __state_light) 0)
    ((:rest_off_ctr __rest_off_ctr) 0)
    ((:lube_ctr __lube_ctr) 0)
    ((:auto_cmd __auto_cmd) 0)
    ((:override_cmd __override_cmd) 0)
    ((:light_ctr __light_ctr) 0)
    )
   (send-super :init)
   (setq _static_check (round __static_check))
   (setq _steering_angle (float __steering_angle))
   (setq _steering_spd (float __steering_spd))
   (setq _thr_angle (round __thr_angle))
   (setq _brake_pressure (float __brake_pressure))
   (setq _brk_current (float __brk_current))
   (setq _flag (round __flag))
   (setq _engine_ctr (round __engine_ctr))
   (setq _park_brk (round __park_brk))
   (setq _load_brk (round __load_brk))
   (setq _carrier_control (round __carrier_control))
   (setq _dumpbed_ctr (float __dumpbed_ctr))
   (setq _turn_light (round __turn_light))
   (setq _gear_num (round __gear_num))
   (setq _gear_cmd (round __gear_cmd))
   (setq _gear_flag (round __gear_flag))
   (setq _gear_cleardriver (round __gear_cleardriver))
   (setq _dipped_light (round __dipped_light))
   (setq _marker_light (round __marker_light))
   (setq _brake_light (round __brake_light))
   (setq _emer_light (round __emer_light))
   (setq _trumpet (round __trumpet))
   (setq _state_light (round __state_light))
   (setq _rest_off_ctr (round __rest_off_ctr))
   (setq _lube_ctr (round __lube_ctr))
   (setq _auto_cmd (round __auto_cmd))
   (setq _override_cmd (round __override_cmd))
   (setq _light_ctr (round __light_ctr))
   self)
  (:static_check
   (&optional __static_check)
   (if __static_check (setq _static_check __static_check)) _static_check)
  (:steering_angle
   (&optional __steering_angle)
   (if __steering_angle (setq _steering_angle __steering_angle)) _steering_angle)
  (:steering_spd
   (&optional __steering_spd)
   (if __steering_spd (setq _steering_spd __steering_spd)) _steering_spd)
  (:thr_angle
   (&optional __thr_angle)
   (if __thr_angle (setq _thr_angle __thr_angle)) _thr_angle)
  (:brake_pressure
   (&optional __brake_pressure)
   (if __brake_pressure (setq _brake_pressure __brake_pressure)) _brake_pressure)
  (:brk_current
   (&optional __brk_current)
   (if __brk_current (setq _brk_current __brk_current)) _brk_current)
  (:flag
   (&optional __flag)
   (if __flag (setq _flag __flag)) _flag)
  (:engine_ctr
   (&optional __engine_ctr)
   (if __engine_ctr (setq _engine_ctr __engine_ctr)) _engine_ctr)
  (:park_brk
   (&optional __park_brk)
   (if __park_brk (setq _park_brk __park_brk)) _park_brk)
  (:load_brk
   (&optional __load_brk)
   (if __load_brk (setq _load_brk __load_brk)) _load_brk)
  (:carrier_control
   (&optional __carrier_control)
   (if __carrier_control (setq _carrier_control __carrier_control)) _carrier_control)
  (:dumpbed_ctr
   (&optional __dumpbed_ctr)
   (if __dumpbed_ctr (setq _dumpbed_ctr __dumpbed_ctr)) _dumpbed_ctr)
  (:turn_light
   (&optional __turn_light)
   (if __turn_light (setq _turn_light __turn_light)) _turn_light)
  (:gear_num
   (&optional __gear_num)
   (if __gear_num (setq _gear_num __gear_num)) _gear_num)
  (:gear_cmd
   (&optional __gear_cmd)
   (if __gear_cmd (setq _gear_cmd __gear_cmd)) _gear_cmd)
  (:gear_flag
   (&optional __gear_flag)
   (if __gear_flag (setq _gear_flag __gear_flag)) _gear_flag)
  (:gear_cleardriver
   (&optional __gear_cleardriver)
   (if __gear_cleardriver (setq _gear_cleardriver __gear_cleardriver)) _gear_cleardriver)
  (:dipped_light
   (&optional __dipped_light)
   (if __dipped_light (setq _dipped_light __dipped_light)) _dipped_light)
  (:marker_light
   (&optional __marker_light)
   (if __marker_light (setq _marker_light __marker_light)) _marker_light)
  (:brake_light
   (&optional __brake_light)
   (if __brake_light (setq _brake_light __brake_light)) _brake_light)
  (:emer_light
   (&optional __emer_light)
   (if __emer_light (setq _emer_light __emer_light)) _emer_light)
  (:trumpet
   (&optional __trumpet)
   (if __trumpet (setq _trumpet __trumpet)) _trumpet)
  (:state_light
   (&optional __state_light)
   (if __state_light (setq _state_light __state_light)) _state_light)
  (:rest_off_ctr
   (&optional __rest_off_ctr)
   (if __rest_off_ctr (setq _rest_off_ctr __rest_off_ctr)) _rest_off_ctr)
  (:lube_ctr
   (&optional __lube_ctr)
   (if __lube_ctr (setq _lube_ctr __lube_ctr)) _lube_ctr)
  (:auto_cmd
   (&optional __auto_cmd)
   (if __auto_cmd (setq _auto_cmd __auto_cmd)) _auto_cmd)
  (:override_cmd
   (&optional __override_cmd)
   (if __override_cmd (setq _override_cmd __override_cmd)) _override_cmd)
  (:light_ctr
   (&optional __light_ctr)
   (if __light_ctr (setq _light_ctr __light_ctr)) _light_ctr)
  (:serialization-length
   ()
   (+
    ;; char _static_check
    1
    ;; float64 _steering_angle
    8
    ;; float64 _steering_spd
    8
    ;; int32 _thr_angle
    4
    ;; float32 _brake_pressure
    4
    ;; float32 _brk_current
    4
    ;; char _flag
    1
    ;; char _engine_ctr
    1
    ;; char _park_brk
    1
    ;; char _load_brk
    1
    ;; char _carrier_control
    1
    ;; float32 _dumpbed_ctr
    4
    ;; char _turn_light
    1
    ;; int32 _gear_num
    4
    ;; int32 _gear_cmd
    4
    ;; int32 _gear_flag
    4
    ;; int32 _gear_cleardriver
    4
    ;; char _dipped_light
    1
    ;; char _marker_light
    1
    ;; char _brake_light
    1
    ;; char _emer_light
    1
    ;; char _trumpet
    1
    ;; char _state_light
    1
    ;; char _rest_off_ctr
    1
    ;; char _lube_ctr
    1
    ;; char _auto_cmd
    1
    ;; char _override_cmd
    1
    ;; char _light_ctr
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; char _static_check
       (write-byte _static_check s)
     ;; float64 _steering_angle
       (sys::poke _steering_angle (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _steering_spd
       (sys::poke _steering_spd (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; int32 _thr_angle
       (write-long _thr_angle s)
     ;; float32 _brake_pressure
       (sys::poke _brake_pressure (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _brk_current
       (sys::poke _brk_current (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; char _flag
       (write-byte _flag s)
     ;; char _engine_ctr
       (write-byte _engine_ctr s)
     ;; char _park_brk
       (write-byte _park_brk s)
     ;; char _load_brk
       (write-byte _load_brk s)
     ;; char _carrier_control
       (write-byte _carrier_control s)
     ;; float32 _dumpbed_ctr
       (sys::poke _dumpbed_ctr (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; char _turn_light
       (write-byte _turn_light s)
     ;; int32 _gear_num
       (write-long _gear_num s)
     ;; int32 _gear_cmd
       (write-long _gear_cmd s)
     ;; int32 _gear_flag
       (write-long _gear_flag s)
     ;; int32 _gear_cleardriver
       (write-long _gear_cleardriver s)
     ;; char _dipped_light
       (write-byte _dipped_light s)
     ;; char _marker_light
       (write-byte _marker_light s)
     ;; char _brake_light
       (write-byte _brake_light s)
     ;; char _emer_light
       (write-byte _emer_light s)
     ;; char _trumpet
       (write-byte _trumpet s)
     ;; char _state_light
       (write-byte _state_light s)
     ;; char _rest_off_ctr
       (write-byte _rest_off_ctr s)
     ;; char _lube_ctr
       (write-byte _lube_ctr s)
     ;; char _auto_cmd
       (write-byte _auto_cmd s)
     ;; char _override_cmd
       (write-byte _override_cmd s)
     ;; char _light_ctr
       (write-byte _light_ctr s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; char _static_check
     (setq _static_check (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float64 _steering_angle
     (setq _steering_angle (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _steering_spd
     (setq _steering_spd (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; int32 _thr_angle
     (setq _thr_angle (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _brake_pressure
     (setq _brake_pressure (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _brk_current
     (setq _brk_current (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; char _flag
     (setq _flag (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; char _engine_ctr
     (setq _engine_ctr (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; char _park_brk
     (setq _park_brk (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; char _load_brk
     (setq _load_brk (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; char _carrier_control
     (setq _carrier_control (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float32 _dumpbed_ctr
     (setq _dumpbed_ctr (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; char _turn_light
     (setq _turn_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; int32 _gear_num
     (setq _gear_num (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _gear_cmd
     (setq _gear_cmd (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _gear_flag
     (setq _gear_flag (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _gear_cleardriver
     (setq _gear_cleardriver (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; char _dipped_light
     (setq _dipped_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; char _marker_light
     (setq _marker_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; char _brake_light
     (setq _brake_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; char _emer_light
     (setq _emer_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; char _trumpet
     (setq _trumpet (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; char _state_light
     (setq _state_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; char _rest_off_ctr
     (setq _rest_off_ctr (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; char _lube_ctr
     (setq _lube_ctr (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; char _auto_cmd
     (setq _auto_cmd (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; char _override_cmd
     (setq _override_cmd (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; char _light_ctr
     (setq _light_ctr (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get msg_v_control::msg_v_control :md5sum-) "22edec3cff924e8fcb908dbc10ac7aff")
(setf (get msg_v_control::msg_v_control :datatype-) "msg_v_control/msg_v_control")
(setf (get msg_v_control::msg_v_control :definition-)
      "char static_check                 # 0:no commend; 1: checking; 2: pass check; 4: check failed
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
")



(provide :msg_v_control/msg_v_control "22edec3cff924e8fcb908dbc10ac7aff")


