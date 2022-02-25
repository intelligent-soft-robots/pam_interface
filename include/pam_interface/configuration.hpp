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
template <int NB_DOFS>
class Configuration
{
public:
    Configuration();
    ~Configuration();

public:
    void print() const;

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

    int min_pressure(int dof, Sign sign);
    int max_pressure(int dof, Sign sign);
    int min_pressure();
    int max_pressure();

    int control_period;
    int sensor_period;
    int server_frequency;
    std::array<int, NB_DOFS> max_pressures_ago;
    std::array<int, NB_DOFS> min_pressures_ago;
    std::array<int, NB_DOFS> max_pressures_antago;
    std::array<int, NB_DOFS> min_pressures_antago;
};

template <int NB_DOFS>
class JsonConfiguration : public Configuration<NB_DOFS>
{
public:
    JsonConfiguration(const std::string &file_path);
};

#include "configuration.hxx"

}  // namespace pam_interface
