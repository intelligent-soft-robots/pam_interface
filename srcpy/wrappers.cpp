#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "pam_interface/sign.hpp"
#include "pam_interface/configuration.hpp"
#include "pam_interface/pressure_action.hpp"
#include "pam_interface/state/robot.hpp"
#include "pam_interface/real/driver.hpp"
#include "pam_interface/dummy/driver.hpp"

#define NB_DOFS 4

typedef pam_interface::Configuration<NB_DOFS> Config;
typedef pam_interface::JsonConfiguration<NB_DOFS> JsonConfig;
typedef pam_interface::DefaultConfiguration<NB_DOFS> DefaultConfig;
typedef pam_interface::PressureAction<2*NB_DOFS> PAction;
typedef pam_interface::RobotState<NB_DOFS> RState;
typedef pam_interface::RealRobotDriver<NB_DOFS> RealDriver;
typedef pam_interface::DummyRobotDriver<NB_DOFS> DummyDriver;

PYBIND11_MODULE(pam_interface,m)
{

  pybind11::class_<Config>(m,"Configuration")
    .def(pybind11::init<>())
    .def("display",&Config::print)
    .def_readwrite("control_period",&Config::control_period)
    .def_readwrite("sensor_period",&Config::sensor_period)
    .def_readwrite("max_pressures_ago",&Config::max_pressures_ago)
    .def_readwrite("min_pressures_ago",&Config::min_pressures_ago) 
    .def_readwrite("max_pressures_antago",&Config::max_pressures_antago)
    .def_readwrite("min_pressures_antago",&Config::min_pressures_antago);

  pybind11::class_<JsonConfig,Config>(m,"JsonConfiguration")
    .def(pybind11::init<const std::string&>())
    .def("display",&JsonConfig::print);
  
  pybind11::class_<DefaultConfig,JsonConfig>(m,"DefaultConfiguration")
    .def(pybind11::init<>())
    .def("display",&DefaultConfig::print);
  
  pybind11::class_<RState>(m,"RobotState")
    .def(pybind11::init<>())
    .def("get_id",&RState::get_id)
    .def("get_desired",&RState::get_desired)
    .def("get",&RState::get)
    .def("get_reference_found",&RState::get_reference_found)
    .def("get_encoder",&RState::get_encoder)
    .def("get_position",&RState::get_position)
    .def("get_velocity",&RState::get_velocity)
    .def("get_control_iteration",&RState::get_control_iteration)
    .def("get_sensor_iteration",&RState::get_sensor_iteration)
    .def("get_time_stamp",&RState::get_time_stamp)
    .def("display",&RState::print);

  pybind11::enum_<pam_interface::Sign>(m,"sign")
    .value("agonist",pam_interface::Sign::AGONIST)
    .value("antagonist",pam_interface::Sign::ANTAGONIST);
    
  pybind11::class_<PAction>(m,"PressureAction")
    .def(pybind11::init<>())
    .def("get",(int(PAction::*)(int)const) &PAction::get)
    .def("get",(int(PAction::*)(int,pam_interface::Sign)const) &PAction::get)
    .def("set",(void(PAction::*)(int,int)) &PAction::set)
    .def("set",(void(PAction::*)(int,pam_interface::Sign,int)) &PAction::set);

  pybind11::class_<RealDriver>(m,"RealRobot")
    .def(pybind11::init<const Config>())
    .def("in",&RealDriver::in)
    .def("out",&RealDriver::out);
  
  pybind11::class_<DummyDriver>(m,"DummyRobot")
    .def(pybind11::init<const Config>())
    .def("in",&DummyDriver::in)
    .def("out",&DummyDriver::out);
  
}
