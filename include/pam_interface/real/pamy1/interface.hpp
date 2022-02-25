// Copyright 2019 Max Planck Gesellschaft
// Author: Vincent Berenz

#pragma once

#include <stdlib.h>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "pam_interface/interface.hpp"
#include "pam_interface/real/pamy1/nifpga/factory.hpp"

namespace pam_interface
{
template <int NB_DOFS>
class Pamy1Interface : public Interface<NB_DOFS>
{
public:
    Pamy1Interface(const Configuration<NB_DOFS> &configuration);
    ~Pamy1Interface();
    void check_status(std::string message, NiFpga_Status status);
    void init();
    Microseconds time_diff(int delta_sensor_iteration);
    double encoder_to_angle(int dof, int encoder);
    void terminate();
    int read_pressure(int dof, Sign sign);
    int read_encoder(int dof);
    int read_sensor_iteration();
    int read_control_iteration();
    bool is_reference_found(int dof);
    void set_pressure(int dof, Sign sign, int value);
    void read_control_loop(int dof, Sign sign, NiFpga_Bool &on_or_off);
    void read_control_loop(int dof, Sign sign, int &on_or_off);
    void set_control_loop(NiFpga_Bool on_or_off, int dof, Sign sign);
    void set_control_loop(int on_or_off, int dof, Sign sign);
    void set_control_loops(int on_or_off);
    void set_control_loops(NiFpga_Bool on_or_off);

private:
    NiFpgaRobot *nifpga_robot_;
    Configuration<NB_DOFS> configuration_;
    bool exception_thrown_;
    bool terminated_;
    bool initialized_;

    // time this instance was created
    std::chrono::high_resolution_clock::time_point start_time_;
    // time control iteration was counted up previously
    std::chrono::high_resolution_clock::time_point previous_time_;
    // just now
    std::chrono::high_resolution_clock::time_point time_now_;
};

#include "interface.hxx"

}  // namespace pam_interface
