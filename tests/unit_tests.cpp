#include <math.h>
#include <cstdlib>
#include <set>
#include <sstream>
#include "gtest/gtest.h"

#include "pam_interface/dummy/driver.hpp"
#include "pam_interface/dummy/interface.hpp"
#include "pam_interface/real/pamy1/configuration.hpp"
#include "pam_interface/real/pamy1/driver.hpp"
#include "pam_interface/real/pamy1/interface.hpp"
#include "pam_interface/real/pamy2/configuration.hpp"
#include "pam_interface/real/pamy2/interface.hpp"
#include "pam_interface/real/pamy2/udp_communication.hpp"

using namespace pam_interface;

class PamInterfaceTests : public ::testing::Test
{
    void SetUp()
    {
    }
    void TearDown()
    {
    }
};

TEST_F(PamInterfaceTests, dummy_interface)
{
    Pamy1DefaultConfiguration<4> configuration;
    /*DummyInterface<4> interface(configuration);
    interface.set_pressure(1, Sign::AGONIST, 16000);
    interface.set_pressure(2, Sign::ANTAGONIST, 16500);
    ASSERT_EQ(interface.read_pressure(1, Sign::AGONIST), 16000);
    ASSERT_EQ(interface.read_pressure(2, Sign::ANTAGONIST), 16500);*/
}

TEST_F(PamInterfaceTests, pamy1_interface_instantiation)
{
    Pamy1DefaultConfiguration<4> configuration;
    Pamy1Interface<4> interface(configuration);
}

TEST_F(PamInterfaceTests, dummy_driver_instantiation)
{
    Pamy1DefaultConfiguration<4> configuration;
    DummyRobotDriver<4> driver(configuration);
}

TEST_F(PamInterfaceTests, dummy_robot)
{
    Pamy1DefaultConfiguration<4> configuration;

    pam_interface::DummyRobotDriver<4> robot(configuration);

    usleep(2000);
    PressureAction<8> action;
    for (int dof = 0; dof < 4; dof++)
    {
        action.set(dof, pam_interface::Sign::AGONIST, 15000);
        action.set(dof, pam_interface::Sign::ANTAGONIST, 16000);
    }

    robot.in(action);
    RobotState<4> observation = robot.out();

    for (int dof = 0; dof < 4; dof++)
    {
        int desired_ago =
            observation.get_desired(dof, pam_interface::Sign::AGONIST);
        int desired_antago =
            observation.get_desired(dof, pam_interface::Sign::ANTAGONIST);
        ASSERT_EQ(desired_ago, 15000);
        ASSERT_EQ(desired_antago, 16000);
    }
}

TEST_F(PamInterfaceTests, rotate)
{
    double pi = static_cast<double>(M_PI);

    double precision = 1e-6;

    double angle = rotate(0, pi / 2.);
    ASSERT_NEAR(angle, pi / 2., precision);

    angle = rotate(pi / 2., pi / 2.);
    ASSERT_NEAR(angle, pi, precision);

    angle = rotate(0, 3 * pi / 2.);
    ASSERT_NEAR(angle, -pi / 2., precision);

    angle = rotate(pi / 8.0, pi / 8.0);
    ASSERT_NEAR(angle, pi / 4., precision);

    angle = rotate(pi / 8.0, pi / 8.0);
    ASSERT_NEAR(angle, pi / 4., precision);

    angle = rotate(pi / 8.0, -2 * pi / 8.0);
    ASSERT_NEAR(angle, -pi / 8., precision);
}
