#include <errno.h>
#include <unistd.h>
#include "pam_interface/real/pamy2/udp_communication.hpp"

static void perform_steps(pam_interface::UDPCommunication udp_com)
{
    std::array<float, 4> pressures{{2.0, 3.0, 2.5, 3.5}};
    std::array<pam_interface::Sign, 2> signs{
        {pam_interface::Sign::AGONIST, pam_interface::Sign::ANTAGONIST}};

    long int duration = 1e6;

    for (int dof = 0; dof < 4; dof++)
    {
        for (float pressure : pressures)
        {
            for (pam_interface::Sign sign : signs)
            {
                udp_com.update_pressure(dof, sign, pressure);
                udp_com.send();
            }
            long int start_time = pam_interface::time_now().count();
            while (pam_interface::time_now().count() - start_time < duration)
            {
                udp_com.receive();
                pam_interface::FromRobotMessage from_robot =
                    udp_com.get_received_message();
                std::cout << "(" << pam_interface::time_now().count() << ","
                          << pressure << ","
                          << from_robot.time_micro_secs_udp_send << ",";
                for (int dof = 0; dof < 4; dof++)
                {
                    std::cout
                        << from_robot.data.joints_set[dof].agonist.pressure
                        << ","
                        << from_robot.data.joints_set[dof].antagonist.pressure
                        << ","
                        << from_robot.data.joints_data[dof].pressure_agonist
                        << ","
                        << from_robot.data.joints_data[dof].pressure_antagonist;
                    if (dof < 3)
                    {
                        std::cout << ",";
                    }
                }
                std::cout << "),";
                usleep(2000);
            }
        }
    }
}

void perform(std::string ip, uint port)
{
    bool simulation = false;
    pam_interface::Pamy2DefaultConfiguration config(simulation);
    pam_interface::UDPCommunication udp_com(config, ip, port);
    perform_steps(udp_com);
}

/**
 * Send step commands to pamy2
 */
int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cout << "requires robot's IP and PORT as arguments";
        return 1;
    }

    std::string ip{argv[1]};
    int port = atoi(argv[2]);

    perform(ip, port);

    return 0;
}
