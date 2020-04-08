#pragma once

#include "robot_interfaces/robot_driver.hpp"
#include "pam_interface/state/robot.hpp"
#include "pam_interface/pressure_action.hpp"
#include "pam_interface/real/factory.hpp"

#include <memory>

namespace pam_interface
{

  // NB_DOFS*2 for some template types because 1 dof for 2 muscles
  
  template<int NB_DOFS>
  class Driver :
    public robot_interfaces::RobotDriver< PressureAction<2*NB_DOFS>,
					  RobotState<NB_DOFS> >
  {
    
  public:

    Driver(const Configuration<NB_DOFS>& configuration);
    ~Driver();
    
    virtual void initialize()=0;

    virtual std::string get_error()=0;
    
    PressureAction<2*NB_DOFS>
    apply_action(const PressureAction<2*NB_DOFS> &desired_action);
    
    RobotState<NB_DOFS> get_latest_observation();
    
    void shutdown();

  protected:

    std::shared_ptr<Interface<NB_DOFS>> hw_interface_;
    Configuration<NB_DOFS> config_;

  };

  #include "driver.hxx"
  
}
