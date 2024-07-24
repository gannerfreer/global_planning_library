;; Auto-generated. Do not edit!


(when (boundp 'msg_common::Covariance)
  (if (not (find-package "MSG_COMMON"))
    (make-package "MSG_COMMON"))
  (shadow 'Covariance (find-package "MSG_COMMON")))
(unless (find-package "MSG_COMMON::COVARIANCE")
  (make-package "MSG_COMMON::COVARIANCE"))

(in-package "ROS")
;;//! \htmlinclude Covariance.msg.html


(defclass msg_common::Covariance
  :super ros::object
  :slots (_value _row _col ))

(defmethod msg_common::Covariance
  (:init
   (&key
    ((:value __value) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:row __row) 0)
    ((:col __col) 0)
    )
   (send-super :init)
   (setq _value __value)
   (setq _row (round __row))
   (setq _col (round __col))
   self)
  (:value
   (&optional __value)
   (if __value (setq _value __value)) _value)
  (:row
   (&optional __row)
   (if __row (setq _row __row)) _row)
  (:col
   (&optional __col)
   (if __col (setq _col __col)) _col)
  (:serialization-length
   ()
   (+
    ;; float32[] _value
    (* 4    (length _value)) 4
    ;; int8 _row
    1
    ;; int8 _col
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32[] _value
     (write-long (length _value) s)
     (dotimes (i (length _value))
       (sys::poke (elt _value i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; int8 _row
       (write-byte _row s)
     ;; int8 _col
       (write-byte _col s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32[] _value
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _value (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _value i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;; int8 _row
     (setq _row (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _row 127) (setq _row (- _row 256)))
   ;; int8 _col
     (setq _col (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _col 127) (setq _col (- _col 256)))
   ;;
   self)
  )

(setf (get msg_common::Covariance :md5sum-) "44d99f5dfbfdb9bd3d5ab1ee2f4b0fcd")
(setf (get msg_common::Covariance :datatype-) "msg_common/Covariance")
(setf (get msg_common::Covariance :definition-)
      "float32[] value #矩阵值
int8 row #协方差行
int8 col #协方差列
")



(provide :msg_common/Covariance "44d99f5dfbfdb9bd3d5ab1ee2f4b0fcd")


