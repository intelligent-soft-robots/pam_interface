#include "pam_interface/real/pamy2/configuration.hpp"

namespace pam_interface
{
Pamy2DefaultConfiguration::Pamy2DefaultConfiguration()
    : JsonConfiguration<4>(PAMY2_DEFAULT_CONFIG_FILE_PATH)
{
}

std::string Pamy2DefaultConfiguration::get_default_configuration_path()
{
    return std::string(PAMY2_DEFAULT_CONFIG_FILE_PATH);
}

}  // namespace pam_interface
