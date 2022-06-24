#pragma once

#include <chrono>
#include <eigen3/Eigen/Core>

namespace pam_interface
{
typedef std::chrono::microseconds Microseconds;
typedef std::chrono::nanoseconds Nanoseconds;
typedef std::chrono::microseconds TimePoint;
typedef std::chrono::high_resolution_clock Clock;

/**
 * Returns current time in microseconds from chrono library.
 *
 * @return TimePoint
 */
TimePoint time_now();

/**
 * Returns time difference of given TimePoints (usually recorded
 * before and after program subroutine).
 *
 * @param before First reference time
 * @param after Second reference time
 * @return Time difference between passed TimePoints
 */
long int time_diff(const TimePoint& before, const TimePoint& after);

}  // namespace pam_interface
