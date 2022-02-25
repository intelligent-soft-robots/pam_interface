#pragma once

#include "pam_interface/configuration.hpp"

namespace pam_interface
{
template <int NB_DOFS>
class Pamy1DefaultConfiguration : public JsonConfiguration<NB_DOFS>
{
public:
    Pamy1DefaultConfiguration();
    static std::string get_default_configuration_path();
};

#include "configuration.hxx"

}  // namespace pam_interface
