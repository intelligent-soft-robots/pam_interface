// Copyright 2018 Max Planck Gesellschaft
// Authors : Dieter Buchler and Vincent Berenz


#pragma once

#include "pam_interface/nifpga/robot.hpp"

namespace pam_interface {

    namespace four_dofs {

      #include "pam_interface/nifpga/4dofs/robot.hpp"
    
      int get_nb_dofs();
      static NiFpgaRobot _ROBOT;
      NiFpgaRobot *get_fpga_robot();

    }
  
}
