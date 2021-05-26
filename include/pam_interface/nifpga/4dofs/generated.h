/*
 * Generated with the FPGA Interface C API Generator 14.0.0
 * for NI-RIO 14.0.0 or later.
 */

#pragma once

#ifndef NiFpga_Version
#define NiFpga_Version 1400
#endif

#include "pam_interface/nifpga/NiFpga.h"

/**
 * The filename of the FPGA bitfile.
 *
 * This is a #define to allow for string literal concatenation. For example:
 *
 *    static const char* const Bitfile = "C:\\"
 * NiFpga_interfaceNewRobotallMuscles_Bitfile;
 */
// note : BITFILE_4DOFS_FILE_PATH replaced by absolute path to the file in
// CMakeLists.txt
#define NiFpga_interfaceNewRobotallMuscles_Bitfile BITFILE_4DOFS_FILE_PATH

/**
 * The signature of the FPGA bitfile.
 */
static const char* const NiFpga_interfaceNewRobotallMuscles_Signature =
    "9D14BBB4C69DBB5761523A51AC506D86";

typedef enum
{
    NiFpga_interfaceNewRobotallMuscles_IndicatorBool_A1 = 0x817A,
    NiFpga_interfaceNewRobotallMuscles_IndicatorBool_A2 = 0x816E,
    NiFpga_interfaceNewRobotallMuscles_IndicatorBool_A3 = 0x8162,
    NiFpga_interfaceNewRobotallMuscles_IndicatorBool_A4 = 0x8156,
    NiFpga_interfaceNewRobotallMuscles_IndicatorBool_B1 = 0x8176,
    NiFpga_interfaceNewRobotallMuscles_IndicatorBool_B2 = 0x816A,
    NiFpga_interfaceNewRobotallMuscles_IndicatorBool_B3 = 0x815E,
    NiFpga_interfaceNewRobotallMuscles_IndicatorBool_B4 = 0x8152,
    NiFpga_interfaceNewRobotallMuscles_IndicatorBool_I1 = 0x817E,
    NiFpga_interfaceNewRobotallMuscles_IndicatorBool_I2 = 0x8172,
    NiFpga_interfaceNewRobotallMuscles_IndicatorBool_I3 = 0x8166,
    NiFpga_interfaceNewRobotallMuscles_IndicatorBool_I4 = 0x815A,
    NiFpga_interfaceNewRobotallMuscles_IndicatorBool_reffound1 = 0x819A,
    NiFpga_interfaceNewRobotallMuscles_IndicatorBool_reffound2 = 0x8196,
    NiFpga_interfaceNewRobotallMuscles_IndicatorBool_reffound3 = 0x8192,
    NiFpga_interfaceNewRobotallMuscles_IndicatorBool_reffound4 = 0x818E,
} NiFpga_interfaceNewRobotallMuscles_IndicatorBool;

typedef enum
{
    NiFpga_interfaceNewRobotallMuscles_IndicatorI16_pr0 = 0x81F6,
    NiFpga_interfaceNewRobotallMuscles_IndicatorI16_pr1 = 0x81FA,
    NiFpga_interfaceNewRobotallMuscles_IndicatorI16_pr3 = 0x81FE,
    NiFpga_interfaceNewRobotallMuscles_IndicatorI16_pr2 = 0x8202,
    // Dieter Buechler: switched addresses of 4 and 5 s.t.
    // agonist acts in positive direction and antagonist in negative
    // direction relative to the joint angle
    NiFpga_interfaceNewRobotallMuscles_IndicatorI16_pr4 = 0x81B6,
    NiFpga_interfaceNewRobotallMuscles_IndicatorI16_pr5 = 0x81AA,
    NiFpga_interfaceNewRobotallMuscles_IndicatorI16_pr7 = 0x8206,
    NiFpga_interfaceNewRobotallMuscles_IndicatorI16_pr6 = 0x820A,
    NiFpga_interfaceNewRobotallMuscles_IndicatorI16_u0 = 0x81DE,
    NiFpga_interfaceNewRobotallMuscles_IndicatorI16_u1 = 0x81E2,
    NiFpga_interfaceNewRobotallMuscles_IndicatorI16_u3 = 0x81E6,
    NiFpga_interfaceNewRobotallMuscles_IndicatorI16_u2 = 0x81EA,
    NiFpga_interfaceNewRobotallMuscles_IndicatorI16_u4 = 0x81BA,
    NiFpga_interfaceNewRobotallMuscles_IndicatorI16_u5 = 0x81AE,
    NiFpga_interfaceNewRobotallMuscles_IndicatorI16_u7 = 0x81EE,
    NiFpga_interfaceNewRobotallMuscles_IndicatorI16_u6 = 0x81F2,
} NiFpga_interfaceNewRobotallMuscles_IndicatorI16;

typedef enum
{
    NiFpga_interfaceNewRobotallMuscles_IndicatorI32_itControl = 0x81C0,
    NiFpga_interfaceNewRobotallMuscles_IndicatorI32_itSensor = 0x81A4,
    NiFpga_interfaceNewRobotallMuscles_IndicatorI32_q1 = 0x819C,
    NiFpga_interfaceNewRobotallMuscles_IndicatorI32_q2 = 0x8188,
    NiFpga_interfaceNewRobotallMuscles_IndicatorI32_q3 = 0x8184,
    NiFpga_interfaceNewRobotallMuscles_IndicatorI32_q4 = 0x8180,
} NiFpga_interfaceNewRobotallMuscles_IndicatorI32;

typedef enum
{
    NiFpga_interfaceNewRobotallMuscles_ControlBool_Openloop0 = 0x81C6,
    NiFpga_interfaceNewRobotallMuscles_ControlBool_Openloop1 = 0x81CA,
    NiFpga_interfaceNewRobotallMuscles_ControlBool_Openloop2 = 0x81CE,
    NiFpga_interfaceNewRobotallMuscles_ControlBool_Openloop3 = 0x81D2,
    // Dieter Buechler: switched addresses of 4 and 5 s.t.
    // agonist acts in positive direction and antagonist in negative
    // direction relative to the joint angle
    NiFpga_interfaceNewRobotallMuscles_ControlBool_Openloop5 = 0x81B2,
    NiFpga_interfaceNewRobotallMuscles_ControlBool_Openloop4 = 0x810E,
    NiFpga_interfaceNewRobotallMuscles_ControlBool_Openloop6 = 0x81D6,
    NiFpga_interfaceNewRobotallMuscles_ControlBool_Openloop7 = 0x81DA,
} NiFpga_interfaceNewRobotallMuscles_ControlBool;

typedef enum
{
    NiFpga_interfaceNewRobotallMuscles_ControlI16_max0 = 0x8112,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_max1 = 0x8116,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_max3 = 0x811A,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_max2 = 0x811E,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_max4 = 0x812A,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_max5 = 0x812E,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_max7 = 0x8122,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_max6 = 0x8126,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_min0 = 0x8132,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_min1 = 0x8136,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_min3 = 0x813A,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_min2 = 0x813E,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_min4 = 0x814A,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_min5 = 0x814E,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_min7 = 0x8142,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_min6 = 0x8146,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_set0 = 0x820E,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_set1 = 0x8212,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_set3 = 0x8216,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_set2 = 0x821A,
    // Dieter Buechler: switched addresses of set4 and set5 s.t.
    // agonist acts in positive direction and antagonist in negative
    // direction relative to the joint angle
    NiFpga_interfaceNewRobotallMuscles_ControlI16_set4 = 0x8226,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_set5 = 0x822A,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_set7 = 0x821E,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_set6 = 0x8222,
} NiFpga_interfaceNewRobotallMuscles_ControlI16;

typedef enum
{
    NiFpga_interfaceNewRobotallMuscles_ControlU32_LoopRateuScontrol = 0x81BC,
    NiFpga_interfaceNewRobotallMuscles_ControlU32_LoopRateuSsensorvalues =
        0x81A0,
} NiFpga_interfaceNewRobotallMuscles_ControlU32;
