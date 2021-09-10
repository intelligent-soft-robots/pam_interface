#include "pam_interface/nifpga/4dofs/robot.hpp"
#include "pam_interface/nifpga/factory.hpp"
#include "pam_interface/nifpga/robot.hpp"

namespace pam_interface
{
namespace four_dofs
{
int get_nb_dofs()
{
    return 4;
}

static void construct_robot(NiFpgaRobot &robot)
{
    robot.control_period = CONTROL_PERIOD;
    robot.sensor_period = SENSOR_PERIOD;

    robot.attribute = ATTRIBUTE;
    robot.signature = SIGNATURE;
    robot.ni_bit_file = NI_BIT_FILE;
    robot.ni_resource = NI_RESOURCE;

    robot.iteration_sensor = ITERATION_SENSOR;
    robot.iteration_control = ITERATION_CONTROL;

    for (int dof = 0; dof < robot.nb_dofs; dof++)
    {
        robot.joints[dof].reference_found = REFERENCE_FOUNDS[dof];
        robot.joints[dof].encoder = ENCODERS[dof];
        robot.joints[dof].encoder_multiplier = ENCODER_MULTIPLIERS[dof];
        robot.joints[dof].encoder_bias = ENCODER_BIAS[dof];
        robot.joints[dof].encoder_inverse = ENCODER_INVERSE[dof];
        robot.joints[dof].encoder_negative = ENCODER_NEGATIVE[dof];
    }

    int stand_pressure_index = 0;
    for (int dof = 0; dof < robot.nb_dofs; dof++)
    {
        robot.joints[dof].stand_pressure[0] =
            STAND_PRESSURES[stand_pressure_index];
        stand_pressure_index++;
        robot.joints[dof].stand_pressure[1] =
            STAND_PRESSURES[stand_pressure_index];
        stand_pressure_index++;
    }

    for (int sign = 0; sign < 2; sign++)
    {
        int *sign_indexes = new int[robot.nb_dofs];

        if (sign == 0)
        {
            for (int i = 0; i < 4; i++)
            {
                sign_indexes[i] = PLUS_INDEXES[i];
            }
        }
        else
        {
            for (int i = 0; i < 4; i++)
            {
                sign_indexes[i] = MINUS_INDEXES[i];
            }
        }

        for (int dof = 0; dof < robot.nb_dofs; dof++)
        {
            int memory_index = sign_indexes[dof];

            robot.joints[dof].controls[sign] = CONTROLS[memory_index];
            robot.joints[dof].min_pressures[sign] = MIN_PRESSURES[memory_index];
            robot.joints[dof].max_pressures[sign] = MAX_PRESSURES[memory_index];
            robot.joints[dof].set_pressures[sign] = SET_PRESSURES[memory_index];
            robot.joints[dof].current_pressures[sign] =
                CURRENT_PRESSURES[memory_index];
        }

        delete[] sign_indexes;
    }
}

NiFpgaRobot *get_fpga_robot()
{
    _ROBOT.set_nb_dofs(get_nb_dofs());
    construct_robot(_ROBOT);
    return &_ROBOT;
}

}  // namespace four_dofs

}  // namespace pam_interface
