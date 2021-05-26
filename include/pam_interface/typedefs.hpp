#pragma once

#include <chrono>
#include <eigen3/Eigen/Core>

namespace pam_interface
{
typedef std::chrono::microseconds Microseconds;
typedef std::chrono::nanoseconds Nanoseconds;
typedef std::chrono::microseconds TimePoint;
typedef std::chrono::high_resolution_clock Clock;

TimePoint time_now();
long int time_diff(const TimePoint& before, const TimePoint& after);

}  // namespace pam_interface
