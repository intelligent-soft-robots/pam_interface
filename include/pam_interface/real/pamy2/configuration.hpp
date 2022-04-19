#pragma once

#include "pam_configuration/pam_configuration.hpp"
#include "pam_interface/configuration.hpp"

// parent folder will be ~/.mpi-is/pam
// or /opt/mpi-is/pam
// (same file for simulation and real robot)
#define PAMY2_REAL_JSON_RELATIVE_PATH "pam_interface/pamy2/config/pam.json"
#define PAMY2_SIM_JSON_RELATIVE_PATH "pam_interface/pamy2/config/pam.json"

namespace pam_interface
{
class Pamy2DefaultConfiguration : public JsonConfiguration<4>
{
public:
    Pamy2DefaultConfiguration(bool simulation);
    static std::string get_default_configuration_path(bool simulation);
};

}  // namespace pam_interface
