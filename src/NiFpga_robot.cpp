#include "pam_interface/nifpga/robot.hpp"

// note : BITFILE_4DOFS_FILE_PATH replaced by absolute path to the file in CMakeLists.txt
const std::string NI_BIT_FILE(BITFILE_4DOFS_FILE_PATH);


namespace pam_interface {

  // code common to all robots ------------------------------------------


  NiFpgaRobot::NiFpgaRobot(){}


  NiFpgaRobot::~NiFpgaRobot(){
      
    delete[] this->joints;
 
  }

  void NiFpgaRobot::set_nb_dofs(int nb_dofs){

    this->nb_dofs = nb_dofs;
    this->joints = new NiFpga_joint[nb_dofs];

  }
  
}
