// Copyright 2019 Max Planck Gesellschaft
// Author: Vincent Berenz

#pragma once

#include <memory>
#include "pam_interface/real/pamy1/interface.hpp"

namespace pam_interface
{
namespace four_dofs
{
// to replace with a std::map<int,ptr> (ID->Interface<4>)
// once we have several 4dofs robots
static std::shared_ptr<Interface<4>> interface_4dofs_g;

/**
 * Returns a pointer to a hardware interface
 * to a dummy 4 DoF robot.
 *
 * @tparam NB_DOFS Number of degrees of freedom
 * @param configuration Pamy1Configuration object
 * @return std::shared_ptr<Interface<NB_DOFS>> Smart pointer
 * to interface
 */
template <int NB_DOFS>
std::shared_ptr<Interface<NB_DOFS>> get_interface(
    const Configuration<NB_DOFS>& configuration);

#include "factory.hxx"

}  // namespace four_dofs

}  // namespace pam_interface
