#pragma once

#include <iostream>
#include <exception>
#include <sstream>
#include "NiFpga.h"


namespace pam_interface {


  class NiFpga_exception : public std::exception {

  public :

    NiFpga_exception(std::string message, NiFpga_Status status);
    ~NiFpga_exception() throw () {}
    const char * what () const throw ();

  private:

    std::string error_message_;

  };


}
