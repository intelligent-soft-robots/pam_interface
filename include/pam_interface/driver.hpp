#pragma once

#include "pam_interface/interface.hpp"
#include "pam_interface/pressure_action.hpp"
#include "pam_interface/state/robot.hpp"

#include <memory>

namespace pam_interface
{
/**
 * @brief Driver parent class for pam_interface.
 *
 * Parent driver class for dummy, Pamy1 and Pamy2.
 *
 * @remark NB_DOFS is multiplied by 2 as for each degree of
 * freedom two muscles in agonist-antagonist configuration is
 * necessary.
 *
 * @tparam NB_DOFS number of degrees of freedom
 */
template <int NB_DOFS>
class Driver
{
public:
    /**
     * Constructs a new Driver object based on given
     * configuration object.
     *
     * @param configuration Object of Configuration class.
     */
    Driver(const Configuration<NB_DOFS>& configuration);

    /**
     * Destructs Driver object after runtime.
     */
    ~Driver();

    /**
     * Assigns passed pressures of pressure_action to each muscle
     * of each degree of freedom via the hardware interface of FPGA.
     *
     * @param pressure_action Object of PressureAction class.
     */
    void in(const PressureAction<2 * NB_DOFS>& pressure_action);

    /**
     * Fetches all states from hardware interface and returns them
     * for each degree of freedom as RobotState instance.
     *
     * @return RobotState<NB_DOFS>
     */
    RobotState<NB_DOFS> out();

protected:
    std::shared_ptr<Interface<NB_DOFS>> hw_interface_;
    Configuration<NB_DOFS> config_;
};

#include "driver.hxx"

}  // namespace pam_interface
