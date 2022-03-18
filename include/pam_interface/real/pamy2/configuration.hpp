#pragma once

#include "pam_configuration/pam_configuration.hpp"
#include "pam_interface/configuration.hpp"

// parent folder will be ~/.mpi-is/pam
// or /opt/mpi-is/pam
#define PAMY2_JSON_RELATIVE_PATH "pam_interface/pamy2/config/pam.json"

namespace pam_interface
{
class Pamy2DefaultConfiguration : public JsonConfiguration<4>
{
public:
    Pamy2DefaultConfiguration();
    static std::string get_default_configuration_path();
};

}  // namespace pam_interface
