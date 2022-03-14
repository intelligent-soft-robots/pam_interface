#include "pam_configuration/pam_configuration.hpp"
#include "pam_interface/real/pamy1/nifpga/robot.hpp"

namespace pam_interface
{
// code common to all robots ------------------------------------------

NiFpgaRobot::NiFpgaRobot()
{
}

NiFpgaRobot::~NiFpgaRobot()
{
    delete[] this->joints;
}

void NiFpgaRobot::set_nb_dofs(int nb_dofs)
{
    this->nb_dofs = nb_dofs;
    this->joints = new NiFpga_joint[nb_dofs];
}

}  // namespace pam_interface
