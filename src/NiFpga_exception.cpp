#include "pam_interface/nifpga/NiFpga_exception.hpp"

namespace pam_interface
{
NiFpga_exception::NiFpga_exception(std::string message, NiFpga_Status status)
{
    std::ostringstream s;
    s << "Ni Fpga error (" << status << "): " << message;
    this->error_message_ = s.str();
}

const char* NiFpga_exception::what() const throw()
{
    return this->error_message_.c_str();
}

}  // namespace pam_interface
