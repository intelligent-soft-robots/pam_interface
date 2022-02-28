// Copyright 2018 Max Planck Gesellschaft
// Authors : Dieter Buchler and Vincent Berenz

#pragma once

#include "pam_interface/real/pamy1/nifpga/robot.hpp"

namespace pam_interface
{
namespace four_dofs
{
#include "pam_interface/real/pamy1/nifpga/4dofs/robot.hpp"

int get_nb_dofs();
static NiFpgaRobot _ROBOT;
NiFpgaRobot *get_fpga_robot();

}  // namespace four_dofs

}  // namespace pam_interface
