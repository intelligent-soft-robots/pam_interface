
template <int NB_DOFS>
Driver<NB_DOFS>::Driver(const Configuration<NB_DOFS>& config)
    : hw_interface_(nullptr), config_(config)
{
}

template <int NB_DOFS>
Driver<NB_DOFS>::~Driver()
{
    hw_interface_->terminate();
}

/**
 * Assigns passed pressures of pressure_action to each muscle
 * of each degree of freedom via the hardware interface of FPGA.
 *
 * @tparam NB_DOFS Number of degrees of freedom.
 * @param pressure_action Object of PressureAction class specifying
 * the pressures values via get-method.
 */
template <int NB_DOFS>
void Driver<NB_DOFS>::in(const PressureAction<2 * NB_DOFS>& pressure_action)
{
    int dof;
    for (unsigned int actuator = 0; actuator < 2 * NB_DOFS; actuator++)
    {
        dof = actuator / 2;
        int pressure = pressure_action.get(actuator);
        if (actuator % 2 == 0)
        {
            hw_interface_->set_pressure(dof, Sign::AGONIST, pressure);
        }
        else
        {
            hw_interface_->set_pressure(dof, Sign::ANTAGONIST, pressure);
        }
    }
    hw_interface_->finalize_iteration();
}

/**
 * Fetches all states from hardware interface and
 * returns them for each degree of freedom.
 *
 * @tparam NB_DOFS number of degrees of freedom.
 * @return RobotState<NB_DOFS>
 */
template <int NB_DOFS>
RobotState<NB_DOFS> Driver<NB_DOFS>::out()
{
    return hw_interface_->get_state();
}
