#ifndef MR_INTERFACE_HPP
#define MR_INTERFACE_HPP

#include "pam_interface/nifpga/robot.hpp"
#include "pam_interface/state/robot.hpp"
#include "pam_interface/sign.hpp"
#include "pam_interface/configuration.hpp"

#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>
#include <chrono>

namespace pam_interface {


  template<int NB_DOFS>
  class Interface {

  public:

    Interface();
    
    RobotState<NB_DOFS> get_state();

    virtual double encoder_to_angle(int dof, int encoder) =0;

    virtual void terminate()=0;
    
    virtual int read_pressure(int dof,
			      Sign sign) =0;
    virtual int read_encoder(int dof) =0;
    virtual int read_sensor_iteration() =0;
    virtual int read_control_iteration() =0;
    virtual bool is_reference_found(int dof) =0;
    
    virtual int set_pressure(int dof, Sign sign, int value)=0;

  protected:

    RobotState<NB_DOFS> previous_state_;
    std::array<int,NB_DOFS> desired_agonists_;
    std::array<int,NB_DOFS> desired_antagonists_;
    
  };

  #include "interface.hxx"

}

#endif
