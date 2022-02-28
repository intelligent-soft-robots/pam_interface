#include "pam_interface/real/pamy2/driver.hpp"

namespace pam_interface
{
Pamy2Driver::Pamy2Driver(Configuration<NB_DOFS>& config,
                         std::string ip,
                         uint port)
    : Driver<NB_DOFS>(config)
{
    this->hw_interface_ = std::make_shared<Pamy2Interface>(config, ip, port);
}

}  // namespace pam_interface
