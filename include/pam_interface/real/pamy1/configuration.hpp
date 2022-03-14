#pragma once

#include "pam_configuration/pam_configuration.hpp"
#include "pam_interface/configuration.hpp"

// parent folder will be ~/.mpi-is/pam
// or /opt/mpi-is/pam
#define PAMY1_JSON_RELATIVE_PATH "/pam_interface/pamy1/config/pam.json"

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
