#pragma once

#include <fcntl.h>
#include <algorithm>
#include <limits>
#include <string>

#include "pam_interface/real/pamy2/configuration.hpp"
#include "pam_interface/real/pamy2/udp_structures.hpp"
#include "pam_interface/rotation.hpp"
#include "pam_interface/sign.hpp"
#include "pam_interface/state/robot.hpp"
#include "pam_interface/typedefs.hpp"

#define NB_DOFS 4
#define BUFFER_LENGTH 46

// for converting from "int" (pamy1 supported
// pressures values) to float (bars, pamy2 supported
// pressures values)
#define INT_TO_BAR_MULTIPLYER 0.0002
#define INT_TO_BAR_BIAS -1.7888

#define MIN_PRESSURE_BARS 0.2
#define MAX_PRESSURE_BARS 4.0

extern "C"
{
#include "pam_interface/real/pamy2/udp_c.h"
}

namespace pam_interface
{
/**
 * @brief UDPCommunication class.
 *
 * Manages the fetching of sensor information and sending of control
 * instructions via UPD networking.
 */
class UDPCommunication
{
public:
    /**
     * UDPCommunication constructor with specified system configuration
     * (e.g. including minimum and maximum available pressure), the target
     * IP address and port.
     *
     * @param configuration Configuration object fitting to corresponding
     * target system.
     * @param ip Corresponding target IP address for socket configuration.
     * @param port Corresponding target port for socket configuration.
     */
    UDPCommunication(Configuration<NB_DOFS>& configuration,
                     std::string ip,
                     uint port);

    /**
     * Send a pressure command, using the pressures as as set
     * by calls to the update_pressure method of this class
     * (minimal pression value if update_pressure has not been
     * called for a specific muscle)
     */
    void send();

    /**
     * Change the desired pressure for a muscle. A corresponding command
     * will be sent to the robot only when the method send of this class
     * is called.
     */
    void update_pressure(unsigned short dof, Sign sign, float desired_pressure);

    /**
     * Receives UDP telegram from the socket and
     * cast the information to an instance of RobotState
     */
    RobotState<NB_DOFS> receive();

    /**
     * Returns the structure encapsulating the data of the latest
     * received telegram.
     */
    const FromRobotMessage& get_received_message() const;

    /**
     * The control PC receives from the robot UPD telegrams that provide
     * the current pressures of the muscles in bar (ranging from 0.2 to
     * 4.0 bar). Because of historical reason (use of pamy1), we need
     * to convert to integral pressures ranging from the min pressure
     * and the max pressure (as provided by the configuration parameter
     * of the constructor)
     */
    int bar_to_int(float value) const;

    /**
     * Counterpart of convert_pressure (float)
     */
    float int_to_bar(int value) const;

private:
    c_socket socket_;              // for communication with the robot
    ToRobotMessage to_robot_;      // for encapsulating commands sent to robot
    FromRobotMessage from_robot_;  // for encapsulating data received from robot
};

/**
 * Convenience function that print in the terminal the
 * structure in a human readable way.
 */
void print_to_robot_message(const ToRobotMessage& message);

/**
 * Convenience function that print in the terminal the
 * structure in a human readable way.
 */
void print_robot_message(const FromRobotMessage& message);

}  // namespace pam_interface
