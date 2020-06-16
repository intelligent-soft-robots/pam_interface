#pragma once

#include "o80/driver.hpp"
#include "pam_interface/state/robot.hpp"
#include "pam_interface/pressure_action.hpp"
#include "pam_interface/real/factory.hpp"

#include <memory>

namespace pam_interface
{

  // NB_DOFS*2 for some template types because 1 dof for 2 muscles

  // concrete instances will be
  // pam_interface/real/driver.hpp
  // pam_interface/dummy/driver.hpp
  
  template<int NB_DOFS>
  class Driver
    : public o80::Driver<PressureAction<2*NB_DOFS>,
			 RobotState<NB_DOFS>>
  {
    
  public:

    Driver(const Configuration<NB_DOFS>& configuration);
    ~Driver();
    void set(const PressureAction<2*NB_DOFS> &pressure_action);
    RobotState<NB_DOFS> get();
    void stop();
    void start();
    
  protected:

    std::shared_ptr<Interface<NB_DOFS>> hw_interface_;
    Configuration<NB_DOFS> config_;

  };

  #include "driver.hxx"
  
}
