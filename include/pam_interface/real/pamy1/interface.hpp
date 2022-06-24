// Copyright 2019 Max Planck Gesellschaft
// Author: Vincent Berenz

#pragma once

#include <stdlib.h>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "pam_interface/interface.hpp"
#include "pam_interface/real/pamy1/nifpga/factory.hpp"

namespace pam_interface
{
/**
 * @brief Pamy1Interface class.
 *
 * A wrapper over UDPCommunication to send pressure command
 * and receive robot state information.
 *
 * The constructor initialize the UDP socket communication.
 * The get_state method overrides the one of the superclass
 * Interface, and calls the receive method of the instance
 * of UDPCommunication.
 *
 * @tparam NB_DOFS Number of degrees of freedom
 */
template <int NB_DOFS>
class Pamy1Interface : public Interface<NB_DOFS>
{
public:
    /**
     * Constructs a new Pamy1Interface object.
     *
     * @param configuration Pamy1Configuration object.
     */
    Pamy1Interface(const Configuration<NB_DOFS> &configuration);

    /**
     * Destroys the Pamy1Interface object.
     */
    ~Pamy1Interface();

public:
    /**
     * Checks given status value and evaluates whether the status
     * is erroneous. Throws exception with given message in case
     * of faulty status.
     *
     * @param message Error message
     * @param status Reference status
     */
    void check_status(std::string message, NiFpga_Status status);

    /**
     * Initializes Pamy 1 specific interface.
     */
    void init();

    /**
     * Returns time difference of sensor iteration in microseconds
     * evaluated on system specific sensor period. The sensor period is
     * specified in the configuration file.
     *
     * @param delta_sensor_iteration Number of iterations between sensor
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
     * Terminates interface.
     */
    void terminate();

    /**
     * Reads pressure values of specified degree of freedom
     * and specified agonist-antagonist sign specifier.
     *
     * @param dof the degree of freedom the muscle is associated to. It
       has to be in the range 0 to 3 included, otherwise a runtime error
       is thrown.
     * @param sign agonist-antagonist specifier (Sign::AGONIST for agonist,
     * Sign::ANTAGONIST for antagonist)
     * @return pressure value
     */
    int read_pressure(int dof, Sign sign);

    /**
     * Reads encoder values of specified degree of freedom.
     *
     * @param dof Degree of freedom the muscle is associated to. It
       has to be in the range 0 to 3 included, otherwise a runtime error
       is thrown.
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
     * Returns statement if reference of specified
     * degree of freedom is found.
     *
     * @param dof Index of degree of freedom.
     * @return true if reference is set.
     */
    bool is_reference_found(int dof);

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
     * @param sign Agonist-antagonist specifier (Sign::AGONIST for agonist,
     * Sign::ANTAGONIST for antagonist)
     * @param value Pressure value to be set
     */
    void set_pressure(int dof, Sign sign, int value);

    /**
     * Reads boolean control value from specified degree of freedom
     * and specified agonist-antagonist. Throws NiFpga error and calls
     * terminate function if on_or_off does not correspond to NiFpga value.
     *
     * @param dof Index of desired degree of freedom
     * @param sign Agonist-antagonist specifier (Sign::AGONIST for agonist,
     * Sign::ANTAGONIST for antagonist)
     * @param on_or_off Control value
     */
    void read_control_loop(int dof, Sign sign, NiFpga_Bool &on_or_off);

    /**
     * Reads boolean control value from specified degree of freedom
     * and specified agonist-antagonist. Throws NiFpga error and calls
     * terminate function if on_or_off does not correspond to NiFpga value.
     *
     * @param dof Index of desired degree of freedom
     * @param sign Agonist-antagonist specifier (Sign::AGONIST for agonist,
     * Sign::ANTAGONIST for antagonist)
     * @param on_or_off Control value
     */
    void read_control_loop(int dof, Sign sign, int &on_or_off);

    /**
     * Starts control loop.
     *
     * @param on_or_off Control value
     * @param dof Index of desired degree of freedom
     * @param sign Agonist-antagonist specifier (Sign::AGONIST for agonist,
     * Sign::ANTAGONIST for antagonist)
     */
    void set_control_loop(NiFpga_Bool on_or_off, int dof, Sign sign);

    /**
     * Writes boolean control value specified in on_or_off via NiFpga
     * API of specified degree of freedom and specified agonist-antagonist.
     *
     * @param on_or_off Control value
     * @param dof Index of desired degree of freedom
     * @param sign Agonist-antagonist specifier (Sign::AGONIST for agonist,
     * Sign::ANTAGONIST for antagonist)
     */
    void set_control_loop(int on_or_off, int dof, Sign sign);

    /**
     * Writes boolean control value specified in on_or_off via NiFpga
     * API to all degrees of freedom and agonists and antagonists.
     *
     * @param on_or_off Control value
     */
    void set_control_loops(int on_or_off);

    /**
     * Writes boolean control value specified in on_or_off via NiFpga
     * API to all degrees of freedom and agonists and antagonists.
     *
     * @param on_or_off Control value
     */
    void set_control_loops(NiFpga_Bool on_or_off);

private:
    NiFpgaRobot *nifpga_robot_;
    Configuration<NB_DOFS> configuration_;
    bool exception_thrown_;
    bool terminated_;
    bool initialized_;

    /**
     * Time of instance creation.
     */
    std::chrono::high_resolution_clock::time_point start_time_;

    /**
     * Previous time control interation
     */
    std::chrono::high_resolution_clock::time_point previous_time_;

    /**
     * Current system time
     */
    std::chrono::high_resolution_clock::time_point time_now_;
};

#include "interface.hxx"

}  // namespace pam_interface
