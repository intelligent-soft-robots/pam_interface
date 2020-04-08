#pragma once

#include "shared_memory/serializer.hpp"
#include "pam_interface/sign.hpp"
#include "pam_interface/typedefs.hpp"
#include "pam_interface/state/joint.hpp"

#include <chrono>
#include <vector>
#include <array>
#include <cstring>
#include <iostream>

namespace pam_interface {


  template<int NB_DOFS>
  class RobotState  {

  public:

    RobotState(int id);
    RobotState(int control_iteration,
		  int sensor_iteration,
		  TimePoint time_stamp);
    RobotState();
    ~RobotState();

    RobotState(const RobotState<NB_DOFS>& other);
    RobotState(RobotState<NB_DOFS>&& other) noexcept;
    RobotState<NB_DOFS>& operator=(const RobotState<NB_DOFS>& other);
    RobotState<NB_DOFS>& operator=(RobotState<NB_DOFS>&& other) noexcept;

    
  public:

    /* set the values for the specified joint
     *
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

    /* returns id of the state.
     * Each new state instance is attributed the id : id of previously
     * instantiated RobotState + 1
     * except if instantiated by passing an int value, which will 
     * then be the id
     * @return : state id
     */
    int get_id() const;
    
    /* returns the latest pressure set to the fpga
     * @param dof : degree of freedom
     * @param sign : Sign::AGONIST for agonist, Sign::ANTAGONIST for antagonist
     * @return : pressure value
     */
    int get_desired(int dof, Sign sign) const;

    /* returns the current pressure for the specified PAM
     * @param dof : degree of freedom
     * @param sign : Sign::AGONIST for agonist, Sign::ANTAGONIST for antagonist
     * @return : pressure value
     */
    int get(int dof, Sign sign) const;


    /* returns whether or not the reference for the specified
     * degree of freedom was found, i.e. the values returned
     * by the functions "get_encoder" and "get_angle" will
     * be meaningfull.
     * @param dof: the degree of freedom
     * @return : true if the reference was found
     * @see get_encoder
     * @see get_angle
     */
    bool get_reference_found(int dof) const;

    /* Values of encoder.
     * Note : will be a meaningfull value only
     * if the reference for the specified degree of freedom
     * has been found
     * @param dof: the degree of freedom
     * @return : the encoder value
     * @see : get_reference_found
     */
    int get_encoder(int dof) const;

    /* Values of angle as read by the encoder
     * Note : will be a meaningfull value only
     * if the reference for the specified degree of freedom
     * has been found
     * @param dof: the degree of freedom
     * @return : the angle value
     * @see : get_reference_found
     */
    double get_position(int dof) const;

    /* Values of angle velocites as read by the encoder
     * Note : will be a meaningfull value only
     * if the reference for the specified degree of freedom
     * has been found
     * @param dof: the degree of freedom
     * @return : the angle velocity value
     * @see : get_reference_found
     */
    double get_velocity(int dof) const ;

    /* returns the value of the control iteration
     * of the FPGA at the time this instance was created
     */
    int get_control_iteration() const;

    /* returns the value of the control iteration
     * of the FPGA at the time this instance was created
     */
    int get_sensor_iteration() const;

    /* Returns the time stamp at which
     * the server wrote the values corresponding
     * to this robot state
     */
    long int get_time_stamp() const;

    /* 
     * Print the current and desired pressures 
     * in the terminal
     */
    void print() const;
      
    
    const JointState& get_joint_state(int dof) const;

  public:

    // for exchange_manager to be able to serialize a
    // command
    template<class Archive>
    void serialize(Archive &archive)
    {
      // note: the command_status_, which is used for
      // monitoring of the execution of the command by a controller,
      // is excluded
      archive( joints_,
	       control_iteration_,
	       sensor_iteration_,
	       time_stamp_,
	       id_ );
    }


  private:

    void copy(const RobotState<NB_DOFS>& other);
    
  private:

    // for shared_memory::serializer to be able to serialize
    // a command into a string (used internally by exchange_manager)
    friend shared_memory::private_serialization;

    int id_;
    std::array<JointState,NB_DOFS> joints_;
    int control_iteration_;
    int sensor_iteration_;
    long int time_stamp_;
    
  };


  #include "robot.hxx"
  
}
