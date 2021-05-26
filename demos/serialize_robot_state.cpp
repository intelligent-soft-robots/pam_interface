
#include "pam_interface/state/robot.hpp"
#include "shared_memory/shared_memory.hpp"

void run()
{
    pam_interface::RobotState<4> robot_state(
        1, 1, pam_interface::TimePoint(1000));
    for (std::size_t dof = 0; dof < 4; dof++)
    {
        robot_state.set_joint(dof, 100, 200, 101, 201, 1.6, 2.1, 0, true);
    }

    shared_memory::clear_shared_memory("A");
    shared_memory::serialize("A", "A", robot_state);

    pam_interface::RobotState<4> robot_state_out;

    shared_memory::deserialize("A", "A", robot_state_out);

    std::cout << "\n" << robot_state_out.get_position(0) << "\n";
    std::cout << "\n" << robot_state_out.get_velocity(0) << "\n";
}

int main()
{
    run();
}
