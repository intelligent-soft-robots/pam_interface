#pragma once

#include "pam_interface/sign.hpp"
#include "pam_interface/state/joint.hpp"
#include "pam_interface/typedefs.hpp"
#include "shared_memory/serializer.hpp"

#include <array>
#include <chrono>
#include <cstring>
#include <iostream>
#include <vector>

namespace pam_interface
{
namespace internal
{
int next_id();
}

/**
 * @brief RobotState management class.
 *
 * Provides utilities for handeling robot states with arbitary
 * number of joints with arbitary number of degrees of freedom.
 *
 * @tparam NB_DOFS number of degrees of freedom
 */
template <int NB_DOFS>
class RobotState
{
public:
    /**
     * RobotState constructor with specified state ID.
     *
     * @param id State ID
     */
    RobotState(int id);

    /**
     * RobotState constructor with specified control iteration, sensor
     * iteration and time stamp.
     *
     * @param control_iteration Iteration of control output
     * @param sensor_iteration Iteration of sensor input
     * @param time_stamp System time stamp
     */
    RobotState(int control_iteration,
               int sensor_iteration,
               TimePoint time_stamp);

    /**
     * RobotState constructor.
     *
     * Fetches the state ID automatically.
     */
    RobotState();

    /**
     * RobotState destructor.
     */
    ~RobotState();

public:
    /**
     * Sets the values for the specified joint.
     */
    void set_joint(int dof,
                   int agonist,
                   int antagonist,
                   int desired_agonist,
                   int desired_antagonist,
                   double position,
                   double velocity,
                   int encoder,
                   bool reference_found);

    /**
     * Returns ID of the state.
     * Each new state instance is attributed the ID : ID of previously
     * instantiated RobotState + 1 except if instantiated by passing
     * an int value, which will then be the id.
     *
     * @return state id
     */
    int get_id() const;

    /**
     * Returns the latest pressure set to the FPGA.
     *
     * @param dof degree of freedom
     * @param sign agonist-antagonist specifier (Sign::AGONIST for agonist,
     * Sign::ANTAGONIST for antagonist)
     * @return pressure value
     */
    int get_desired(int dof, Sign sign) const;

    /**
     * Returns the current pressure for the specified PAM.
     *
     * @param dof degree of freedom
     * @param sign agonist-antagonist specifier (Sign::AGONIST for agonist,
     * Sign::ANTAGONIST for antagonist)
     * @return pressure value
     */
    int get(int dof, Sign sign) const;

    /**
     * Returns whether or not the reference for the specified
     * degree of freedom was found, i.e. the values returned
     * by the functions "get_encoder" and "get_angle" will
     * be meaningful.
     *
     * @param dof degree of freedom
     * @return true if the reference was found
     *
     * @see get_encoder
     * @see get_angle
     */
    bool get_reference_found(int dof) const;

    /**
     * Values of encoder.
     *
     * @param dof degree of freedom
     * @return the encoder value
     *
     * @see get_reference_found
     * @remark will be a meaningful value only if the reference for
     * the specified degree of freedom has been found
     */
    int get_encoder(int dof) const;

    /**
     * Values of angle as read by the encoder.
     *
     * @param dof degree of freedom
     * @return the angle value
     *
     * @remark will be a meaningful value only if the reference for
     * the specified degree of freedom has been found
     * @see get_reference_found
     */
    double get_position(int dof) const;

    /**
     * Values of angle velocites as read by the encoder.
     *
     * Will be a meaningful value only if the reference
     * for the specified degree of freedom has been found.
     *
     * @param dof degree of freedom
     * @return angle velocity value
     * @see get_reference_found
     */
    double get_velocity(int dof) const;

    /**
     * Returns the value of the control iteration
     * of the FPGA at the time this instance was created.
     */
    int get_control_iteration() const;

    /**
     * Returns the value of the control iteration
     * of the FPGA at the time this instance was created.
     */
    int get_sensor_iteration() const;

    /**
     * Returns the time stamp at which the server wrote
     * the values corresponding to this robot state.
     */
    long int get_time_stamp() const;

    /**
     * Prints the current and desired pressures
     * in the terminal.
     */
    void print() const;

    /**
     * @brief Get the joint state object
     *
     * @param dof index of degree of freedom
     * @return const JointState& joint state
     */
    const JointState& get_joint_state(int dof) const;

public:
    /**
     * Enables exchange_manager to serialize a command.
     *
     * @tparam Archive template variable
     * @param archive reference to archive object
     */
    template <class Archive>
    void serialize(Archive& archive)
    {
        // note: the command_status_, which is used for
        // monitoring of the execution of the command by a controller,
        // is excluded
        archive(
            joints_, control_iteration_, sensor_iteration_, time_stamp_, id_);
    }

private:
    // for shared_memory::serializer to be able to serialize
    // a command into a string (used internally by exchange_manager)
    friend shared_memory::private_serialization;

    int id_;
    std::array<JointState, NB_DOFS> joints_;
    int control_iteration_;
    int sensor_iteration_;
    long int time_stamp_;
};

#include "robot.hxx"

}  // namespace pam_interface
