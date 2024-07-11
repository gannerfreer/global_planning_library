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