#pragma once

#include <map>

#include "robot_interfaces/robot_driver.hpp"
#include "robot_interfaces/robot.hpp"

#include "pam_interface/pressure_action.hpp"
#include "pam_interface/state/robot.hpp"
#include "pam_interface/dummy/driver.hpp"
#include "pam_interface/real/driver.hpp"


namespace pam_interface
{

  template<int NB_DOFS>
  class Factory
  {

  public:
    
    typedef PressureAction<NB_DOFS*2> Action;
    typedef RobotState<NB_DOFS> Observation;
    typedef DummyRobotDriver<NB_DOFS> DummyDriver;
    typedef RealRobotDriver<NB_DOFS> RealDriver;

    typedef robot_interfaces::Robot<Action,Observation,DummyDriver> DummyRobot;
    typedef robot_interfaces::Robot<Action,Observation,RealDriver> RealRobot;

    typedef std::shared_ptr<DummyRobot> DummyRobotPtr;
    typedef std::shared_ptr<RealRobot> RealRobotPtr;

  private:

    template<typename A, typename APtr>
    static bool exists(std::map<int,APtr>&m,
		       int id);
    
    template<typename A, typename APtr>
    static APtr create_robot(std::map<int,APtr>&m,
			  int id,
			  const Configuration<NB_DOFS>& config);
    
    template<typename A, typename APtr>
    static APtr get_robot(std::map<int,APtr>&m, int id);

    static std::map<int,DummyRobotPtr> dummy_robots;
    static std::map<int,RealRobotPtr> real_robots;
    
  public:
    
    static DummyRobotPtr create_dummy(int id, const Configuration<NB_DOFS>& config);
    static RealRobotPtr create_real(int id, const Configuration<NB_DOFS>& config);
    
    static DummyRobotPtr get_dummy(int id);
    static RealRobotPtr get_real(int id);
    
  };

  #include "factory.hxx"
  
}
