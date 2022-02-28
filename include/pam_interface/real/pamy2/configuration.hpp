#pragma once

#include "pam_interface/configuration.hpp"

namespace pam_interface
{
class Pamy2DefaultConfiguration : public JsonConfiguration<4>
{
public:
    Pamy2DefaultConfiguration();
    static std::string get_default_configuration_path();
};

}  // namespace pam_interface
