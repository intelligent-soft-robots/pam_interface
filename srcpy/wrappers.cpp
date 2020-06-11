#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "pam_interface/factory.hpp"
#include "pam_interface/sign.hpp"

#define NB_DOFS 4

typedef pam_interface::Configuration<NB_DOFS> Configuration;
typedef pam_interface::JsonConfiguration<NB_DOFS> JsonConfiguration;
typedef pam_interface::DefaultConfiguration<NB_DOFS> DefaultConfiguration;
typedef pam_interface::PressureAction<2*NB_DOFS> PressureAction;
typedef pam_interface::RobotState<NB_DOFS> RobotState;
typedef pam_interface::Factory<NB_DOFS> Factory;
typedef pam_interface::Factory<NB_DOFS>::DummyRobot DummyRobot;
typedef pam_interface::Factory<NB_DOFS>::RealRobot RealRobot;
typedef pam_interface::Factory<NB_DOFS>::DummyRobotPtr DummyRobotPtr;
typedef pam_interface::Factory<NB_DOFS>::RealRobotPtr RealRobotPtr;

/*
typedef robot_interfaces::TimeIndex TimeIndex;

template<typename RobotTypePtr,
	 RobotTypePtr(*Factory)(int,const Configuration&)>
class Robot
{
public:
  Robot(int id,const Configuration& config)
    : robot_(Factory(id,config)){}
  TimeIndex append_desired_action(const PressureAction& action)
  {
    return robot_->append_desired_action(action);
  }
  RobotState get_observation(TimeIndex index)
  {
    return robot_->get_observation(index);
  }
protected:
  RobotTypePtr robot_;
};

typedef Robot<pam_interface::Factory<NB_DOFS>::DummyRobotPtr,
	      pam_interface::Factory<NB_DOFS>::create_dummy> DummyRobot;

typedef Robot<pam_interface::Factory<NB_DOFS>::RealRobotPtr,
	      pam_interface::Factory<NB_DOFS>::create_real> RealRobot;
*/

PYBIND11_MODULE(pam_interface,m)
{

  pybind11::class_<Configuration>(m,"Configuration")
    .def(pybind11::init<>())
    .def("display",&Configuration::print)
    .def_readwrite("control_period",&Configuration::control_period)
    .def_readwrite("sensor_period",&Configuration::sensor_period)
    .def_readwrite("max_pressures_ago",&Configuration::max_pressures_ago)
    .def_readwrite("min_pressures_ago",&Configuration::min_pressures_ago) 
    .def_readwrite("max_pressures_antago",&Configuration::max_pressures_antago)
    .def_readwrite("min_pressures_antago",&Configuration::min_pressures_antago);

  pybind11::class_<JsonConfiguration,Configuration>(m,"JsonConfiguration")
    .def(pybind11::init<const std::string&>())
    .def("display",&JsonConfiguration::print);
  
  pybind11::class_<DefaultConfiguration,JsonConfiguration>(m,"DefaultConfiguration")
    .def(pybind11::init<>())
    .def("display",&DefaultConfiguration::print);
  
  pybind11::class_<RobotState>(m,"RobotState")
    .def(pybind11::init<>())
    .def("get_id",&RobotState::get_id)
    .def("get_desired",&RobotState::get_desired)
    .def("get",&RobotState::get)
    .def("get_reference_found",&RobotState::get_reference_found)
    .def("get_encoder",&RobotState::get_encoder)
    .def("get_position",&RobotState::get_position)
    .def("get_velocity",&RobotState::get_velocity)
    .def("get_control_iteration",&RobotState::get_control_iteration)
    .def("get_sensor_iteration",&RobotState::get_sensor_iteration)
    .def("get_time_stamp",&RobotState::get_time_stamp)
    .def("display",&RobotState::print);

  pybind11::enum_<pam_interface::Sign>(m,"sign")
    .value("agonist",pam_interface::Sign::AGONIST)
    .value("antagonist",pam_interface::Sign::ANTAGONIST);
    
  pybind11::class_<PressureAction>(m,"PressureAction")
    .def(pybind11::init<>())
    .def("get",(int(PressureAction::*)(int)const) &PressureAction::get)
    .def("get",(int(PressureAction::*)(int,pam_interface::Sign)const) &PressureAction::get)
    .def("set",(void(PressureAction::*)(int,int)) &PressureAction::set)
    .def("set",(void(PressureAction::*)(int,pam_interface::Sign,int)) &PressureAction::set);

  pybind11::class_<DummyRobot,DummyRobotPtr>(m,"DummyRobot")
    .def("append_desired_action",&DummyRobot::append_desired_action)
    .def("get_observation",&DummyRobot::get_observation)
    .def("get_desired_action",&DummyRobot::get_desired_action)
    .def("get_applied_action",&DummyRobot::get_applied_action)
    .def("get_time_stamp_ms",&DummyRobot::get_time_stamp_ms)
    .def("get_current_timeindex",&DummyRobot::get_current_timeindex)
    .def("wait_until_timeindex",&DummyRobot::wait_until_timeindex);

  pybind11::class_<RealRobot,RealRobotPtr>(m,"RealRobot")
    .def("append_desired_action",&RealRobot::append_desired_action)
    .def("get_observation",&RealRobot::get_observation)
    .def("get_desired_action",&RealRobot::get_desired_action)
    .def("get_applied_action",&RealRobot::get_applied_action)
    .def("get_time_stamp_ms",&RealRobot::get_time_stamp_ms)
    .def("get_current_timeindex",&RealRobot::get_current_timeindex)
    .def("wait_until_timeindex",&RealRobot::wait_until_timeindex);

  pybind11::class_<Factory>(m,"Factory")
    .def_static("create_dummy",&Factory::create_dummy)
    .def_static("create_real",&Factory::create_real);
  
  
}
