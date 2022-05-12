#pragma once

#include "pam_interface/pressure_action.hpp"

namespace pam_interface
{
/**
 * @brief Command parent class.
 *
 * Command class for serialization of pressure actions with
 * command IDs.
 *
 * Each control command has its own unique ID which consists
 * of an incrementally increased integer. Using the command ID,
 * control outputs can be archieved and the history of outputs
 * can be traced.
 *
 * @tparam NB_ACTUATORS number of actuators
 */
template <int NB_ACTUATORS>
class Command
{
public:
    /**
     * Constructs a new Command object with specified ID
     * and PressureAction object.
     *
     * @param id Command ID
     * @param action PressureAction object
     */
    Command(int id, PressureAction<NB_ACTUATORS> action)
        : id_(id), action_(action)
    {
    }

    /**
     * Constructs a new Command object with specified ID.
     *
     * @param id Command ID
     */
    Command(int id) : id_(id)
    {
    }

    /**
     * Constructs a new Command object with no ID
     * specified.
     */
    Command() : id_(-1)
    {
    }

    /**
     * Returns command ID.
     *
     * @return int Command ID
     */
    int get_id() const
    {
        return id_;
    }

    /**
     * Returns pressure action.
     *
     * @return const PressureAction<NB_ACTUATORS>&
     */
    const PressureAction<NB_ACTUATORS>& get_action() const
    {
        return action_;
    }

    /**
     * Serializes command in specified archive.
     *
     * @tparam Archive
     * @param archive Archive object.
     */
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
