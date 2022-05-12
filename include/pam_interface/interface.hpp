#ifndef MR_INTERFACE_HPP
#define MR_INTERFACE_HPP

#include "pam_interface/configuration.hpp"
#include "pam_interface/sign.hpp"
#include "pam_interface/state/robot.hpp"

#include <stdlib.h>
#include <chrono>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#define UNUSED(x) (void)(x)

namespace pam_interface
{
/**
 * Checks if given variable v is within the range of the
 * min and max attributes.
 *
 * If v is smaller then min, min is returned.
 * If v is larger then max, max is returned.
 * If within the range, v is returned unchanged.
 *
 * @param min lower range value
 * @param max upper range value
 * @param v variable to be clipped
 *
 * @return int clipped variable
 */
int clip(int min, int max, int v);

/**
 * @brief Placeholder parent interface class.
 *
 * Parent interface class with virtual placeholder functions to be overloaded
 * for dummy, Pamy1 and Pamy2 specific interfaces.
 *
 * @tparam NB_DOFS number of degrees of freedom
 */
template <int NB_DOFS>
class Interface
{
public:
    Interface();

public:
    /**
     * Fetches states and returns RobotState object.
     *
     * @return RobotState<NB_DOFS>
     */
    virtual RobotState<NB_DOFS> get_state();

    /**
     * Sets given pressure value for specified degree of freedom
     * and specified agonist-antagonist specifier.
     *
     * @param dof index of desired degree of freedom
     * @param sign agonist-antagonist specifier (0 for agonist,
     * 1 for antagonist, see sign.hpp for reference)
     * @param value pressure value to be set
     *
     * @remark This function serves as virtual placeholder function
     * which can be overwritten by robot specific interface classes.
     */
    virtual void set_pressure(int dof, Sign sign, int value) = 0;

    /**
     * Initializes interface.
     */
    virtual void init()
    {
    }

    /**
     * Terminates interface.
     */
    virtual void terminate()
    {
    }

    /**
     * Executes final interation with closing robot-specific procedure
     * of sequence.
     */
    virtual void finalize_iteration()
    {
    }

protected:
    /**
     * Maps robot specific encoder values to angles.
     *
     * @param dof the degree of freedom the muscle is associated to. It
       has to be in the range 0 to 3 included, otherwise a runtime error
       is thrown.
     * @param encoder encoder value
     * @return double angle value
     */
    virtual double encoder_to_angle(int dof, int encoder)
    {
        UNUSED(dof);
        UNUSED(encoder);
        return 0.;
    }

    /**
     * Reads pressure values of specified degree of freedom
     * and specified agonist-antagonist sign specifier.
     *
     * @param dof the degree of freedom the muscle is associated to. It
       has to be in the range 0 to 3 included, otherwise a runtime error
       is thrown.
     * @param sign agonist-antagonist specifier
     * @return int pressure value
     */
    virtual int read_pressure(int dof, Sign sign)
    {
        UNUSED(dof);
        UNUSED(sign);
        return 0;
    }

    /**
     * Reads encoder values of specified degree of freedom.
     *
     * @param dof the degree of freedom the muscle is associated to. It
       has to be in the range 0 to 3 included, otherwise a runtime error
       is thrown.
     * @return int encoder value
     *
     * @remark even actuator indices are agonist actuators,
     * odd actuator indices specify antagonist actuators.
     */
    virtual int read_encoder(int dof)
    {
        UNUSED(dof);
        return 0;
    }

    /**
     * Reads sensor iteration.
     *
     * @return int sensor iteration
     */
    virtual int read_sensor_iteration()
    {
        return 0;
    }

    /**
     * Reads control interation.
     *
     * @return int control interation
     */
    virtual int read_control_iteration()
    {
        return 0;
    }

    /**
     * Returns statement if reference of specified
     * degree of freedom is found.
     *
     * @param dof index of degree of freedom.
     * @return true placeholder value.
     */
    virtual bool is_reference_found(int dof)
    {
        UNUSED(dof);
        return true;
    }

protected:
    RobotState<NB_DOFS> previous_state_;
    std::array<int, NB_DOFS> desired_agonists_;
    std::array<int, NB_DOFS> desired_antagonists_;
};

#include "interface.hxx"

}  // namespace pam_interface

#endif
