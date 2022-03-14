#include "pam_interface/real/pamy2/configuration.hpp"

namespace pam_interface
{
Pamy2DefaultConfiguration::Pamy2DefaultConfiguration()
  : JsonConfiguration<4>(get_default_configuration_path())
{
}

std::string Pamy2DefaultConfiguration::get_default_configuration_path()
{
  std::string parent_folder =  pam_configuration::get_path();
  return parent_folder+std::string(PAMY2_JSON_RELATIVE_PATH);
}

}  // namespace pam_interface
