#pragma once

#include "pam_interface/interface.hpp"
#include "pam_interface/real/pamy2/udp_communication.hpp"

namespace pam_interface
{
/** A wrapper over UDPCommunication to send pressure command
 * and receive robot state information.
 *
 * The constructor initialize the UDP socket communication.
 * The get_state method overrides the one of the superclass
 * Interface, and calls the receive method of the instance
 * of UDPCommunication.
 */
class Pamy2Interface : public Interface<NB_DOFS>
{
    // dev note: the corresponding cpp file is /src/pamy2_interface.cpp

public:
    /**
     * Instantiate an instance of UDPCommunication, i.e. initialise
     * the UDP socket for communication with the robot.
     *
     * @param configuration Configuration of the robot (only
     * the maximum and minimal pressures will be used)
     * @param ip IP of the robot
     * @param port Port set on the robot for udp communication
     */
    Pamy2Interface(Configuration<NB_DOFS>& configuration,
                   std::string ip,
                   uint port);
    /**
     * Returns the latest state of the robot (as provided
     * by the latest telegram received via the UDP connection)
     */
    RobotState<NB_DOFS> get_state() override;

    /**
     * Requests a change of pressure of the specified muscle. Does not
     * send an udp telegram to the robot. Pressure commands will be sent
     * to the robot when the finalize_iteration method is called.
     *
     * If for a given muscle set_pressure is called several times,
     * before finalize_iteration is called, only the latest call
     * will have effect.
     *
     * @param dof Degree of freedoms the muscle is associated to. It
       has to be in the range 0 to 3 included, otherwise a runtime error
       is thrown.
     * @param sign Sign (i.e. agonist or antagonist) the muscle
     * is associated to.
     * @param value Desired pressure value. The method will cap it
     * between the min and max pressure values as set by the configuration
     * parameter passed to the constructor.
     */
    void set_pressure(int dof, Sign sign, int value);

    /**
     * Send an UDP telegram command to the robot, with desired pressures
     * set according to the value provided by calls to the set_pressure
     * method. If set_pressure has never been called for a given muscle,
     * then this desired pressure will be the minimal pressure.
     */
    void finalize_iteration() override;

private:
    UDPCommunication udp_;
    Configuration<NB_DOFS> config_;
};
}  // namespace pam_interface
