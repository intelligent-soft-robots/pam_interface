#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "pam_interface/sign.hpp"
#include "pam_interface/configuration.hpp"
#include "pam_interface/pressure_action.hpp"
#include "pam_interface/command.hpp"
#include "pam_interface/state/robot.hpp"
#include "pam_interface/real/driver.hpp"
#include "pam_interface/dummy/driver.hpp"

#define NB_DOFS 4

typedef pam_interface::Configuration<NB_DOFS> Config;
typedef pam_interface::JsonConfiguration<NB_DOFS> JsonConfig;
typedef pam_interface::DefaultConfiguration<NB_DOFS> DefaultConfig;
typedef pam_interface::PressureAction<2*NB_DOFS> PressureAction;
typedef pam_interface::Command<2*NB_DOFS> Command;
typedef pam_interface::RobotState<NB_DOFS> RobotState;
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
    .def_readwrite("min_pressures_antago",&Config::min_pressures_antago)
    .def("min_pressure",&Config::min_pressure)
    .def("max_pressure",&Config::max_pressure);
    
  
  pybind11::class_<JsonConfig,Config>(m,"JsonConfiguration")
    .def(pybind11::init<const std::string&>())
    .def("display",&JsonConfig::print);
  
  pybind11::class_<DefaultConfig,JsonConfig>(m,"DefaultConfiguration")
    .def(pybind11::init<>())
    .def("display",&DefaultConfig::print);
  
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

  m.def("signs",[](){
      std::array<pam_interface::Sign,2> a = {pam_interface::Sign::AGONIST,
					     pam_interface::Sign::ANTAGONIST};
      return a;
    });
  
  pybind11::class_<PressureAction>(m,"PressureAction")
    .def(pybind11::init<>())
    .def("get",(int(PressureAction::*)(int)const) &PressureAction::get)
    .def("get",(int(PressureAction::*)(int,pam_interface::Sign)const) &PressureAction::get)
    .def("set",(void(PressureAction::*)(int,int)) &PressureAction::set)
    .def("set",(void(PressureAction::*)(int,pam_interface::Sign,int)) &PressureAction::set);

  pybind11::class_<Command>(m,"Command")
    .def(pybind11::init<>())
    .def(pybind11::init<int>())
    .def(pybind11::init<int,PressureAction>())
    .def("get_id",&Command::get_id)
    .def("get_action",&Command::get_action);
  
  m.def("write_command",[](const std::string& segment_id,
			   std::array<int,NB_DOFS> agos,
			   std::array<int,NB_DOFS> antagos)
	{
	  static int id = 0;
	  PressureAction action;
	  for(int dof=0;dof<NB_DOFS;dof++)
	    {
	      action.set(dof,pam_interface::Sign::AGONIST,agos[dof]);
	      action.set(dof,pam_interface::Sign::ANTAGONIST,antagos[dof]);
	    }
	  Command command(id,action);
	  id++;
	  shared_memory::serialize(segment_id,"command",command);
	}
	);

  m.def("read_command",[](const std::string& segment_id)
	{
	  Command command;
	  shared_memory::deserialize(segment_id,"command",command);
	  return command;
	}
	);
  

  m.def("write_robot_state",[](const std::string& segment_id,
			       const RobotState& state)
	{
	  shared_memory::serialize(segment_id,"state",state);
	}
	);

  m.def("read_robot_state",[](const std::string& segment_id)
	{
	  RobotState state;
	  shared_memory::deserialize(segment_id,"state",state);
	  return state;
	}
	);
  
  m.def("init",[](const std::string& segment_id)
	{
	  shared_memory::clear_shared_memory(segment_id);
	  Command command(-1);
	  shared_memory::serialize(segment_id,"command",command);
	  RobotState state;
	  shared_memory::serialize(segment_id,"state",state);
	}
	);
  
  
  pybind11::class_<RealDriver>(m,"RealRobot")
    .def(pybind11::init<const Config>())
    .def("pressure_in",&RealDriver::in)
    .def("data_out",&RealDriver::out);
  
  pybind11::class_<DummyDriver>(m,"DummyRobot")
    .def(pybind11::init<const Config>())
    .def("pressure_in",&DummyDriver::in)
    .def("data_out",&DummyDriver::out);
  
}
