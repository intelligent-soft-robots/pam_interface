// Copyright 2018 Max Planck Gesellschaft
// Authors : Dieter Buchler and Vincent Berenz

/*

Code here meant to organize the memory addresses declared in
NiFpga_interfaceNewRobotallMuscles.h in a more convenient way

*/

#pragma once

#include <math.h>
#include <unistd.h>
#include "NiFpga.h"
#include "NiFpga_exception.hpp"

#define PAMY1_NI_BIT_FILE_SUBDIR "pam_interface/pamy1/bitfile/pam_robot.lvbitx"
#define PAMY1_CONFIG_SUB_FOLDER "/pam_interface/pamy1/config/"

namespace pam_interface
{
// This code is shared among all robots.

/**
 * @brief Joint class using a FPGA designed by National Instruments Corp.
 *
 * Each joint of Pamy1 is actuated by two pneumatic muscles with one muscle
 * moving the joint in positive direction (index 0) and one in negative rotary
 * direction (index 1) with increasing pressure.
 *
 * The joint class stores the corresponding memory addresses of the FPGA.
 */
class NiFpga_joint
{
public:
    uint32_t controls[2];
    uint32_t min_pressures[2];
    uint32_t max_pressures[2];
    uint32_t set_pressures[2];
    uint32_t current_pressures[2];
    uint32_t reference_found;
    uint32_t stand_pressure[2];
    uint32_t encoder;
    double encoder_multiplier;
    double encoder_bias;
    bool encoder_inverse;
    bool encoder_negative;
};

/**
 * @brief Robot class using a FPGA designed by National Instruments Corp.
 *
 * A robot is a collection of joints with each joint defining
 * degrees of freedom. For controlling the robot, a number of
 * memory addresses of the FPGA API has to be engaged to control
 * the corresponding robot.
 */
class NiFpgaRobot
{
public:
    /**
     * Constructs a new NiFPGA Robot object.
     */
    NiFpgaRobot();

    /**
     * Destructs a NiFPGA Robot object.
     */
    ~NiFpgaRobot();

    /**
     * Sets the number of degrees of freedom.
     *
     * @param nb_dofs number of degrees of freedom
     */
    void set_nb_dofs(int nb_dofs);

public:
    NiFpga_joint *joints;
    uint32_t control_period;
    uint32_t sensor_period;
    int nb_dofs;
    NiFpga_Session session;
    std::string signature;
    uint32_t attribute;
    std::string ni_bit_file;
    std::string ni_resource;
    uint32_t iteration_sensor;
    uint32_t iteration_control;
};

}  // namespace pam_interface
