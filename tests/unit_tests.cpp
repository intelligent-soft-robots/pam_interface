#include "gtest/gtest.h"
#include <cstdlib>
#include <unistd.h>
#include <sstream>
#include <set>

#include "pam_interface/configuration.hpp"
#include "pam_interface/real/interface.hpp"
#include "pam_interface/real/driver.hpp"
#include "pam_interface/dummy/interface.hpp"
#include "pam_interface/dummy/driver.hpp"
#include "pam_interface/factory.hpp"


using namespace pam_interface;

class PamInterfaceTests : public ::testing::Test
{
  void SetUp(){}
  void TearDown(){}
};


TEST_F(PamInterfaceTests,dummy_interface)
{
  DefaultConfiguration<4> configuration(1);
  DummyInterface<4> interface(configuration);
  interface.set_pressure(1,Sign::AGONIST,16000);
  interface.set_pressure(2,Sign::ANTAGONIST,16500);
  ASSERT_EQ(interface.read_pressure(1,Sign::AGONIST),16000);
  ASSERT_EQ(interface.read_pressure(2,Sign::ANTAGONIST),16500);
}

TEST_F(PamInterfaceTests,real_interface_instantiation)
{
  DefaultConfiguration<4> configuration;
  RealRobotInterface<4> interface(1,configuration);
}

TEST_F(PamInterfaceTests,real_driver_instantiation)
{
  DefaultConfiguration<4> configuration;
  RealRobotDriver<4> driver(1,configuration);
}

TEST_F(PamInterfaceTests,dummy_driver_instantiation)
{
  DefaultConfiguration<4> configuration;
  DummyRobotDriver<4> driver(1,configuration);
  driver.initialize();
  driver.shutdown();
}

TEST_F(PamInterfaceTests,dummy_robot)
{

  int robot_id=1;
  DefaultConfiguration<4> configuration;
  
  auto robot_ptr = Factory<4>::get_dummy(robot_id,
					 configuration);
  
  usleep(2000);
  PressureAction<8> action;
  for(int dof=0;dof<4;dof++)
    {
      action.set(dof,Sign::Agonist,15000);
      action.set(dof,Sign::Antagonist,16000);
    }

  robot_interfaces::TimeIndex index = robot_ptr->append_desired_action(action);
  RobotState<4> observation = robot_ptr->get_observation(index+1);
  
  int id = observation.get_id();
  int control_iteration = observation.get_control_iteration();
  for(int dof=0;i<dof;i++)
    {
      int desired_ago = observation.get_desired(dof,Sign::AGONIST);
      int desired_antago = observation.get_desired(dof,Sign::ANTAGONIST);
      ASSERT_EQ(desired_ago,15000);
      ASSERT_EQ(desired_antago,16000);
    }
  
}


