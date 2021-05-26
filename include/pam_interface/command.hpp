#pragma once

#include "pam_interface/pressure_action.hpp"

namespace pam_interface
{
template <int NB_ACTUATORS>
class Command
{
public:
    Command(int id, PressureAction<NB_ACTUATORS> action)
        : id_(id), action_(action)
    {
    }

    Command(int id) : id_(id)
    {
    }

    Command() : id_(-1)
    {
    }

    int get_id() const
    {
        return id_;
    }

    const PressureAction<NB_ACTUATORS>& get_action() const
    {
        return action_;
    }

    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(id_, action_);
    }

private:
    friend shared_memory::private_serialization;
    int id_;
    PressureAction<NB_ACTUATORS> action_;
};

}  // namespace pam_interface
