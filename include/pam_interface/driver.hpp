#pragma once

#include "pam_interface/pressure_action.hpp"
#include "pam_interface/real/factory.hpp"
#include "pam_interface/state/robot.hpp"

#include <memory>

namespace pam_interface
{
// NB_DOFS*2 for some template types because 1 dof for 2 muscles

// concrete instances will be
// pam_interface/real/driver.hpp
// pam_interface/dummy/driver.hpp

template <int NB_DOFS>
class Driver
{
public:
    Driver(const Configuration<NB_DOFS>& configuration);
    ~Driver();
    void in(const PressureAction<2 * NB_DOFS>& pressure_action);
    RobotState<NB_DOFS> out();

protected:
    std::shared_ptr<Interface<NB_DOFS>> hw_interface_;
    Configuration<NB_DOFS> config_;
};

#include "driver.hxx"

}  // namespace pam_interface
