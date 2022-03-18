#include "pam_interface/real/pamy2/configuration.hpp"

namespace pam_interface
{
Pamy2DefaultConfiguration::Pamy2DefaultConfiguration()
  : JsonConfiguration<4>(get_default_configuration_path())
{
}

std::string Pamy2DefaultConfiguration::get_default_configuration_path()
{
  return ( pam_configuration::get_path() / std::string(PAMY2_JSON_RELATIVE_PATH) ).string();
}

}  // namespace pam_interface
