#pragma once

#include "pam_interface/sign.hpp"

namespace pam_interface
{
typedef struct
{
    float angle = 0;      // unused
    float valve_ago = 0;  // unused
    float pressure_agonist = 0;
    float valve_antagonist = 0;  // unused
    float pressure_antagonist = 0;
} JointControl;

typedef struct
{
    unsigned short counter = 0;  // counter
    unsigned short connection =
        0;  // close connection if 0 // same as emergency stop ?
    unsigned short control = 0;  // 1  = pressure control , 2 = position control
                                 // // always use 1
    unsigned short reserve = 0;  // unused
    unsigned int timestamp_client = 0;
    JointControl controls[4];
} ToRobotMessage;

typedef struct  // ff
{
    float valve;
    float pressure;
} MuscleSetPoint;

typedef struct  // f ff ff
{
    float angle;
    MuscleSetPoint agonist;
    MuscleSetPoint antagonist;
} JointSetPoint;

typedef struct  // ffff
{
    float p;
    float i;
    float d;
    float ts;
} PID;

typedef struct  // f[4*((4*2)+4)] -> 48f
{
    PID muscles[4][2];
    PID angles[4];
} PIDData;

typedef struct
{
    unsigned int system_errors;
    unsigned int io_hardware_errors;
} ErrorInformation;

typedef struct  // Llffffff
{
    unsigned int dw_errors;
    int encoder_value;
    float angle;
    float speed;
    float pressure_agonist;
    float valve_agonist;
    float pressure_antagonist;
    float valve_antagonist;
} JointData;

/**
 * Structure that will be packed into UDP telegrams sent to the
 * robot.
 */
typedef struct  // LLLHHHH [JointSetPoint*4 : f*20] [JointData*4 : Llffffff*4]
                // [PIDData : 48f] ff [ErrorInformation : LL]
{
    unsigned int time_micro_secs_sensor_data;
    unsigned int time_micro_secs_actuator_data;
    unsigned int time_micro_secs_set_points;
    unsigned short operation;
    unsigned short control;
    unsigned short pressure_mode;
    unsigned short b_quick_stop_pushed;
    JointSetPoint joints_set[4];
    JointData joints_data[4];
    PIDData r_pid_settings;
    float supply_pressure;
    float ring_pressure;
    ErrorInformation error;
} ArmData;

/**
 * Structure into which telegrams received by
 * the robot will be unpacked.
 */
typedef struct  // LLLHLL [ArmData]
{
    unsigned int index_control_task;
    unsigned int index_set_points_cycle;
    unsigned int index_udp_telegram;
    unsigned int not_close_srv;
    unsigned int time_micro_secs_udp_send;
    unsigned int time_micro_secs_last_udp_receive;
    ArmData data;
} FromRobotMessage;

}  // namespace pam_interface
