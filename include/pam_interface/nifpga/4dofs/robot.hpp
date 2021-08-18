#pragma once

#include <string>
#include "generated.h"

const int PLUS_INDEXES[4] = {0, 2, 4, 7};

const int MINUS_INDEXES[4] = {1, 3, 5, 6};

// standing pressure:

const int STAND_PRESSURES[8] = {
    16000, 15500, 13500, 12000, 16000, 15500, 14000, 12000};

const double ENCODER_MULTIPLIERS[4] = {
    0.03629032, 0.07258065, 0.07258065, 0.07758621};

const double ENCODER_BIAS[4] = {
  -0.174, 0.0957, 0.0833, -0.0201};

const bool ENCODER_INVERSE[4] = {
  true, false, false, false};

const std::string SIGNATURE = NiFpga_interfaceNewRobotallMuscles_Signature;
const uint32_t ATTRIBUTE = NiFpga_OpenAttribute_NoRun;

const std::string NI_BIT_FILE(BITFILE_4DOFS_FILE_PATH);
const std::string NI_RESOURCE("RIO0");

const uint32_t ENCODERS[4] = {
    NiFpga_interfaceNewRobotallMuscles_IndicatorI32_q1,
    NiFpga_interfaceNewRobotallMuscles_IndicatorI32_q2,
    NiFpga_interfaceNewRobotallMuscles_IndicatorI32_q3,
    NiFpga_interfaceNewRobotallMuscles_IndicatorI32_q4};

const uint32_t REFERENCE_FOUNDS[4] = {
    NiFpga_interfaceNewRobotallMuscles_IndicatorBool_reffound1,
    NiFpga_interfaceNewRobotallMuscles_IndicatorBool_reffound2,
    NiFpga_interfaceNewRobotallMuscles_IndicatorBool_reffound3,
    NiFpga_interfaceNewRobotallMuscles_IndicatorBool_reffound4};

const uint32_t CURRENT_PRESSURES[8] = {
    NiFpga_interfaceNewRobotallMuscles_IndicatorI16_pr0,
    NiFpga_interfaceNewRobotallMuscles_IndicatorI16_pr1,
    NiFpga_interfaceNewRobotallMuscles_IndicatorI16_pr2,
    NiFpga_interfaceNewRobotallMuscles_IndicatorI16_pr3,
    NiFpga_interfaceNewRobotallMuscles_IndicatorI16_pr4,
    NiFpga_interfaceNewRobotallMuscles_IndicatorI16_pr5,
    NiFpga_interfaceNewRobotallMuscles_IndicatorI16_pr6,
    NiFpga_interfaceNewRobotallMuscles_IndicatorI16_pr7};

const uint32_t SET_PRESSURES[8] = {
    NiFpga_interfaceNewRobotallMuscles_ControlI16_set0,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_set1,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_set2,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_set3,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_set4,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_set5,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_set6,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_set7};

const uint32_t CONTROLS[8] = {
    NiFpga_interfaceNewRobotallMuscles_ControlBool_Openloop0,
    NiFpga_interfaceNewRobotallMuscles_ControlBool_Openloop1,
    NiFpga_interfaceNewRobotallMuscles_ControlBool_Openloop2,
    NiFpga_interfaceNewRobotallMuscles_ControlBool_Openloop3,
    NiFpga_interfaceNewRobotallMuscles_ControlBool_Openloop4,
    NiFpga_interfaceNewRobotallMuscles_ControlBool_Openloop5,
    NiFpga_interfaceNewRobotallMuscles_ControlBool_Openloop6,
    NiFpga_interfaceNewRobotallMuscles_ControlBool_Openloop7};

const uint32_t MIN_PRESSURES[8] = {
    NiFpga_interfaceNewRobotallMuscles_ControlI16_min0,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_min1,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_min2,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_min3,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_min4,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_min5,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_min6,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_min7};

const uint32_t MAX_PRESSURES[8] = {
    NiFpga_interfaceNewRobotallMuscles_ControlI16_max0,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_max1,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_max2,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_max3,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_max4,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_max5,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_max6,
    NiFpga_interfaceNewRobotallMuscles_ControlI16_max7};

const uint32_t ITERATION_SENSOR =
    NiFpga_interfaceNewRobotallMuscles_IndicatorI32_itSensor;

const uint32_t ITERATION_CONTROL =
    NiFpga_interfaceNewRobotallMuscles_IndicatorI32_itControl;

const uint32_t CONTROL_PERIOD =
    NiFpga_interfaceNewRobotallMuscles_ControlU32_LoopRateuScontrol;

const uint32_t SENSOR_PERIOD =
    NiFpga_interfaceNewRobotallMuscles_ControlU32_LoopRateuSsensorvalues;
