#pragma once

#include <exception>
#include <iostream>
#include <sstream>
#include "NiFpga.h"

namespace pam_interface
{
/**
 * @brief Ni FPGA exception class extending standard exceptions.
 *
 * Defines FPGA specific exception handling and error message
 * e.g. if FPGA status does not correspond to desired state.
 */
class NiFpga_exception : public std::exception
{
public:
    /**
     * Constructs a new NiFpga_exception object
     *
     * @param message Error message if FPGA status does not fit
     * expected status
     * @param status Desired status
     */
    NiFpga_exception(std::string message, NiFpga_Status status);
    ~NiFpga_exception() throw()
    {
    }
    const char* what() const throw();

private:
    std::string error_message_;
};

}  // namespace pam_interface
