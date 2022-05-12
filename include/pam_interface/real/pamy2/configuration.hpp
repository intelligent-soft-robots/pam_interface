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
/**
 * @brief Pamy2DefaultConfiguration Class
 *
 * Stores Pamy 2 default parameters.
 */
class Pamy2DefaultConfiguration : public JsonConfiguration<4>
{
public:
    /**
     * Constructs a new Pamy2DefaultConfiguration object.
     *
     * @param simulation Specifier for real or simulated robot
     */
    Pamy2DefaultConfiguration(bool simulation);

    /**
     * @brief Get the default configuration path object
     *
     * @param simulation Specifier for real or simulated robot
     * @return std::string Path to configuration file
     */
    static std::string get_default_configuration_path(bool simulation);
};

}  // namespace pam_interface
