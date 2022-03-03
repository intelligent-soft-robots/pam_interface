#pragma once

#include <cstdint>
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

/**
 * Structure that will be packed into UDP telegrams sent to the
 * robot.
 */
typedef struct
{
    uint16_t counter = 0;  // counter
    uint16_t connection =
        0;                 // close connection if 0 // same as emergency stop ?
    uint16_t control = 0;  // 1  = pressure control , 2 = position control
                           // // always use 1
    uint16_t reserve = 0;  // unused
    uint32_t timestamp_client = 0;
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
    uint32_t system_errors;
    uint32_t io_hardware_errors;
} ErrorInformation;

typedef struct  // Llffffff
{
    uint32_t dw_errors;
    int32_t encoder_value;
    float angle;
    float speed;
    float pressure_agonist;
    float valve_agonist;
    float pressure_antagonist;
    float valve_antagonist;
} JointData;

typedef struct  // LLLHHHH [JointSetPoint*4 : f*20] [JointData*4 : Llffffff*4]
                // [PIDData : 48f] ff [ErrorInformation : LL]
{
    uint32_t time_micro_secs_sensor_data;
    uint32_t time_micro_secs_actuator_data;
    uint32_t time_micro_secs_set_points;
    uint16_t operation;
    uint16_t control;
    uint16_t pressure_mode;
    uint16_t b_quick_stop_pushed;
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
    uint32_t index_control_task;
    uint32_t index_set_points_cycle;
    uint32_t index_udp_telegram;
    uint32_t not_close_srv;
    uint32_t time_micro_secs_udp_send;
    uint32_t time_micro_secs_last_udp_receive;
    ArmData data;
} FromRobotMessage;

}  // namespace pam_interface
