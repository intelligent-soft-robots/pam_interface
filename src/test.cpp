
#include "robot_interfaces/robot_backend.hpp"

using namespace robot_interfaces;

class Action
{
};
class Observation
{
};

typedef RobotDriver<Action, Observation> Driver;
typedef std::shared_ptr<Driver> DriverPtr;

typedef RobotData<Action, Observation, RobotBackend::Status> Data;
typedef std::shared_ptr<Data> DataPtr;

int main()
{
    DriverPtr driver(new Driver);
    DataPtr data(new Data);

    RobotBackend backend(driver, data, 1, 1);
}
