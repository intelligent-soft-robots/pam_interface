#pragma once

#include "pam_interface/state/robot.hpp"
#include "pam_interface/interface.hpp"
#include "pam_interface/configuration.hpp"

#include <cmath>
#include <chrono>
#include <array>

namespace pam_interface {


  template<int NB_DOFS>
  class DummyInterface : public Interface<NB_DOFS>

  {

  public:

    DummyInterface(const Configuration<NB_DOFS> &configuration);
		   
    ~DummyInterface();

    void init();
    void terminate();

    Microseconds time_diff(int delta_sensor_iteration) ;
    
    double encoder_to_angle(int dof, int encoder) ;

    int read_pressure(int dof,
		      Sign sign) ;
    int read_encoder(int dof) ;
    int read_sensor_iteration()  ;
    int read_control_iteration() ;
    bool is_reference_found(int dof) ;

    double read_angle(int dof) ;
    
    std::chrono::microseconds get_control_period() ;
    std::chrono::microseconds get_sensor_period() ;

    void set_pressure(int dof,
		      Sign sign,
		      int value);

  private:

    long int iteration(int period);

  private:

    Configuration<NB_DOFS> configuration_;
    
    std::array<int,NB_DOFS>  pressures_ago_;
    std::array<int,NB_DOFS>  pressures_antago_;
    std::array<double,NB_DOFS> positions_;
    std::array<int,NB_DOFS> encoder_readings_;
    std::array<bool,NB_DOFS> references_found_;

    Microseconds beginning_of_time_;

  };


  #include "interface.hxx"
  
}
