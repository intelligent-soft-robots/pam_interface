#pragma once

#include <array>
#include <stdexcept>
#include "pam_interface/sign.hpp"
#include "shared_memory/serializer.hpp"

namespace pam_interface
{


  template<int NB_ACTUATORS>
  class PressureAction
  {

  public:

    PressureAction(){}
    PressureAction(const PressureAction<NB_ACTUATORS>& other);
    PressureAction(PressureAction<NB_ACTUATORS>&& other) noexcept;
    PressureAction<NB_ACTUATORS>& operator=(const PressureAction<NB_ACTUATORS>& other);
    PressureAction<NB_ACTUATORS>& operator=(PressureAction<NB_ACTUATORS>&& other) noexcept;
    
    int get(int actuator) const;
    int get(int dof, Sign sign) const;
      
    void set(int actuator, int pressure);
    void set(int dof, Sign sign, int pressure);

    template <class Archive>
    void serialize(Archive &archive)
    {
      archive(pressures_);
    }
    
  private:
    
    friend shared_memory::private_serialization;
    std::array<int,NB_ACTUATORS> pressures_;
    
  };

  #include "pressure_action.hxx"

}
