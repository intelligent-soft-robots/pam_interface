// Copyright 2019 Max Planck Gesellschaft
// Author: Vincent Berenz

#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>
#include <memory>

#include "pam_interface/interface.hpp"
#include "pam_interface/nifpga/factory.hpp"

namespace pam_interface {

  /* ---------------- conversions ------------------------- */

  static inline NiFpga_Bool get_nifpga_bool(int v){
    if (v==0) return NiFpga_False;
    return NiFpga_True;
  }

  static inline NiFpga_Bool get_nifpga_bool(unsigned int v){
    if (v==0) return NiFpga_False;
    return NiFpga_True;
  }

  static inline int get_int(NiFpga_Bool v){
    if(v==NiFpga_False) return 0;
    return 1;
  }

  /* ---------------- static functions ------------------------- */


  template<typename T>
  static void _check_correct_size(std::string message,
				  const std::vector<T> &v,
				  int expected_size){

    if(v.size()==expected_size) return;

    std::ostringstream s;
    s  << "incorrect size for "
       << message << " : " << v.size()
       << "; expected " << expected_size;
    std::string error_message(s.str());

    throw std::length_error(error_message);

  }
  
  /* ------------------------------------------------------------ */
  
  template<int NB_DOFS>
  class RealRobotInterface
    : public Interface<NB_DOFS>
  {

  public:

    RealRobotInterface(const Configuration<NB_DOFS> &configuration)
      : Interface<NB_DOFS>(),
      configuration_(configuration),
      exception_thrown_(false),
      initialized_(false)
    {
      static_assert(NB_DOFS==4,"RealRobotInterface: only 4 dofs robot supported");
    }

    ~RealRobotInterface()
    {
      terminate();
    }
    
    void check_status(std::string message, NiFpga_Status status) 
    {
      if(!NiFpga_IsError(status)) return;
      if(!exception_thrown_){
	exception_thrown_ = true;
	std::cout << "pam_interface::RealRobotInterface exception " << message << std::endl;
	terminate();
	throw NiFpga_exception(message,status);
      }
    }

    void init()
    {

      if(initialized_)
	{
	  std::cout <<
	    std::string(std::string("\nwarning: ")+
			std::string("pam_interface::RealRobotInterface init ")+
			std::string("function called twice")) << std::endl;
	  return;
	}
      
      initialized_=true;

      // see : pam_interface/nifpga/factory.hpp
      std::cout << "\ninitializing fpga" << std::endl;
      nifpga_robot_ = four_dofs::get_fpga_robot();
      NiFpga_Status status;
      status = NiFpga_Initialize();
      check_status("initializing fpga",status);
      std::cout << "-- done" << std::endl;
      
      std::cout << "opening fpga" << std::endl;
      status = NiFpga_Open(nifpga_robot_->ni_bit_file.c_str(),
			   nifpga_robot_->signature.c_str(),
			   nifpga_robot_->ni_resource.c_str(),
			   nifpga_robot_->attribute,
			   &(nifpga_robot_->session));
      check_status("opening fpga",status);
      std::cout << "-- done" << std::endl;
      
      std::cout << "calling run function" << std::endl;
      status = NiFpga_Run(nifpga_robot_->session,0);
      check_status("calling run function",status);
      std::cout << "-- done" << std::endl;

      // deactivating air pressure (?)
      std::cout << "stopping control loops" << std::endl;
      set_control_loops(1);
      std::cout << "-- done" << std::endl;

      // setting control period to fpga
      std::cout << "setting control period" << std::endl;
      status = NiFpga_WriteU32(nifpga_robot_->session,
			       nifpga_robot_->control_period,
			       configuration_.control_period );
      check_status("setting control period",status);
      std::cout << "-- done" << std::endl;

      // setting sensor period to fpga
      std::cout << "setting sensor period" << std::endl;
      status = NiFpga_WriteU32(nifpga_robot_->session,
			       nifpga_robot_->sensor_period,
			       configuration_.sensor_period);
      check_status("setting sensor period",status);
      std::cout << "-- done" << std::endl;

      // setting min and max pressures to fpga
      std::cout << "setting minimal and maximal pressures" << std::endl;
      for(int dof=0;dof<NB_DOFS;dof++){
	for(Sign sign:signs){
	  status =
	    NiFpga_WriteI16(nifpga_robot_->session,
			    nifpga_robot_->joints[dof].max_pressures[sign],
			    sign==Sign::AGONIST?
			    configuration_.max_pressures_ago[dof]:
			    configuration_.max_pressures_antago[dof]);
	  check_status("setting maximal pressure",status);
	  status =
	    NiFpga_WriteI16(nifpga_robot_->session,
			    nifpga_robot_->joints[dof].min_pressures[sign],
			    sign==Sign::AGONIST?
			    configuration_.min_pressures_ago[dof]:
			    configuration_.min_pressures_antago[dof]);
	  check_status("setting minimal pressure",status);
	}
      }
      std::cout  << "-- done" << std::endl;

      // activating air pressure (?)
      std::cout << "starting control loops" << std::endl;
      set_control_loops(0);
      std::cout << "-- done" << std::endl;

    }
    
    Microseconds time_diff(int delta_sensor_iteration) 
    {
      return Microseconds(delta_sensor_iteration*configuration_.sensor_period);
    }

    double encoder_to_angle(int dof, int encoder) 
    {
      return encoder * nifpga_robot_->joints[dof].encoder_multiplier;
    }

    void terminate() 
    {
      if(!initialized_)
	return;
      
      if(terminated_)
	return;

      std::cout << "\nremoving pressure\n";
      set_control_loops(1);
      usleep(0.1 *1000 * 1000);
      std::cout << "closing fpga\n";
      NiFpga_Close(nifpga_robot_->session,0);
      usleep(0.1 *1000 * 1000);
      std::cout << "-- done\n";
      std::cout << "finalizing fpga\n";
      NiFpga_Finalize();
      usleep(0.1 *1000 * 1000);
      std::cout << "-- done\n\n";
      usleep(0.1 *1000 * 1000); // 0.1s
      terminated_=true;

    }
    
    int read_pressure(int dof,
		      Sign sign) 
    {
      int16_t value;
      NiFpga_Status status =
	NiFpga_ReadI16(nifpga_robot_->session,
		       nifpga_robot_->joints[dof].current_pressures[sign],
		       &value);
      check_status("reading pressure",status);
      return value;
    }
    
    int read_encoder(int dof) 
    {
      int get;
      NiFpga_Status status = NiFpga_ReadI32(nifpga_robot_->session,
					    nifpga_robot_->joints[dof].encoder,
					    &get);
      check_status("reading encoder",status);
      return get;
    }
    
    int read_sensor_iteration() 
    {
      NiFpga_Status status;
      int32_t get;
      status = NiFpga_ReadI32(nifpga_robot_->session,
			      nifpga_robot_->iteration_sensor,
			      &get);
      check_status("reading sensor iteration",status);
      return get;
    }
    
    int read_control_iteration() 
    {
      NiFpga_Status status;
      int32_t get;
      status = NiFpga_ReadI32(nifpga_robot_->session,
			      nifpga_robot_->iteration_control,
			      &get);
      check_status("reading motor iteration",status);
    }
    
    bool is_reference_found(int dof) 
    {
      NiFpga_Bool found;
      NiFpga_Status status = NiFpga_ReadBool(nifpga_robot_->session,
					     nifpga_robot_->joints[dof].reference_found,
					     &found);
      check_status("checking if reference is set",status);
      return (found==NiFpga_True);
    }

    static int clip(int min, int max, int v)
    {
      if(v<min) return min;
      if(v>max) return max;
      return v;
    }
    
    int set_pressure(int dof, Sign sign, int value)
    {
      if(sign==Sign::AGONIST)
	{
	  value = clip(configuration_.min_pressures_ago[dof],
		       configuration_.max_pressures_ago[dof],
		       value);
	}
      else{
	value = clip(configuration_.min_pressures_antago[dof],
		     configuration_.max_pressures_antago[dof],
		     value);
      }
      NiFpga_Status status;
      status = NiFpga_WriteI16(nifpga_robot_->session,
			       nifpga_robot_->joints[dof].set_pressures[sign],value);
      // tracking desired set values
      if (sign==Sign::AGONIST){
	this->desired_agonists_[dof]=value;
      } else {
	this->desired_antagonists_[dof]=value;
      }
      check_status("setting pressure",status);
    }

  void read_control_loop(int dof, Sign sign, NiFpga_Bool &on_or_off){
    NiFpga_Status status = NiFpga_ReadBool(nifpga_robot_->session,
					   nifpga_robot_->joints[dof].controls[sign],
					   &on_or_off);
    check_status("failed to read control loop",status);
  }

  void read_control_loop(int dof, Sign sign, int &on_or_off){
    NiFpga_Bool on_or_off_;
    read_control_loop(dof,sign,on_or_off_);
    on_or_off = get_int(on_or_off_);
  }

  void set_control_loop(NiFpga_Bool on_or_off, int dof, Sign sign){
    NiFpga_Status status = NiFpga_WriteBool(nifpga_robot_->session,
					    nifpga_robot_->joints[dof].controls[sign],
					    on_or_off);
    check_status("failed to set control loop",status);
  }

  void set_control_loop(int on_or_off, int dof, Sign sign){
    NiFpga_Bool on_or_off_ = get_nifpga_bool(on_or_off);
    set_control_loop(on_or_off_,dof,sign);
  }

  void set_control_loops(int on_or_off){
    for(int dof=0;dof<NB_DOFS;dof++){
      for(Sign sign:signs){
	this->set_control_loop(on_or_off,dof,sign);
      }
    }
  }

  void set_control_loops(NiFpga_Bool on_or_off){
    for(int dof=0;dof<NB_DOFS;dof++){
      for(Sign sign:signs){
	this->set_control_loop(on_or_off,dof,sign);
      }
    }
  }
    
  private:

    NiFpgaRobot* nifpga_robot_;
    Configuration<NB_DOFS> configuration_;
    bool exception_thrown_;
    bool terminated_ ;
    bool initialized_;
    
    // time this instance was created
    std::chrono::high_resolution_clock::time_point start_time_;
    // time control iteration was counted up previously
    std::chrono::high_resolution_clock::time_point previous_time_;
    // just now
    std::chrono::high_resolution_clock::time_point time_now_;
    
  };


}
