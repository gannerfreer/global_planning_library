;; Auto-generated. Do not edit!


(when (boundp 'msg_gnss_prep::msg_gnss_prep)
  (if (not (find-package "MSG_GNSS_PREP"))
    (make-package "MSG_GNSS_PREP"))
  (shadow 'msg_gnss_prep (find-package "MSG_GNSS_PREP")))
(unless (find-package "MSG_GNSS_PREP::MSG_GNSS_PREP")
  (make-package "MSG_GNSS_PREP::MSG_GNSS_PREP"))

(in-package "ROS")
;;//! \htmlinclude msg_gnss_prep.msg.html


(defclass msg_gnss_prep::msg_gnss_prep
  :super ros::object
  :slots (_x _y _z _latitude _longitude _height _spd_east _spd_north _spd_down _heading_angle _yaw_angle _yaw_rate _pitch_angle _roll_angle _speed _spd_lon _spd_lat _acce _acce_lon _acce_lat _flag _gps_status ))

(defmethod msg_gnss_prep::msg_gnss_prep
  (:init
   (&key
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:z __z) 0.0)
    ((:latitude __latitude) 0.0)
    ((:longitude __longitude) 0.0)
    ((:height __height) 0.0)
    ((:spd_east __spd_east) 0.0)
    ((:spd_north __spd_north) 0.0)
    ((:spd_down __spd_down) 0.0)
    ((:heading_angle __heading_angle) 0.0)
    ((:yaw_angle __yaw_angle) 0.0)
    ((:yaw_rate __yaw_rate) 0.0)
    ((:pitch_angle __pitch_angle) 0.0)
    ((:roll_angle __roll_angle) 0.0)
    ((:speed __speed) 0.0)
    ((:spd_lon __spd_lon) 0.0)
    ((:spd_lat __spd_lat) 0.0)
    ((:acce __acce) 0.0)
    ((:acce_lon __acce_lon) 0.0)
    ((:acce_lat __acce_lat) 0.0)
    ((:flag __flag) 0)
    ((:gps_status __gps_status) 0)
    )
   (send-super :init)
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _z (float __z))
   (setq _latitude (float __latitude))
   (setq _longitude (float __longitude))
   (setq _height (float __height))
   (setq _spd_east (float __spd_east))
   (setq _spd_north (float __spd_north))
   (setq _spd_down (float __spd_down))
   (setq _heading_angle (float __heading_angle))
   (setq _yaw_angle (float __yaw_angle))
   (setq _yaw_rate (float __yaw_rate))
   (setq _pitch_angle (float __pitch_angle))
   (setq _roll_angle (float __roll_angle))
   (setq _speed (float __speed))
   (setq _spd_lon (float __spd_lon))
   (setq _spd_lat (float __spd_lat))
   (setq _acce (float __acce))
   (setq _acce_lon (float __acce_lon))
   (setq _acce_lat (float __acce_lat))
   (setq _flag (round __flag))
   (setq _gps_status (round __gps_status))
   self)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:z
   (&optional __z)
   (if __z (setq _z __z)) _z)
  (:latitude
   (&optional __latitude)
   (if __latitude (setq _latitude __latitude)) _latitude)
  (:longitude
   (&optional __longitude)
   (if __longitude (setq _longitude __longitude)) _longitude)
  (:height
   (&optional __height)
   (if __height (setq _height __height)) _height)
  (:spd_east
   (&optional __spd_east)
   (if __spd_east (setq _spd_east __spd_east)) _spd_east)
  (:spd_north
   (&optional __spd_north)
   (if __spd_north (setq _spd_north __spd_north)) _spd_north)
  (:spd_down
   (&optional __spd_down)
   (if __spd_down (setq _spd_down __spd_down)) _spd_down)
  (:heading_angle
   (&optional __heading_angle)
   (if __heading_angle (setq _heading_angle __heading_angle)) _heading_angle)
  (:yaw_angle
   (&optional __yaw_angle)
   (if __yaw_angle (setq _yaw_angle __yaw_angle)) _yaw_angle)
  (:yaw_rate
   (&optional __yaw_rate)
   (if __yaw_rate (setq _yaw_rate __yaw_rate)) _yaw_rate)
  (:pitch_angle
   (&optional __pitch_angle)
   (if __pitch_angle (setq _pitch_angle __pitch_angle)) _pitch_angle)
  (:roll_angle
   (&optional __roll_angle)
   (if __roll_angle (setq _roll_angle __roll_angle)) _roll_angle)
  (:speed
   (&optional __speed)
   (if __speed (setq _speed __speed)) _speed)
  (:spd_lon
   (&optional __spd_lon)
   (if __spd_lon (setq _spd_lon __spd_lon)) _spd_lon)
  (:spd_lat
   (&optional __spd_lat)
   (if __spd_lat (setq _spd_lat __spd_lat)) _spd_lat)
  (:acce
   (&optional __acce)
   (if __acce (setq _acce __acce)) _acce)
  (:acce_lon
   (&optional __acce_lon)
   (if __acce_lon (setq _acce_lon __acce_lon)) _acce_lon)
  (:acce_lat
   (&optional __acce_lat)
   (if __acce_lat (setq _acce_lat __acce_lat)) _acce_lat)
  (:flag
   (&optional __flag)
   (if __flag (setq _flag __flag)) _flag)
  (:gps_status
   (&optional __gps_status)
   (if __gps_status (setq _gps_status __gps_status)) _gps_status)
  (:serialization-length
   ()
   (+
    ;; float64 _x
    8
    ;; float64 _y
    8
    ;; float64 _z
    8
    ;; float64 _latitude
    8
    ;; float64 _longitude
    8
    ;; float64 _height
    8
    ;; float32 _spd_east
    4
    ;; float32 _spd_north
    4
    ;; float32 _spd_down
    4
    ;; float32 _heading_angle
    4
    ;; float32 _yaw_angle
    4
    ;; float32 _yaw_rate
    4
    ;; float32 _pitch_angle
    4
    ;; float32 _roll_angle
    4
    ;; float32 _speed
    4
    ;; float32 _spd_lon
    4
    ;; float32 _spd_lat
    4
    ;; float32 _acce
    4
    ;; float32 _acce_lon
    4
    ;; float32 _acce_lat
    4
    ;; uint8 _flag
    1
    ;; uint8 _gps_status
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _x
       (sys::poke _x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _y
       (sys::poke _y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _z
       (sys::poke _z (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _latitude
       (sys::poke _latitude (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _longitude
       (sys::poke _longitude (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _height
       (sys::poke _height (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float32 _spd_east
       (sys::poke _spd_east (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _spd_north
       (sys::poke _spd_north (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _spd_down
       (sys::poke _spd_down (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _heading_angle
       (sys::poke _heading_angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _yaw_angle
       (sys::poke _yaw_angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _yaw_rate
       (sys::poke _yaw_rate (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _pitch_angle
       (sys::poke _pitch_angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _roll_angle
       (sys::poke _roll_angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _speed
       (sys::poke _speed (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _spd_lon
       (sys::poke _spd_lon (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _spd_lat
       (sys::poke _spd_lat (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _acce
       (sys::poke _acce (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _acce_lon
       (sys::poke _acce_lon (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _acce_lat
       (sys::poke _acce_lat (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint8 _flag
       (write-byte _flag s)
     ;; uint8 _gps_status
       (write-byte _gps_status s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _x
     (setq _x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _y
     (setq _y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _z
     (setq _z (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _latitude
     (setq _latitude (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _longitude
     (setq _longitude (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _height
     (setq _height (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float32 _spd_east
     (setq _spd_east (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _spd_north
     (setq _spd_north (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _spd_down
     (setq _spd_down (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _heading_angle
     (setq _heading_angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _yaw_angle
     (setq _yaw_angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _yaw_rate
     (setq _yaw_rate (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _pitch_angle
     (setq _pitch_angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _roll_angle
     (setq _roll_angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _speed
     (setq _speed (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _spd_lon
     (setq _spd_lon (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _spd_lat
     (setq _spd_lat (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _acce
     (setq _acce (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _acce_lon
     (setq _acce_lon (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _acce_lat
     (setq _acce_lat (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint8 _flag
     (setq _flag (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _gps_status
     (setq _gps_status (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get msg_gnss_prep::msg_gnss_prep :md5sum-) "e134d5a1a517850320e9c8189731570d")
(setf (get msg_gnss_prep::msg_gnss_prep :datatype-) "msg_gnss_prep/msg_gnss_prep")
(setf (get msg_gnss_prep::msg_gnss_prep :definition-)
      "float64 x
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


")



(provide :msg_gnss_prep/msg_gnss_prep "e134d5a1a517850320e9c8189731570d")


