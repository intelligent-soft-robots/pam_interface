#pragma once

#include "pam_interface/driver.hpp"
#include "pam_interface/configuration.hpp"
#include "pam_interface/dummy/interface.hpp"

namespace pam_interface
{

  template<int NB_DOFS>
  class DummyRobotDriver
    : public Driver<NB_DOFS>
  {

  public:

    DummyRobotDriver(const Configuration<NB_DOFS>& config);

  };

  #include "driver.hxx"
  
}
