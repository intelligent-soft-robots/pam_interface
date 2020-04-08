#pragma once


#include <eigen3/Eigen/Core>
#include <chrono>

namespace pam_interface {

  typedef std::chrono::microseconds Microseconds;
  typedef std::chrono::nanoseconds Nanoseconds;
  typedef std::chrono::microseconds TimePoint;
  typedef std::chrono::high_resolution_clock Clock;
  
  TimePoint time_now();
  long int time_diff(const TimePoint& before,
		     const TimePoint& after);
  
}
