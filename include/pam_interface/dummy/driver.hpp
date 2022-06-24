#pragma once

#include "pam_interface/configuration.hpp"
#include "pam_interface/driver.hpp"
#include "pam_interface/dummy/interface.hpp"

namespace pam_interface
{
/**
 * @brief Dummy robot driver child class.
 *
 * Dummy robot driver can be used for testing and
 * debugging of pam_interface, if real robot environment
 * is not available.
 *
 * @tparam NB_DOFS Number of degrees of freedom.
 */
template <int NB_DOFS>
class DummyRobotDriver : public Driver<NB_DOFS>
{
public:
    /**
     * Constructs a new Dummy Robot Driver object.
     *
     * @param config Object of Configuration class.
     */
    DummyRobotDriver(const Configuration<NB_DOFS>& config);
};

#include "driver.hxx"

}  // namespace pam_interface
