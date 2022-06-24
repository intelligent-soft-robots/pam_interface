#pragma once

#include <array>
#include <stdexcept>
#include "pam_interface/sign.hpp"
#include "shared_memory/serializer.hpp"

namespace pam_interface
{
/**
 * @brief Pressure Action class.
 *
 * Manages and stores pressure actuation commands for a variable
 * number of actuators.
 *
 * @tparam NB_ACTUATORS Number of actuators.
 */
template <int NB_ACTUATORS>
class PressureAction
{
public:
    /**
     * Constructor of Pressure Action object.
     */
    PressureAction()
    {
    }

    /**
     * Constructor of Pressure Action objects with other
     * constant Pressure Action object.
     *
     * @param other Template Pressure Action object
     */
    PressureAction(const PressureAction<NB_ACTUATORS>& other);

    /**
     * Constructor of Pressure Action objects with other Pressure
     * Action object as template with compile-time check.
     *
     * @param other Template Pressure Action object.
     */
    PressureAction(PressureAction<NB_ACTUATORS>&& other) noexcept;

    /**
     * Equal operator overloading for Pressure Action object assignment.
     *
     * @param other Template Pressure Action object.
     * @return PressureAction<NB_ACTUATORS>& Pressure Action object.
     */
    PressureAction<NB_ACTUATORS>& operator=(
        const PressureAction<NB_ACTUATORS>& other);

    /**
     * Equal operator overloading for Pressure Action object assignment
     * with compile-time check.
     *
     * @param other Template Pressure Action object.
     * @return PressureAction<NB_ACTUATORS>& Pressure Action object.
     */
    PressureAction<NB_ACTUATORS>& operator=(
        PressureAction<NB_ACTUATORS>&& other) noexcept;

public:
    /**
     * Checks validity of given actuator index and gets current
     * pressure of specified actuator.
     *
     * @param actuator Specified actuator
     * @return Pressure value.
     *
     * @remark even actuator indices are agonist actuators,
     * odd actuator indices specify antagonist actuators.
     */
    int get(int actuator) const;

    /**
     * Gets current pressure of specified degree of freedom
     * and specified agonist-antagonist sign specifier.
     *
     * @param dof Index of desired degree of freedom
     * @param sign Agonist-antagonist specifier (0 for AGONIST,
     * 1 for ANTAGONIST, see sign.hpp for reference)
     * @return Pressure value
     */
    int get(int dof, Sign sign) const;

    /**
     * Checks validity of given actuator index and sets given
     * pressure value for specified actuator.
     *
     * @param actuator Actuator index of actuator to be tuned
     * @param pressure Pressure value to be set
     */
    void set(int actuator, int pressure);

    /**
     * Sets given pressure value for specified degree of freedom
     * and specified agonist-antagonist sign specifier.
     *
     * @param dof Index of desired degree of freedom
     * @param sign Agonist-antagonist specifier (0 for AGONIST,
     * 1 for ANTAGONIST, see sign.hpp for reference)
     * @param pressure Pressure value to be set
     */
    void set(int dof, Sign sign, int pressure);

    /**
     * Serialization of pressure values in specified
     * archive.
     *
     * @tparam Archive
     * @param archive Archive object
     */
    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(pressures_);
    }

private:
    friend shared_memory::private_serialization;
    std::array<int, NB_ACTUATORS> pressures_;
};

#include "pressure_action.hxx"

}  // namespace pam_interface
