#pragma once

#include "pam_interface/configuration.hpp"
#include "pam_interface/driver.hpp"
#include "pam_interface/real/pamy2/interface.hpp"

namespace pam_interface
{
/**
 * @brief Pamy2Driver child class.
 *
 * Encapsulates an instance of Pamy2Interface
 * and provide the concrete implementations of the
 * in and out methods of the Driver interface.
 */
class Pamy2Driver : public Driver<NB_DOFS>
{
public:
    /**
     * Constructs a new Pamy2Driver object.
     *
     * @param configuration Only the minimal and maximal
     * pressure values will be used
     * @param ip IP of the Pamy 2 robot
     * @param port UDP port of the Pamy 2 robot
     */
    Pamy2Driver(Configuration<NB_DOFS>& configuration,
                std::string ip,
                uint port);
};

}  // namespace pam_interface
