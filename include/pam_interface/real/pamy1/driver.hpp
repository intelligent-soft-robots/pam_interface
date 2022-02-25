#pragma once

#include "pam_interface/configuration.hpp"
#include "pam_interface/driver.hpp"
#include "pam_interface/real/pamy1/factory.hpp"

namespace pam_interface
{
template <int NB_DOFS>
class Pamy1Driver : public Driver<NB_DOFS>
{
public:
    Pamy1Driver(const Configuration<NB_DOFS>& config);
};

#include "driver.hxx"

}  // namespace pam_interface
