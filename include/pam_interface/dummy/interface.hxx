#define UNUSED(x) (void)(x)

template <int NB_DOFS>
DummyInterface<NB_DOFS>::DummyInterface(
    const Configuration<NB_DOFS>& configuration)
    : Interface<NB_DOFS>(),
      configuration_(configuration),
      beginning_of_time_(time_now())
{
    positions_.fill(0);
    encoder_readings_.fill(0);
    references_found_.fill(true);
}

template <int NB_DOFS>
bool DummyInterface<NB_DOFS>::is_reference_found(int dof)
{
    UNUSED(dof);
    return true;
}

template <int NB_DOFS>
DummyInterface<NB_DOFS>::~DummyInterface()
{
}

template <int NB_DOFS>
Microseconds DummyInterface<NB_DOFS>::time_diff(int delta_sensor_iteration)
{
    return Microseconds(delta_sensor_iteration *
                        configuration_.sensor_period.count());
}

template <int NB_DOFS>
double DummyInterface<NB_DOFS>::encoder_to_angle(int dof, int encoder)
{
    UNUSED(dof);
    return static_cast<double>(encoder) * 0.07258065;
}

template <int NB_DOFS>
std::chrono::microseconds DummyInterface<NB_DOFS>::get_control_period()
{
    return configuration_.control_period;
}

template <int NB_DOFS>
std::chrono::microseconds DummyInterface<NB_DOFS>::get_sensor_period()
{
    return configuration_.sensor_period;
}

template <int NB_DOFS>
void DummyInterface<NB_DOFS>::set_pressure(int dof, Sign sign, int value)
{
    // not actually setting any id, this is mainly for other interfaces, such as
    // the sim_interface that needs to know when a new state has been consumed
    if (sign == Sign::AGONIST)
    {
        value = clip(configuration_.min_pressures_ago[dof],
                     configuration_.max_pressures_ago[dof],
                     value);
        this->pressures_ago_[dof] = value;
        this->desired_agonists_[dof] = value;
    }
    else
    {
        value = clip(configuration_.min_pressures_antago[dof],
                     configuration_.max_pressures_antago[dof],
                     value);
        this->pressures_antago_[dof] = value;
        this->desired_antagonists_[dof] = value;
    }
}

template <int NB_DOFS>
int DummyInterface<NB_DOFS>::read_pressure(int dof, Sign sign)
{
    if (sign == Sign::AGONIST)
    {
        return pressures_ago_[dof];
    }
    return pressures_antago_[dof];
}

template <int NB_DOFS>
int DummyInterface<NB_DOFS>::read_encoder(int dof)
{
    UNUSED(dof);
    double angle = read_angle(dof);
    return static_cast<int>(angle / 0.07258065 + 0.5);
}

template <int NB_DOFS>
double DummyInterface<NB_DOFS>::read_angle(int dof)
{
    int ago = pressures_ago_[dof];
    int antago = pressures_antago_[dof];
    double sum = static_cast<double>(ago + antago);
    double ratio = static_cast<double>(ago) / static_cast<double>(antago);
    double exp = std::exp(-ratio + 1);
    double sigmoid = 1.0 / (1.0 + exp);
    return (sigmoid - 0.5) * 5 * 180 * (sum / 50000);
}

template <int NB_DOFS>
long int DummyInterface<NB_DOFS>::iteration(int period)
{
    Microseconds now = time_now();
    Microseconds diff_ = now - beginning_of_time_;
    long int diff = diff_.count();
    double r = diff / period;
    return static_cast<long int>(r + 0.5);
}

template <int NB_DOFS>
int DummyInterface<NB_DOFS>::read_sensor_iteration()
{
    return iteration(configuration_.sensor_period);
}

template <int NB_DOFS>
int DummyInterface<NB_DOFS>::read_control_iteration()
{
    return iteration(configuration_.control_period);
}

template <int NB_DOFS>
void DummyInterface<NB_DOFS>::terminate()
{
}

template <int NB_DOFS>
void DummyInterface<NB_DOFS>::init()
{
}
