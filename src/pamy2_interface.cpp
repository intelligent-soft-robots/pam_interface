#include "pam_interface/real/pamy2/interface.hpp"

namespace pam_interface
{
Pamy2Interface::Pamy2Interface(Configuration<NB_DOFS>& configuration,
                               std::string ip,
                               uint port)
    : Interface<NB_DOFS>{},
      udp_{configuration, ip, port},
      config_{configuration}
{
}

RobotState<NB_DOFS> Pamy2Interface::get_state()
{
    RobotState<NB_DOFS> state = udp_.receive();
    return state;
}

void Pamy2Interface::set_pressure(int dof, Sign sign, int value)
{
    if (dof < 0 || dof > 3)
    {
        throw std::runtime_error(
            std::string("can not set pressure for degree of freedom ") +
            std::to_string(dof) + ": dof should be in range [0,3]");
    }
    value = clip(config_.min_pressure(dof, sign),
                 config_.max_pressure(dof, sign),
                 value);
    float value_d = udp_.int_to_bar(value);
    udp_.update_pressure(dof, sign, value_d);
}

void Pamy2Interface::finalize_iteration()
{
    udp_.send();
}

}  // namespace pam_interface
