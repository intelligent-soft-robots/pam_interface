#pragma once

#include "pam_interface/configuration.hpp"
#include "pam_interface/driver.hpp"
#include "pam_interface/real/factory.hpp"

namespace pam_interface
{
template <int NB_DOFS>
class RealRobotDriver : public Driver<NB_DOFS>
{
public:
    RealRobotDriver(const Configuration<NB_DOFS>& config);
};

#include "driver.hxx"

}  // namespace pam_interface
