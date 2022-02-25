#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "pam_interface/command.hpp"
#include "pam_interface/dummy/driver.hpp"
#include "pam_interface/pressure_action.hpp"
#include "pam_interface/real/pamy1/configuration.hpp"
#include "pam_interface/real/pamy1/driver.hpp"
#include "pam_interface/real/pamy2/configuration.hpp"
#include "pam_interface/sign.hpp"
#include "pam_interface/state/robot.hpp"
#include "shared_memory/shared_memory.hpp"

#define NB_DOFS 4

typedef pam_interface::Configuration<NB_DOFS> Config;
typedef pam_interface::JsonConfiguration<NB_DOFS> JsonConfig;
typedef pam_interface::Pamy1DefaultConfiguration<NB_DOFS> Pamy1DefaultConfig;
typedef pam_interface::Pamy2DefaultConfiguration Pamy2DefaultConfig;
typedef pam_interface::PressureAction<2 * NB_DOFS> PressureAction;
typedef pam_interface::Command<2 * NB_DOFS> Command;
typedef pam_interface::RobotState<NB_DOFS> RobotState;
typedef pam_interface::Pamy1Driver<NB_DOFS> Pamy1Driver;
typedef pam_interface::DummyRobotDriver<NB_DOFS> DummyDriver;

PYBIND11_MODULE(pam_interface, m)
{
    pybind11::class_<Config>(m, "Configuration")
        .def(pybind11::init<>())
        .def("display", &Config::print)
        .def_readwrite("control_period", &Config::control_period)
        .def_readwrite("sensor_period", &Config::sensor_period)
        .def_readwrite("max_pressures_ago", &Config::max_pressures_ago)
        .def_readwrite("min_pressures_ago", &Config::min_pressures_ago)
        .def_readwrite("max_pressures_antago", &Config::max_pressures_antago)
        .def_readwrite("min_pressures_antago", &Config::min_pressures_antago)
        .def("min_pressure",
             pybind11::overload_cast<int, pam_interface::Sign>(
                 &Config::min_pressure))
        .def("max_pressure",
             pybind11::overload_cast<int, pam_interface::Sign>(
                 &Config::max_pressure))
        .def("min_pressure", pybind11::overload_cast<>(&Config::min_pressure))
        .def("max_pressure", pybind11::overload_cast<>(&Config::max_pressure));

    pybind11::class_<JsonConfig, Config>(m, "JsonConfiguration")
        .def(pybind11::init<const std::string&>())
        .def("display", &JsonConfig::print);

    pybind11::class_<Pamy1DefaultConfig, JsonConfig>(
        m, "Pamy1DefaultConfiguration")
        .def(pybind11::init<>())
        .def("display", &Pamy1DefaultConfig::print)
        .def("get_path", &Pamy1DefaultConfig::get_default_configuration_path);

    pybind11::class_<Pamy2DefaultConfig, JsonConfig>(
        m, "Pamy2DefaultConfiguration")
        .def(pybind11::init<>())
        .def("display", &Pamy2DefaultConfig::print)
        .def("get_path", &Pamy2DefaultConfig::get_default_configuration_path);

    pybind11::class_<RobotState>(m, "RobotState")
        .def(pybind11::init<>())
        .def("get_id", &RobotState::get_id)
        .def("get_desired", &RobotState::get_desired)
        .def("get", &RobotState::get)
        .def("get_reference_found", &RobotState::get_reference_found)
        .def("get_encoder", &RobotState::get_encoder)
        .def("get_position", &RobotState::get_position)
        .def("get_velocity", &RobotState::get_velocity)
        .def("get_control_iteration", &RobotState::get_control_iteration)
        .def("get_sensor_iteration", &RobotState::get_sensor_iteration)
        .def("get_time_stamp", &RobotState::get_time_stamp)
        .def("display", &RobotState::print);

    pybind11::enum_<pam_interface::Sign>(m, "sign")
        .value("agonist", pam_interface::Sign::AGONIST)
        .value("antagonist", pam_interface::Sign::ANTAGONIST);

    m.def("signs", []() {
        std::array<pam_interface::Sign, 2> a = {
            pam_interface::Sign::AGONIST, pam_interface::Sign::ANTAGONIST};
        return a;
    });

    pybind11::class_<PressureAction>(m, "PressureAction")
        .def(pybind11::init<>())
        .def("get", (int (PressureAction::*)(int) const) & PressureAction::get)
        .def("get",
             (int (PressureAction::*)(int, pam_interface::Sign) const) &
                 PressureAction::get)
        .def("set", (void (PressureAction::*)(int, int)) & PressureAction::set)
        .def("set",
             (void (PressureAction::*)(int, pam_interface::Sign, int)) &
                 PressureAction::set);

    pybind11::class_<Command>(m, "Command")
        .def(pybind11::init<>())
        .def(pybind11::init<int>())
        .def(pybind11::init<int, PressureAction>())
        .def("get_id", &Command::get_id)
        .def("get_action", &Command::get_action);

    m.def("write_command",
          [](const std::string& segment_id,
             std::array<int, NB_DOFS> agos,
             std::array<int, NB_DOFS> antagos) {
              static int id = 0;
              PressureAction action;
              for (int dof = 0; dof < NB_DOFS; dof++)
              {
                  action.set(dof, pam_interface::Sign::AGONIST, agos[dof]);
                  action.set(
                      dof, pam_interface::Sign::ANTAGONIST, antagos[dof]);
              }
              Command command(id, action);
              id++;
              shared_memory::serialize(segment_id, "command", command);
          });

    m.def("read_command", [](const std::string& segment_id) {
        Command command;
        shared_memory::deserialize(segment_id, "command", command);
        return command;
    });

    m.def("write_robot_state",
          [](const std::string& segment_id, const RobotState& state) {
              shared_memory::serialize(segment_id, "state", state);
          });

    m.def("read_robot_state", [](const std::string& segment_id) {
        RobotState state;
        shared_memory::deserialize(segment_id, "state", state);
        return state;
    });

    m.def("init", [](const std::string& segment_id) {
        shared_memory::clear_shared_memory(segment_id);
        Command command(-1);
        shared_memory::serialize(segment_id, "command", command);
        RobotState state;
        shared_memory::serialize(segment_id, "state", state);
    });

    pybind11::class_<Pamy1Driver>(m, "Pamy1Robot")
        .def(pybind11::init<const Config>())
        .def("pressure_in", &Pamy1Driver::in)
        .def("data_out", &Pamy1Driver::out);

    pybind11::class_<DummyDriver>(m, "DummyRobot")
        .def(pybind11::init<const Config>())
        .def("pressure_in", &DummyDriver::in)
        .def("data_out", &DummyDriver::out);
}
