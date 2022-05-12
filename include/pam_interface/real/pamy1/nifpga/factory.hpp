// Copyright 2018 Max Planck Gesellschaft
// Authors : Dieter Buchler and Vincent Berenz

#pragma once

#include "pam_interface/real/pamy1/nifpga/robot.hpp"

namespace pam_interface
{
namespace four_dofs
{
#include "pam_interface/real/pamy1/nifpga/4dofs/robot.hpp"

static NiFpgaRobot _ROBOT;

/**
 * Get specified number of degrees of freedom.
 *
 * @return int number of degrees of freedom
 */
int get_nb_dofs();

/**
 * Factory function for specifying number of degrees of freedom for
 * specified NiFpgaRobot along robot (Pamy 1) specific predefined
 * parameters. Returns pointer to NiFpgaRobot object.
 *
 * @return NiFpgaRobot* Pointer to NiFpgaRobot object
 */
NiFpgaRobot *get_fpga_robot();

}  // namespace four_dofs

}  // namespace pam_interface
