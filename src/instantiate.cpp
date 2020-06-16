#include "pam_interface/dummy_interface.hpp"
#include "pam_interface/driver.hpp"
#include "pam_interface/data.hpp"

using namespace pam_interface;

#define NB_DOFS 5

typedef DummyInterface<NB_DOFS> PamInterface;
typedef std::shared_ptr<PamInterface> PamInterfacePtr;

// 2*NB_DOFS because 2 muscles per DOF
typedef Driver<2*NB_DOFS> RobotDriver;
typedef std::shared_ptr<RobotDriver> RobotDriverPtr;

typedef Data<2*NB_DOFS> RobotData;
typedef std::shared_ptr<RobotData> RobotDataPtr;

typedef robot_interfaces::RobotBackend< PressureAction<2*NB_DOFS>,
					PamRobotState<NB_DOFS> > RobotBackend;

typedef robot_interfaces::RobotFrontend< PressureAction<2*NB_DOFS>,
					 PamRobotState<NB_DOFS> > RobotFrontend;

int main()
{

  Microseconds control_period(200);
  Microseconds sensor_period(200);
  std::array<int,NB_DOFS> min_pressures;
  std::array<int,NB_DOFS> max_pressures;

  PamInterfacePtr pam_interface( new PamInterface ( control_period,
						    sensor_period,
						    min_pressures,
						    max_pressures,
						    min_pressures,
						    max_pressures) );

  RobotDriverPtr driver ( new RobotDriver(pam_interface) );
  RobotDataPtr data ( new RobotData );

  RobotBackend backend( driver,
			data,
			1.0,
			1.0 );

  RobotFrontend frontend(data);

  
}

