#include "pam_interface/real/pamy2/udp_communication.hpp"

int c_init_socket(c_socket* socket_,
                  const char* ip,
                  uint port,
                  int recv_buffer_size)
{
    socket_->descriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    socket_->rcv_buffer_size = recv_buffer_size;
    // set the socket recv buffer to minimum size
    // note: if recv_buffer_size < minimum size (likely to be the case),
    //       then the buffer will not be set to recv_buffer_size but to this
    //       minimal size.
    setsockopt(socket_->descriptor,
               SOL_SOCKET,
               SO_RCVBUF,
               &(socket_->rcv_buffer_size),
               sizeof(socket_->rcv_buffer_size));
    // set the socket non blocking
    fcntl(socket_->descriptor,
          F_SETFL,
          fcntl(socket_->descriptor, F_GETFL) | O_NONBLOCK);
    memset(&(socket_->addr), 0, sizeof(socket_->size));
    socket_->addr.sin_family = AF_INET;
    socket_->addr.sin_port = htons(port);
    inet_aton(ip, &(socket_->addr.sin_addr));
    return socket_->descriptor;
}

ssize_t c_send(c_socket* socket_, void* message, int message_size)
{
    return sendto(socket_->descriptor,
                  message,
                  message_size,
                  0,
                  (struct sockaddr*)&(socket_->addr),
                  socket_->size);
}

ssize_t c_receive(c_socket* socket_, void* message, int message_size)
{
    return recvfrom(socket_->descriptor,
                    message,
                    message_size,
                    0,
                    (struct sockaddr*)&(socket_->addr),
                    &(socket_->size));
}

namespace pam_interface
{

static void init_to_robot_message(ToRobotMessage& message)
{
    message.counter = 0;
    message.connection = 0;
    message.control = 0;
    message.reserve = 0;
    message.timestamp_client = 0;
    for (unsigned int dof = 0; dof < 4; dof++)
    {
        message.controls[dof].angle = 0;
        message.controls[dof].valve_ago = 0;
        message.controls[dof].pressure_agonist = 0;
        message.controls[dof].valve_antagonist = 0;
        message.controls[dof].pressure_antagonist = 0;
    }
}

UDPCommunication::UDPCommunication(Configuration<NB_DOFS>& configuration,
                                   std::string ip,
                                   uint port)
{
    // creating the socket for communicating with the robot
    int desc = c_init_socket(&socket_, ip.c_str(), port, sizeof(from_robot_));
    if (desc == 1)
    {
        std::ostringstream s;
        s << "failed to create socket for udp communication (" << ip << ", "
          << port << "): " << strerror(errno) << std::endl;
        std::string error_message(s.str());
        throw std::runtime_error(error_message);
    }

    // to_robot_ is the structure that will be used to generate the telegrams
    // sent to the robot. Making sure it has suitable default values
    init_to_robot_message(to_robot_);
    to_robot_.connection =
        1;                  // other values would request the robot to shutdown
    to_robot_.control = 1;  // i.e. pressure control

    // sending udp telegram requesting minimal pressures
    // on all muscles
    for (unsigned short dof = 0; dof < NB_DOFS; dof++)
    {
      int imin_ago = configuration.min_pressure(dof, Sign::AGONIST);
      int imin_antago = configuration.min_pressure(dof, Sign::ANTAGONIST);
      float min_pressure_ago = int_to_bar(imin_ago);
      float min_pressure_antago = int_to_bar(imin_antago);
      to_robot_.controls[dof].pressure_agonist = min_pressure_ago;
      to_robot_.controls[dof].pressure_antagonist = min_pressure_antago;
      update_pressure(dof, Sign::AGONIST, min_pressure_ago);
      update_pressure(dof, Sign::ANTAGONIST, min_pressure_antago);
      send();
    }
}

void UDPCommunication::send()
{
    // sending a UDP telegram to the robot
    to_robot_.counter += 1;
    to_robot_.timestamp_client = time_now().count();
    ssize_t r = c_send(&socket_, &to_robot_, sizeof(to_robot_));
    if (r < 0)
    {
        std::ostringstream s;
        s << "failed to send udp package " << strerror(errno) << std::endl;
        std::string error_message(s.str());
        throw std::runtime_error(error_message);
    }
}

void UDPCommunication::update_pressure(unsigned short dof,
                                       Sign sign,
                                       float desired_pressure)
{
    if (dof == 3)
    {
        // because muscles are inverted for dof 3
        sign = switch_sign(sign);
    }
    // just update the to_robot_ structure, does not send
    // any telegram
    if (sign == Sign::AGONIST)
    {
        to_robot_.controls[dof].pressure_agonist = desired_pressure;
    }
    else
    {
        to_robot_.controls[dof].pressure_antagonist = desired_pressure;
    }
}

RobotState<NB_DOFS> UDPCommunication::receive()
{
    ssize_t r = -1;
    // We want the latest received UDP package, so we "receive" across
    // the full queue until we get to an EAGAIN error, which means that
    // to get a new value, the socket would need to wait (and the socket was set
    // as non blocking, see the method c_init_socket in this file). When hitting
    // this error, we know we reached the end of the queue, i.e. the newest data
    while (r == -1)
    {
        r = c_receive(&socket_, &from_robot_, sizeof(from_robot_));
        if (r < 0 && errno != EAGAIN)
        {
            std::ostringstream s;
            s << "failed to receive udp package: " << errno << " ("
              << strerror(errno) << ")" << std::endl;
            std::string error_message(s.str());
            throw std::runtime_error(error_message);
        }
    }
    // initializing the robot state to return
    RobotState<NB_DOFS> state{
        static_cast<int>(from_robot_.data.time_micro_secs_actuator_data),
        static_cast<int>(from_robot_.data.time_micro_secs_sensor_data),
        TimePoint(from_robot_.time_micro_secs_udp_send)};

    // will be used to perform some corrective transform on the received
    // angles
    constexpr double PI = 3.141592653589793238463;
    constexpr double TO_RADIAN = +PI / 180.;
    std::array<double, 4> signs{{-1, -1, -1, +1}};
    std::array<double, 4> rotations{{-5.37 * TO_RADIAN,
                                     2.5 * TO_RADIAN,
                                     -0.75 * TO_RADIAN,
                                     -PI / 4. + 0.5 * TO_RADIAN}};

    for (int dof = 0; dof < NB_DOFS; dof++)
    {
        double angle = from_robot_.data.joints_data[dof].angle * TO_RADIAN;
        angle = rotate(angle, rotations[dof]);
        angle = angle * signs[dof];
        double speed = from_robot_.data.joints_data[dof].speed * TO_RADIAN;
        speed = speed * signs[dof];
        // the observed pressure (i.e. as read by the robot sensors)
        int observed_pressure_ago =
            bar_to_int(from_robot_.data.joints_data[dof].pressure_agonist);
        int observed_pressure_antago =
            bar_to_int(from_robot_.data.joints_data[dof].pressure_antagonist);
        // the desired pressure (i.e. that the robot controller is trying to
        // converge to)
        int desired_pressure_ago =
	  bar_to_int(from_robot_.data.joints_set[dof].agonist.pressure);
        int desired_pressure_antago =
	  bar_to_int(from_robot_.data.joints_set[dof].antagonist.pressure);
        if (dof == 3)
        {
            // for 3rd dof, the muscles are inverted
            std::swap(observed_pressure_ago, observed_pressure_antago);
            std::swap(desired_pressure_ago, desired_pressure_antago);
        }
	state.set_joint(
            dof,
            observed_pressure_ago,
            observed_pressure_antago,
            desired_pressure_ago,
            desired_pressure_antago,
            angle,
            speed,
            static_cast<int>(from_robot_.data.joints_data[dof].encoder_value),
            true);
    }
    return state;
}

const FromRobotMessage& UDPCommunication::get_received_message() const
{
    return from_robot_;
}

int UDPCommunication::bar_to_int(float v) const
{
  return static_cast<int>( (v-INT_TO_BAR_BIAS) / INT_TO_BAR_MULTIPLYER );
}

float UDPCommunication::int_to_bar(int v) const
{
  return INT_TO_BAR_MULTIPLYER * static_cast<double>(v) + INT_TO_BAR_BIAS;
}

void print_to_robot_message(const ToRobotMessage& message)
{
    std::cout << "To robot message: " << std::endl;
    for (int dof = 0; dof < 4; dof++)
    {
        std::cout << "dof: " << dof << std::endl
                  << "\tpressure agonist: "
                  << message.controls[dof].pressure_agonist << std::endl
                  << "\tpressure antagonist: "
                  << message.controls[dof].pressure_antagonist << std::endl;
    }
    std::cout << std::endl;
}

void print_robot_message(const FromRobotMessage& message)
{
    std::cout << "robot message:" << std::endl
              << "control task: " << message.index_control_task << std::endl
              << "index_set_points_cycle: " << message.index_set_points_cycle
              << std::endl
              << "index_udp_telegram: " << message.index_set_points_cycle
              << std::endl
              << "not_close_srv: " << message.not_close_srv << std::endl
              << "time_micro_secs_udp_send: "
              << message.time_micro_secs_udp_send << std::endl
              << "time_micro_secs_last_udp_receive: "
              << message.time_micro_secs_last_udp_receive << std::endl
              << "data: " << std::endl
              << "\ttime_micro_secs_sensor_data: "
              << message.data.time_micro_secs_sensor_data << std::endl
              << "\ttime_micro_secs_actuator_data: "
              << message.data.time_micro_secs_actuator_data << std::endl
              << "\ttime_micro_secs_set_points: "
              << message.data.time_micro_secs_set_points << std::endl
              << "\toperation: " << message.data.operation << std::endl
              << "\tcontrol: " << message.data.control << std::endl
              << "\tpressure_mode: " << message.data.pressure_mode << std::endl
              << "\tb_quick_stop_pushed: " << message.data.b_quick_stop_pushed
              << std::endl
              << "\t\tjoint_set: " << std::endl;
    for (int dof = 0; dof < 4; dof++)
    {
        std::cout << "\t\tdof: " << dof << std::endl;
        std::cout << "\t\t\tangle: " << message.data.joints_data[dof].angle
                  << std::endl
                  << "\t\t\tspeed: " << message.data.joints_data[dof].speed
                  << std::endl
                  << "\t\t\tencoder: "
                  << message.data.joints_data[dof].encoder_value << std::endl
                  << "\t\t\tagonist: " << std::endl
                  << "\t\t\t\tvalve: "
                  << message.data.joints_data[dof].valve_agonist << std::endl
                  << "\t\t\t\tpressure: "
                  << message.data.joints_data[dof].pressure_agonist << std::endl
                  << "\t\t\tantagonist: " << std::endl
                  << "\t\t\t\tvalve: "
                  << message.data.joints_data[dof].valve_antagonist << std::endl
                  << "\t\t\t\tpressure: "
                  << message.data.joints_data[dof].pressure_antagonist
                  << std::endl;
    }
    std::cout << std::endl;
}
}  // namespace pam_interface
