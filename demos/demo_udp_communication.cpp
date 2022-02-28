#include <unistd.h>
#include "pam_interface/real/pamy2/udp_communication.hpp"

#define IP "192.168.0.110"
#define PORT 4700

void perform(std::string ip, int port)
{
    std::shared_ptr<pam_interface::Configuration> config =
        std::make_shared<pam_interface::DefaultConfiguration<4>>();
    pam_interface::UDPCommunication udp_com
    {
        config, ip, port
    }

    int pressures[4]{1.0, 1.5, 2.0, 2.5};

    for (int index = 0; index < 4; index++)
    {
        for (int dof = 0; dof < 4; dof++)
        {
            udp_com.send(dof, pam_interface.Sign::AGONIST, pressures[index]);
            udp_com.send(dof, pam_interface.Sign::ANTAGONIST, pressures[index]);
        }
        usleep(1000000);
        pam_interface::RobotState state = udp_com.receive();
        state.print();
    }
}

void main()
{
    perform(IP, PORT);
}
