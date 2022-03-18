#include "pam_interface/real/pamy1/nifpga/4dofs/robot.hpp"


const std::string get_ni_bit_file_path()
{
  return ( pam_configuration::get_path() / std::string(NI_BIT_FILE_SUBDIR) ).string();
}
