

namespace internal
{
int next_id()
{
    static int id = 0;
    id++;
    return id;
}
}  // namespace internal

template <int NB_DOFS>
RobotState<NB_DOFS>::RobotState(int control_iteration,
                                int sensor_iteration,
                                TimePoint time_stamp)
    : control_iteration_(control_iteration),
      sensor_iteration_(sensor_iteration),
      time_stamp_(time_stamp.count())
{
    id_ = internal::next_id();
}

template <int NB_DOFS>
RobotState<NB_DOFS>::RobotState()
{
    id_ = internal::next_id();
}

template <int NB_DOFS>
RobotState<NB_DOFS>::RobotState(int id) : id_(id)
{
}

template <int NB_DOFS>
RobotState<NB_DOFS>::~RobotState()
{
}

template <int NB_DOFS>
void RobotState<NB_DOFS>::set_joint(int dof,
                                    int agonist,
                                    int antagonist,
                                    int desired_agonist,
                                    int desired_antagonist,
                                    double position,
                                    double velocity,
                                    int encoder,
                                    bool reference_found)
{
    joints_[dof].agonist = agonist;
    joints_[dof].antagonist = antagonist;
    joints_[dof].desired_agonist = desired_agonist;
    joints_[dof].desired_antagonist = desired_antagonist;
    joints_[dof].position = position;
    joints_[dof].velocity = velocity;
    joints_[dof].encoder = encoder;
    joints_[dof].reference_found = reference_found;
}

template <int NB_DOFS>
int RobotState<NB_DOFS>::get_id() const
{
    return id_;
}

template <int NB_DOFS>
int RobotState<NB_DOFS>::get_desired(int dof, Sign sign) const
{
    if (sign == Sign::AGONIST)
    {
        return joints_[dof].desired_agonist;
    }
    else
    {
        return joints_[dof].desired_antagonist;
    }
}

template <int NB_DOFS>
int RobotState<NB_DOFS>::get(int dof, Sign sign) const
{
    if (sign == Sign::AGONIST)
    {
        return joints_[dof].agonist;
    }
    else
    {
        return joints_[dof].antagonist;
    }
}

template <int NB_DOFS>
bool RobotState<NB_DOFS>::get_reference_found(int dof) const
{
    return joints_[dof].reference_found;
}

template <int NB_DOFS>
int RobotState<NB_DOFS>::get_encoder(int dof) const
{
    return joints_[dof].encoder;
}

template <int NB_DOFS>
double RobotState<NB_DOFS>::get_position(int dof) const
{
    return joints_[dof].position;
}

template <int NB_DOFS>
double RobotState<NB_DOFS>::get_velocity(int dof) const
{
    return joints_[dof].velocity;
}

template <int NB_DOFS>
long int RobotState<NB_DOFS>::get_time_stamp() const
{
    return time_stamp_;
}

template <int NB_DOFS>
int RobotState<NB_DOFS>::get_control_iteration() const
{
    return control_iteration_;
}

template <int NB_DOFS>
int RobotState<NB_DOFS>::get_sensor_iteration() const
{
    return sensor_iteration_;
}

template <int NB_DOFS>
const JointState& RobotState<NB_DOFS>::get_joint_state(int dof) const
{
    return joints_[dof];
}

template <int NB_DOFS>
void RobotState<NB_DOFS>::print() const
{
    std::cout << "state id: " << id_ << "\t"
              << "iteration: " << control_iteration_ << std::endl;
    for (int i = 0; i < NB_DOFS; i++)
    {
        int encoder = get_encoder(i);
        bool reference_found = get_reference_found(i);
        double position = get_position(i);
        int current_ago = get(i, Sign::AGONIST);
        int current_antago = get(i, Sign::ANTAGONIST);
        int desired_ago = get_desired(i, Sign::AGONIST);
        int desired_antago = get_desired(i, Sign::ANTAGONIST);
        std::cout << "dof: " << i << " | ";
        std::cout << "encoder: " << encoder << " | ";
        if (reference_found)
        {
            std::cout << "position: " << position << std::endl;
        }
        else
        {
            std::cout << "*" << std::endl;
        }
        std::cout << "\tcurrent agonist: " << current_ago
                  << " | desired agonist: " << desired_ago << std::endl;
        std::cout << "\tcurrent antagonist: " << current_antago
                  << " | desired antagonist: " << desired_antago << std::endl;
    }
}
