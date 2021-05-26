

template <int NB_ACTUATORS>
PressureAction<NB_ACTUATORS>::PressureAction(
    const PressureAction<NB_ACTUATORS>& other)
    : pressures_(other.pressures_)
{
}

template <int NB_ACTUATORS>
PressureAction<NB_ACTUATORS>::PressureAction(
    PressureAction<NB_ACTUATORS>&& other) noexcept
    : pressures_(std::move(other.pressures_))
{
}

template <int NB_ACTUATORS>
PressureAction<NB_ACTUATORS>& PressureAction<NB_ACTUATORS>::operator=(
    const PressureAction<NB_ACTUATORS>& other)
{
    pressures_ = other.pressures_;
    return *this;
}

template <int NB_ACTUATORS>
PressureAction<NB_ACTUATORS>& PressureAction<NB_ACTUATORS>::operator=(
    PressureAction<NB_ACTUATORS>&& other) noexcept
{
    pressures_ = std::move(other.pressures_);
    return *this;
}

template <int NB_ACTUATORS>
void PressureAction<NB_ACTUATORS>::set(int actuator, int value)
{
    if (value < 0)
    {
        value = 0;
    }
    if (actuator < 0 || actuator >= NB_ACTUATORS)
    {
        throw std::runtime_error(
            "pam_interface::PressureAction: invalid actuator index");
    }
    pressures_[actuator] = value;
}

template <int NB_ACTUATORS>
void PressureAction<NB_ACTUATORS>::set(int dof, Sign sign, int value)
{
    if (sign == Sign::AGONIST)
    {
        set(2 * dof, value);
    }
    else
    {
        set(2 * dof + 1, value);
    }
}

template <int NB_ACTUATORS>
int PressureAction<NB_ACTUATORS>::get(int actuator) const
{
    if (actuator < 0 || actuator >= NB_ACTUATORS)
    {
        throw std::runtime_error(
            "pam_interface::PressureAction: invalid actuator index");
    }
    return pressures_[actuator];
}

template <int NB_ACTUATORS>
int PressureAction<NB_ACTUATORS>::get(int dof, Sign sign) const
{
    if (sign == Sign::AGONIST)
    {
        return get(2 * dof);
    }
    else
    {
        return get(2 * dof + 1);
    }
}
