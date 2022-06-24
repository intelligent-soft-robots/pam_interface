#include "pam_interface/real/pamy2/configuration.hpp"

namespace pam_interface
{
Pamy2DefaultConfiguration::Pamy2DefaultConfiguration(bool simulation)
    : JsonConfiguration<4>(get_default_configuration_path(simulation))
{
}

std::string Pamy2DefaultConfiguration::get_default_configuration_path(
    bool simulation)
{
    if (simulation)
    {
        return (pam_configuration::get_path() /
                std::string(PAMY2_SIM_JSON_RELATIVE_PATH))
            .string();
    }
    else
    {
        return (pam_configuration::get_path() /
                std::string(PAMY2_REAL_JSON_RELATIVE_PATH))
            .string();
    }
}

}  // namespace pam_interface
