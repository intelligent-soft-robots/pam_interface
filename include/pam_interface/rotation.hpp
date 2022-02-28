#pragma once

#include <cmath>

namespace pam_interface
{
/**
 * to_rotate being an angle in radian, this
 * method returns the addition of to_rotate
 * to rotation_angle, casted between -pi and
 * +pi.
 */
double rotate(double to_rotate, double rotation_angle);

}  // namespace pam_interface
