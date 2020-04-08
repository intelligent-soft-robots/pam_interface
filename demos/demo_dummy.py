import pam_interface


def run():

    robot_id = 1

    configuration = pam_interface.DefaultConfiguration()

    # robot is an instance of robot_interfaces::robot_frontend
    # see :
    # https://github.com/open-dynamic-robot-initiative/robot_interfaces/blob/master/include/robot_interfaces/robot_frontend.hpp
    robot = pam_interface.Factory.create_dummy(robot_id,configuration)

    action = pam_interface.PressureAction()
    for dof in range(4):
        action.set(dof,pam_interface.sign.agonist,15000)
        action.set(dof,pam_interface.sign.antagonist,16000)

    index = robot.append_desired_action(action)
    observation = robot.get_observation(index+1)

    observation.display()


if __name__ == "__main__":

    run()
