#include "pam_interface/factory.hpp"
#include "pam_interface/sign.hpp"

void run()
{

  int robot_id = 1;
  
  // configuration for this robot instance
  pam_interface::DefaultConfiguration<4> configuration;
  
  // robot_ptr is an instance of a pointer to robot interface frontend,
  // see: https://github.com/open-dynamic-robot-initiative/robot_interfaces/
  //            blob/master/include/robot_interfaces/robot_frontend.hpp

  auto robot_ptr = pam_interface::Factory<4>::create_dummy(robot_id,
							   configuration);
  usleep(2000);

  // PressureAction is of size 2*dofs, because 2 muscles per dof
  pam_interface::PressureAction<8> action;
  // this action set pressures of all agonists to 15000 and
  // pressure of all antagonists to 16000
  for(int dof=0;dof<4;dof++)
    {
      action.set(dof,pam_interface::Sign::AGONIST,15000);
      action.set(dof,pam_interface::Sign::ANTAGONIST,16000);
    }

  // applying the action
  robot_interfaces::TimeIndex index = robot_ptr->append_desired_action(action);

  // getting the corresponding observation
  pam_interface::RobotState<4> observation = robot_ptr->get_observation(index+1);

  // checking the desired pressures have been changed as expected
  observation.print();

}


int main()
{
  run();
}
