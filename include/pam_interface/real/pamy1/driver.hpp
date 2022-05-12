#pragma once

#include "pam_interface/configuration.hpp"
#include "pam_interface/driver.hpp"
#include "pam_interface/real/pamy1/factory.hpp"

namespace pam_interface
{
/**
 * @brief Pamy1Driver child class.
 *
 * Encapsulates an instance of Pamy1Interface
 * and provide the concrete implementations of the
 * in and out methods of the driver interface.
 *
 * @tparam NB_DOFS Number of degrees of freedom
 */
template <int NB_DOFS>
class Pamy1Driver : public Driver<NB_DOFS>
{
public:
    /**
     * Constructor of Pamy1Driver.
     *
     * @param config Pamy1Configuration object
     */
    Pamy1Driver(const Configuration<NB_DOFS>& config);
};

#include "driver.hxx"

}  // namespace pam_interface
