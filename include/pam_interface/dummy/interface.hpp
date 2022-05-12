#pragma once

#include "pam_interface/configuration.hpp"
#include "pam_interface/interface.hpp"
#include "pam_interface/state/robot.hpp"

#include <array>
#include <chrono>
#include <cmath>

namespace pam_interface
{
/**
 * @brief DummyInterface class
 *
 * @tparam NB_DOFS Number of degrees of freedom
 */
template <int NB_DOFS>
class DummyInterface : public Interface<NB_DOFS>
{
public:
    /**
     * Constructs a new DummyInterface object.
     *
     * @param configuration DummyConfiguration object.
     */
    DummyInterface(const Configuration<NB_DOFS> &configuration);

    /**
     * Destroys the DummyInterface object.
     */
    ~DummyInterface();

public:
    /**
     * Initializes Pamy 1 specific interface.
     */
    void init();

    /**
     * Terminates interface.
     */
    void terminate();

    /**
     * Returns time difference of sensor iteration in microseconds
     * evaluated on system specific sensor period. The sensor period is
     * specified in the configuration file.
     *
     * @param delta_sensor_iteration Number of iterations between sensor \
     * measurements
     * @return Time difference in microseconds
     */
    Microseconds time_diff(int delta_sensor_iteration);

    /**
     * Maps robot specific encoder values to angles.
     *
     * @param dof Degree of freedom the muscle is associated to. It
       has to be in the range 0 to 3 included, otherwise a runtime error
       is thrown.
     * @param encoder Encoder value
     * @return Angle value
     */
    double encoder_to_angle(int dof, int encoder);

    /**
     * Reads pressure values of specified degree of freedom
     * and specified agonist-antagonist sign specifier.
     *
     * @param dof Degree of freedom the muscle is associated to. It
       has to be in the range 0 to 3 included, otherwise a runtime error
       is thrown
     * @param sign Agonist-antagonist specifier
     * @return Pressure value
     */
    int read_pressure(int dof, Sign sign);

    /**
     * Reads encoder values of specified degree of freedom.
     *
     * @param dof the degree of freedom the muscle is associated to. It
       has to be in the range 0 to 3 included, otherwise a runtime error
       is thrown
     * @return Encoder value
     */
    int read_encoder(int dof);

    /**
     * Reads current sensor iteration.
     *
     * @return Sensor iteration
     */
    int read_sensor_iteration();

    /**
     * Reads current control interation.
     *
     * @return Control interation
     */
    int read_control_iteration();

    /**
     * Returns statement if reference of specified degree of
     * freedom is found.
     *
     * @param dof Index of degree of freedom
     * @return true if reference is set
     */
    bool is_reference_found(int dof);

    /**
     * Reads current angle of specified degree of freedom.
     *
     * @param dof Degree of freedom
     * @return Angle value
     */
    double read_angle(int dof);

    /**
     * Fetches current control period between two control
     * outputs.
     *
     * @return Time period between control periods in
     * microseconds
     */
    std::chrono::microseconds get_control_period();

    /**
     * Fetches time period between last and penultimate sensor
     * measurement.
     *
     * @return Time period between sensor measurements in
     * microseconds
     */
    std::chrono::microseconds get_sensor_period();

    /**
     * Sets given pressure value for specified degree of freedom
     * and specified agonist-antagonist specifier.
     *
     * Requests a change of pressure of the specified muscle.
     * Does not send an UDP telegram to the robot.
     * Pressure commands will be sent to the robot when the
     * finalize_iteration method is called.
     * If for a given muscle set_pressure is called several times,
     * before finalize_iteration is called, only the latest call
     * will have effect.
     *
     * @param dof Index of desired degree of freedom
     * @param sign Agonist-antagonist specifier
     * @param value Pressure value to be set
     */
    void set_pressure(int dof, Sign sign, int value);

private:
    /**
     * Measures time difference of given period and returns
     * number of iterations.
     *
     * @param period Time period in microseconds
     * @return number of interations
     */
    long int iteration(int period);

private:
    Configuration<NB_DOFS> configuration_;

    std::array<int, NB_DOFS> pressures_ago_;
    std::array<int, NB_DOFS> pressures_antago_;
    std::array<double, NB_DOFS> positions_;
    std::array<int, NB_DOFS> encoder_readings_;
    std::array<bool, NB_DOFS> references_found_;

    Microseconds beginning_of_time_;
};

#include "interface.hxx"

}  // namespace pam_interface
