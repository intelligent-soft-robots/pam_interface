#ifndef MR_INTERFACE_HPP
#define MR_INTERFACE_HPP

#include "pam_interface/configuration.hpp"
#include "pam_interface/sign.hpp"
#include "pam_interface/state/robot.hpp"

#include <stdlib.h>
#include <chrono>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#define UNUSED(x) (void)(x)

namespace pam_interface
{
int clip(int min, int max, int v);

template <int NB_DOFS>
class Interface
{
public:
    Interface();
    virtual RobotState<NB_DOFS> get_state();
    virtual void set_pressure(int dof, Sign sign, int value) = 0;
    virtual void init()
    {
    }
    virtual void terminate()
    {
    }
    virtual void finalize_iteration()
    {
    }

protected:
    virtual double encoder_to_angle(int dof, int encoder)
    {
        UNUSED(dof);
        UNUSED(encoder);
        return 0.;
    }
    virtual int read_pressure(int dof, Sign sign)
    {
        UNUSED(dof);
        UNUSED(sign);
        return 0;
    }
    virtual int read_encoder(int dof)
    {
        UNUSED(dof);
        return 0;
    }
    virtual int read_sensor_iteration()
    {
        return 0;
    }
    virtual int read_control_iteration()
    {
        return 0;
    }
    virtual bool is_reference_found(int dof)
    {
        UNUSED(dof);
        return true;
    }

protected:
    RobotState<NB_DOFS> previous_state_;
    std::array<int, NB_DOFS> desired_agonists_;
    std::array<int, NB_DOFS> desired_antagonists_;
};

#include "interface.hxx"

}  // namespace pam_interface

#endif
