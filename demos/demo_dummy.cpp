#include "pam_interface/dummy/driver.hpp"
#include "pam_interface/sign.hpp"

void run()
{

  int robot_id = 1;
  
  // configuration for this robot instance
  pam_interface::DefaultConfiguration<4> configuration;
  
  pam_interface::DummyRobotDriver<4> robot(configuration);
  
  // PressureAction is of size 2*dofs, because 2 muscles per dof
  pam_interface::PressureAction<8> action;

  for(uint i=0;i<10;i++)
    {

      std::cout << " ----- " << i << " ----- " << std::endl;
      
      // this action set pressures of all agonists to 15000 and
      // pressure of all antagonists to 16000
      for(int dof=0;dof<4;dof++)
	{
	  action.set(dof,pam_interface::Sign::AGONIST,15000+i*10);
	  action.set(dof,pam_interface::Sign::ANTAGONIST,16000+i*10);
	}

      // applying the action
      robot.in(action);

      // getting the corresponding observation
      pam_interface::RobotState<4> observation = robot.out();

      // checking the desired pressures have been changed as expected
      observation.print();

      usleep(50000);
      
    }

}


int main()
{
  run();
}
