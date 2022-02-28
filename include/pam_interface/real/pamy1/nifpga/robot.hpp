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

namespace pam_interface
{
// code common to all robots ------------------------------------------

// a joint has 2 muscles, one for which increase of pressure means
// moving positively (index 0) and one for which increase of pressure
// means moving negatively (index 1)
// This class just stores the memory addresses on the FPGA
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

// a robot is a collection of joints, one per dofs
// + some memory addresses relevant to the whole robot
class NiFpgaRobot
{
public:
    NiFpgaRobot();
    ~NiFpgaRobot();
    void set_nb_dofs(int nb_dofs);
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
