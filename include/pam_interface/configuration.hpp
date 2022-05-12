#pragma once

#include <filesystem>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include "json_helper/json_helper.hpp"
#include "pam_interface/sign.hpp"

namespace pam_interface
{
/**
 * @brief Configuration class
 *
 * Stores parameters of desired system.
 *
 * @tparam NB_DOFS number of degrees of freedom
 */
template <int NB_DOFS>
class Configuration
{
public:
    /**
     * Constructs a new Configuration object.
     */
    Configuration();

    /**
     * Terminates a Configuration object.
     */
    ~Configuration();

public:
    /**
     * Console print of configuration parameters.
     */
    void print() const;

    /**
     * Serialization of configuration parameters in specified
     * achive.
     *
     * @tparam Archive
     * @param archive Archive object
     */
    template <class Archive>
    void serialize(Archive &archive)
    {
        archive(control_period,
                sensor_period,
                server_frequency,
                max_pressures_ago,
                min_pressures_ago,
                max_pressures_antago,
                min_pressures_antago);
    }

    /**
     * Returns minimum pressure parameter of specified degree
     * of freedom and specified agonist-antagonist sign specifier.
     *
     * @param dof index of desired degree of freedom
     * @param sign agonist-antagonist specifier
     * @return int minimum pressure parameter
     */
    int min_pressure(int dof, Sign sign);

    /**
     * Returns maximum pressure parameter of specified degree
     * of freedom and specified agonist-antagonist sign specifier.
     *
     * @param dof index of desired degree of freedom
     * @param sign agonist-antagonist specifier
     * @return int maximum pressure parameter
     */
    int max_pressure(int dof, Sign sign);

    /**
     * Returns smallest minimum pressure parameter of all degrees of
     * freedom.
     *
     * @return int minimum pressure parameter
     */
    int min_pressure();

    /**
     * Returns smallest maximum pressure parameter of all degrees
     * of freedom.
     *
     * @return int maximum pressure parameter
     */
    int max_pressure();

    int control_period;
    int sensor_period;
    int server_frequency;
    std::array<int, NB_DOFS> max_pressures_ago;
    std::array<int, NB_DOFS> min_pressures_ago;
    std::array<int, NB_DOFS> max_pressures_antago;
    std::array<int, NB_DOFS> min_pressures_antago;
};

/**
 * @brief JSON Configuration class.
 *
 * Special Configuration object gathered from JSON file.
 * JsonConfiguration class inherits from Configuration class.
 *
 * @tparam NB_DOFS number of degrees of freedom
 */
template <int NB_DOFS>
class JsonConfiguration : public Configuration<NB_DOFS>
{
public:
    /**
     * Constructs JSONConfiguration object with parameters
     * stored in JSON file in specified file path.
     *
     * @param file_path
     */
    JsonConfiguration(const std::string &file_path);
};

#include "configuration.hxx"

}  // namespace pam_interface
